#include <Survive/scene_node.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SceneNode::SceneNode()
	:
m_pParent(0)
{

}

SceneNode::~SceneNode()
{
	m_pParent = 0;
}

bool SceneNode::AddChild(SceneNode* Node)
{
	for (size_t Idx = 0; Idx < m_Children.size(); ++Idx)
	{
		if (m_Children[Idx].get() == Node)
			return false;
	}

	m_Children.push_back(SceneNodePtr());

	m_Children.back().reset(Node);

	return true;
}

bool SceneNode::RemoveNode(SceneNode* Node)
{
	for (auto It = m_Children.begin(); It != m_Children.end(); ++It)
	{
		if ((*It).get() == Node)
		{
			m_Children.erase(It);
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

	for (size_t Idx = 0; Idx < m_Children.size(); ++Idx)
	{
		m_Children[Idx]->draw(Target, States);
	}
}

void SceneNode::Update(float Dt)
{
	OnUpdate(Dt);

	for (size_t Idx = 0; Idx < m_Children.size(); ++Idx)
	{
		m_Children[Idx]->Update(Dt);
	}
}

void SceneNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{

}

void SceneNode::OnUpdate(float Dt)
{

}

}