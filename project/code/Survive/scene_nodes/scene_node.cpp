#include <Survive/scene_nodes/scene_node.h>
#include <Survive/quad_tree_node.h>
#include <Survive/math_utils.h>
#include <Survive/world.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(SceneNode, SURVIVE_TYPELIST_1(Rtti))

SceneNode::SceneNode()
	:
m_pParent(0),
m_Id((int)this),
m_Flags(0),
m_Layer(eWorldLayer::LayerCount),
m_pQuadTreeNode(0),
m_pWorld(0),
m_UpdateFrequency(1),
m_UpdatePhase(0),
m_TimeStepAccum(0.0f),
m_IsInFrustrum(true)
{
	SetInFrustrum(false);
}

SceneNode::~SceneNode()
{
	m_pParent = 0;
}

bool SceneNode::AddChild(SceneNode* Node)
{
	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		if (m_pChildren[Idx].get() == Node)
			return false;
	}

	m_pChildren.push_back(SceneNodePtr());

	m_pChildren.back().reset(Node);

	Node->m_pParent = this;

	return true;
}

bool SceneNode::RemoveNode(SceneNode* Node)
{
	for (auto It = m_pChildren.begin(); It != m_pChildren.end(); ++It)
	{
		if ((*It).get() == Node)
		{
			m_pChildren.erase(It);
			return true;
		}
	}

	return false;
}

sf::Transform SceneNode::GetWorldTransform()const
{
	sf::Transform Result = m_Transform.getTransform();

	if (m_pParent)
	{
		Result = m_pParent->GetWorldTransform() * Result;
	}

	return Result;
}

void SceneNode::InitFromTemplate(const Template* Tmpl)
{

}

sf::Vector2f SceneNode::GetWorldPosition()const
{
	sf::Transform T = GetWorldTransform();

	return MathUtils::GetTranslation(T);
}

void SceneNode::draw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	/*States.transform *= m_Transform.getTransform();

	OnDraw(Target, States);

	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		m_pChildren[Idx]->draw(Target, States);
	}*/

	States.transform = GetWorldTransform();
	OnDraw(Target, States);
}

void SceneNode::Update(float Dt)
{
	unsigned int freq = GetUpdateFrequency();
	unsigned int phase = GetUpdatePhase();
	unsigned int frame = freq + phase;
	unsigned int tick = GetWorld()->GetTickCounter();

	if ( tick % frame != 0 )
	{
		m_TimeStepAccum += Dt;
	}
	else
	{
		if (GetWorld()->IsObjectInView(this))
		{
			SetInFrustrum(true);
		}
		else
		{
			SetInFrustrum(false);
		}

		OnUpdate(std::max(m_TimeStepAccum, Dt));
		m_TimeStepAccum = 0.0f;
	}
	

	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		m_pChildren[Idx]->Update(Dt);
	}
}

void SceneNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{

}

void SceneNode::OnUpdate(float Dt)
{

}

Type* SceneNode::GetType()const
{
	return TypeImpl<SceneNode>::Instance();
}

AlignedBoxShape SceneNode::GetBounds()
{
	return AlignedBoxShape();
}

const CollisionShape* SceneNode::GetCollisionShape()const
{
	return 0;
}

CollisionShape* SceneNode::GetCollisionShapeModify()
{
	return const_cast<CollisionShape*>(GetCollisionShape());
}

const sf::Vector2f& SceneNode::GetLocalPosition()const
{
	return m_Transform.getPosition();
}

void SceneNode::SetLocalPosition(const sf::Vector2f& Position)
{
	if (!MathUtils::AreClose(Position, m_Transform.getPosition()))
	{
		m_Transform.setPosition(Position);
		UpdateQuadTreeLocation();
	}	
}

void SceneNode::UpdateQuadTreeLocation()
{
	const CollisionShape* pShape = GetCollisionShape();

	if (pShape && m_pQuadTreeNode)
	{
		int oc = GetWorld()->GetQuadTree()->GetObjectCount();
		m_pQuadTreeNode->Remove(this);
		//int oc2 = GetWorld()->GetQuadTree()->GetObjectCount();
		GetWorld()->GetQuadTree()->AddObject(this);
		
		//m_pQuadTreeNode->Update(this);
		int oc1 = GetWorld()->GetQuadTree()->GetObjectCount();
		assert(oc == oc1);
	}	
}

void SceneNode::SetLocalScale(const sf::Vector2f& Scale)
{
	m_Transform.setScale(Scale);
}

void SceneNode::Move(const sf::Vector2f& Disp)
{
	m_Transform.move(Disp);
	UpdateQuadTreeLocation();
}

void SceneNode::OnEnterLeaveFrustrum(bool NewFrustrumState)
{

}

void SceneNode::SetUpdateFrequency(unsigned int Frequency, unsigned int MaxPhase)
{
	m_UpdateFrequency = Frequency;
}

}