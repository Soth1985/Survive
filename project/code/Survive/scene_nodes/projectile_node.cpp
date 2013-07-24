#include <Survive/scene_nodes/projectile_node.h>
#include <Survive/scene_nodes/character_entity_node.h>
#include <Survive/collision/ray.h>
#include <Survive/world.h>
#include <Survive/math_utils.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(ProjectileEntityNode, SURVIVE_TYPELIST_1(DynamicEntityNode))

Type* ProjectileEntityNode::GetType()const
{
	return TypeImpl<ProjectileEntityNode>::Instance();
}

ProjectileEntityNode::ProjectileEntityNode()
	:
m_MaskToTrace(0),
m_Damage(0),
m_pShooter(0),
m_Speed(0.0f)
{

}

void ProjectileEntityNode::InitProjectile(const SceneNode* pShooter, const sf::Vector2f& ShootDir, float Speed, int Damage, unsigned int TraceMask, const sf::Texture* pTex)
{
	m_pShooter = pShooter;
	m_ShootDir = ShootDir;
	m_Speed = Speed;
	m_Damage = Damage;
	m_MaskToTrace = TraceMask;
	
	if (pTex)
	{
		m_Sprite.setTexture(*pTex);
		m_Sprite.setRotation(MathUtils::RadToDeg(atan2f(m_ShootDir.y, m_ShootDir.x)) + 90.0f);
		sf::Vector2u SizeU = pTex->getSize();
		sf::Vector2f SizeF(SizeU.x, SizeU.y);
		m_Collision.SetCornerPosition(-SizeF * 0.5f);
		m_Collision.SetSize(SizeF);
		m_Collision.SetCollisionGroup(eCollisionGroup::Projectile);
		GetWorld()->GetQuadTree()->AddObject(this);
	}

	SetUpdateFrequency(2, 5);
}

void ProjectileEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Sprite, States);
}

void ProjectileEntityNode::OnUpdate(float Dt)
{
	if (!GetInFrustrum())
	{
		GetWorld()->AddSceneNodeToRemove(this);
		return;
	}

	Ray R(GetWorldPosition(), m_ShootDir);
	float Param = Dt * m_Speed;
	HitInfo Result;

	GetWorld()->GetQuadTree()->RayTraceClosest(R, m_MaskToTrace, this, Result);

	if (Result.m_pObject && Result.m_Param < Param)
	{
		CharacterEntityNode* pCharacter = TypeCast<CharacterEntityNode>(Result.m_pObject);

		if (pCharacter)
			pCharacter->OnHit(m_Damage);

		GetWorld()->AddSceneNodeToRemove(this);
		return;
	}
	
	Move(m_ShootDir * Param);
}

AlignedBoxShape ProjectileEntityNode::GetBounds()
{
	return m_Collision;
}

const CollisionShape* ProjectileEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

}