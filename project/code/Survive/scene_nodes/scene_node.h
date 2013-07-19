#pragma once

#include <Survive/forward.h>
#include <Survive/rtti.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::SceneNode);

class SceneNode: public sf::Drawable, public Rtti
{
public:

	SceneNode();

	~SceneNode();

	size_t GetChildC()const
	{
		return m_pChildren.size();
	}

	bool AddChild(SceneNode* Node);

	bool RemoveNode(SceneNode* Node);

	const SceneNode* GetParent()const
	{
		return m_pParent;
	}

	sf::Transform GetWorldTransform()const;

	sf::Vector2f GetWorldPosition()const;

	const sf::Vector2f& GetLocalPosition()const
	{
		return m_Transform.getPosition();
	}

	void SetLocalPosition(const sf::Vector2f& Position)
	{
		m_Transform.setPosition(Position);
	}

	float GetLocalRotation()const
	{
		return m_Transform.getRotation();
	}

	void SetLocalRotation(float AngleDegree)
	{
		m_Transform.setRotation(AngleDegree);
	}

	const sf::Vector2f& GetLocalScale()const
	{
		return m_Transform.getScale();
	}

	void SetLocalScale(const sf::Vector2f& Scale)
	{
		m_Transform.setScale(Scale);
	}

	const sf::Vector2f& GetOrigin()const
	{
		return m_Transform.getOrigin();
	}

	void SetOrigin(const sf::Vector2f& Origin)
	{
		m_Transform.setOrigin(Origin);
	}

	void Move(const sf::Vector2f& Disp)
	{
		m_Transform.move(Disp);
	}

	void Rotate(float AngleDegrees)
	{
		m_Transform.rotate(AngleDegrees);
	}

	virtual sf::FloatRect GetBounds();

	void Update(float Dt);

	virtual Type* GetType()const;

protected:

	friend class World;

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

	World* GetWorld()
	{
		return m_pWorld;
	}

	eWorldLayer::Val GetWorldLayer()
	{
		return m_Layer;
	}

private:

	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States)const;

	sf::Transformable m_Transform;
	std::vector<SceneNodePtr> m_pChildren;
	SceneNode* m_pParent;
	eWorldLayer::Val m_Layer;
	World* m_pWorld;
	int m_Id;
	int m_Flags;
};

}