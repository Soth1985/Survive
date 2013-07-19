#include <Survive/scene_nodes/scene_node.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(SceneNode, SURVIVE_TYPELIST_1(Rtti))

SceneNode::SceneNode()
	:
m_pParent(0),
m_Id((int)this),
m_Flags(0),
m_Layer(eWorldLayer::LayerCount)
{

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

sf::Vector2f SceneNode::GetWorldPosition()const
{
	sf::Transform T = GetWorldTransform();

	const float* pMat = T.getMatrix();

	return sf::Vector2f(pMat[12], pMat[13]);
}

void SceneNode::draw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	States.transform *= m_Transform.getTransform();

	OnDraw(Target, States);

	for (size_t Idx = 0; Idx < m_pChildren.size(); ++Idx)
	{
		m_pChildren[Idx]->draw(Target, States);
	}
}

void SceneNode::Update(float Dt)
{
	OnUpdate(Dt);

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

sf::FloatRect SceneNode::GetBounds()
{
	return sf::FloatRect();
}

}