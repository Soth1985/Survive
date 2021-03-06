#pragma once

#include <Survive/forward.h>
#include <Survive/rtti.h>
#include <Survive/collision/collision_shape.h>
#include <Survive/collision/aligned_box_shape.h>

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

	bool IsMarkedForDelete()const
	{
		return m_Flags & eSceneNodeFlags::MarkToDelete;
	}

	bool AddChild(SceneNode* Node);

	bool RemoveNode(SceneNode* Node);

	const SceneNode* GetParent()const
	{
		return m_pParent;
	}

	sf::Transform GetWorldTransform()const;

	sf::Vector2f GetWorldPosition()const;

	const sf::Vector2f& GetLocalPosition()const;

	void SetLocalPosition(const sf::Vector2f& Position);

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

	unsigned int GetUpdateFrequency()const
	{
		return m_UpdateFrequency;
	}

	unsigned int GetUpdatePhase()const
	{
		return m_UpdatePhase;
	}

	bool GetInFrustrum()const
	{
		return m_IsInFrustrum;
	}

	void SetLocalScale(const sf::Vector2f& Scale);

	void Move(const sf::Vector2f& Disp);

	void Rotate(float AngleDegrees)
	{
		m_Transform.rotate(AngleDegrees);
	}

	virtual AlignedBoxShape GetBounds();

	void Update(float Dt);

	virtual Type* GetType()const;

	virtual const CollisionShape* GetCollisionShape()const;

	void SetCollisionGroup(unsigned int Group);

protected:

	friend class World;

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

	virtual void InitFromTemplate(const Template* Tmpl);

	virtual void OnEnterLeaveFrustrum(bool NewFrustrumState);

	World* GetWorld()const
	{
		return m_pWorld;
	}

	eWorldLayer::Val GetWorldLayer()
	{
		return m_Layer;
	}

	const sf::Vector2f& GetVelocity()const
	{
		return m_Velocity;
	}

	void SetVelocity(const sf::Vector2f& Velocity)
	{
		m_Velocity = Velocity;
	}

	void UpdateQuadTreeLocation();

	QuadTreeNode* GetQuadTreeNode()
	{
		return m_pQuadTreeNode;
	}

	CollisionShape* GetCollisionShapeModify();

	void SetUpdateFrequency(unsigned int Frequency, unsigned int MaxPhase);

	void SetInFrustrum(bool InFrustrum);

private:

	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States)const;
	
	void SetQuadTreeNode(QuadTreeNode* pTreeNode)
	{
		m_pQuadTreeNode = pTreeNode;
	}

	friend class QuadTreeNode;

	sf::Transformable m_Transform;
	sf::Vector2f m_Velocity;
	std::vector<SceneNodePtr> m_pChildren;
	SceneNode* m_pParent;
	eWorldLayer::Val m_Layer;
	World* m_pWorld;
	int m_Id;
	int m_Flags;
	QuadTreeNode* m_pQuadTreeNode;
	unsigned int m_UpdateFrequency;
	unsigned int m_UpdatePhase;
	bool m_IsInFrustrum;
	float m_TimeStepAccum;
};

}