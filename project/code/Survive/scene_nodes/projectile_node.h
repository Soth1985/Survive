#pragma once

#include <Survive/forward.h>
#include <Survive/scene_nodes/dynamic_entity_node.h>

#include <SFML/Graphics/Sprite.hpp>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::ProjectileEntityNode);

class ProjectileEntityNode : public DynamicEntityNode
{
public:

	ProjectileEntityNode();

	virtual Type* GetType()const;

	void InitProjectile(const SceneNode* pShooter, const sf::Vector2f& ShootDir, float Speed, int Damage, unsigned int TraceMask, const sf::Texture* pTex);

	virtual AlignedBoxShape GetBounds();

	virtual const CollisionShape* GetCollisionShape()const;

protected:

	virtual void OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const;

	virtual void OnUpdate(float Dt);

private:

	unsigned int m_MaskToTrace;
	sf::Sprite m_Sprite;
	sf::Vector2f m_ShootDir;
	int m_Damage;
	const SceneNode* m_pShooter;
	float m_Speed;
	AlignedBoxShape m_Collision;
};

}