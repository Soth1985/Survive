#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/scene_nodes/character_entity_node.h>
#include <Survive/scene_nodes/projectile_node.h>
#include <Survive/scene_nodes/static_sprite_node.h>
#include <Survive/templates/character_template.h>
#include <Survive/templates/static_sprite_template.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(CharacterEntityNode, SURVIVE_TYPELIST_1(DynamicEntityNode))

CharacterEntityNode::CharacterEntityNode()
	:
m_RangedWeaponUseTimer(0.0f),
m_CloseCombatWeaponUseTime(0.0f),
m_pLastWeaponTmpl(0),
m_pRangedWeaponTmpl(0),
m_pCloseCombatWeaponTmpl(0),
m_Health(0)
{

}

Type* CharacterEntityNode::GetType()const
{
	return TypeImpl<CharacterEntityNode>::Instance();
}
	
void CharacterEntityNode::InitFromTemplate(const Template* Tmpl)
{
	m_pCharacterTmpl = TypeCast<CharacterTemplate>(Tmpl);

	if (m_pCharacterTmpl)
	{
		eTextureID::Val BodyTexId = MathUtils::GetRandomItem(m_pCharacterTmpl->m_BodyTextures);
		ContentManager* pContentManager = GetWorld()->GetContext()->GetContentManager();
		const sf::Texture* pBodyTex = pContentManager->Textures().Get(BodyTexId);

		if (pBodyTex)
		{
			m_Body.setTexture(*pBodyTex);
			sf::Vector2f HalfSize(m_Body.getLocalBounds().width / 2.0f, m_Body.getLocalBounds().height / 2.0f);
			m_Body.setOrigin(HalfSize);
			m_CloseCombatSprite.setOrigin(HalfSize);
			m_RangedWeaponSprite.setOrigin(HalfSize);
			m_Health = m_pCharacterTmpl->m_MaxHealth;

			m_pCloseCombatWeaponTmpl = m_pCharacterTmpl->m_CloseCombatWeapon.GetTemplate();

			if (m_pCloseCombatWeaponTmpl)
			{
				const sf::Texture* pCloseWeaponTex = pContentManager->Textures().Get(m_pCloseCombatWeaponTmpl->m_Texture);

				if (pCloseWeaponTex)
					m_CloseCombatSprite.setTexture(*pCloseWeaponTex);

				m_pLastWeaponTmpl = m_pCloseCombatWeaponTmpl;
			}

			m_pRangedWeaponTmpl = m_pCharacterTmpl->m_RangedWeapon.GetTemplate();

			if (m_pRangedWeaponTmpl)
			{
				const sf::Texture* pRangedWeaponTex = pContentManager->Textures().Get(m_pRangedWeaponTmpl->m_Texture);

				if (pRangedWeaponTex)
					m_RangedWeaponSprite.setTexture(*pRangedWeaponTex);

				m_pLastWeaponTmpl = m_pRangedWeaponTmpl;
			}
			//HalfSize *= sqrtf(2.0f);
			m_Collision.SetCornerPosition(-HalfSize);
			m_Collision.SetSize(HalfSize * 2.0f);
			GetWorld()->GetQuadTree()->AddObject(this);
		}
		else
			GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Body texture not found.");
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid character template type.");
	}
}

const CollisionShape* CharacterEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

void CharacterEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	if (m_pLastWeaponTmpl == m_pRangedWeaponTmpl)
		Target.draw(m_RangedWeaponSprite, States);
	else if (m_pLastWeaponTmpl == m_pCloseCombatWeaponTmpl)
		Target.draw(m_CloseCombatSprite, States);

	Target.draw(m_Body, States);	
	GetWorld()->GetContext()->GetDebugRender()->AddAlignedBox(m_Collision, GetWorldTransform(), 0.01f);
}

void CharacterEntityNode::OnUpdate(float Dt)
{
	if (m_RangedWeaponUseTimer > 0.0f)
		m_RangedWeaponUseTimer -= Dt;

	if (m_CloseCombatWeaponUseTime > 0.0f)
		m_CloseCombatWeaponUseTime -= Dt;
}

AlignedBoxShape CharacterEntityNode::GetBounds()
{
	return m_Collision;
}

void CharacterEntityNode::UseRangedWeapon(const sf::Vector2f& ShootDir)
{
	if (m_pRangedWeaponTmpl && m_RangedWeaponUseTimer <= 0.0f)
	{
		m_pLastWeaponTmpl = m_pRangedWeaponTmpl;
		m_RangedWeaponUseTimer = m_pRangedWeaponTmpl->m_ShootTime;

		ProjectileEntityNode* pProjectile = GetWorld()->CreateNode<ProjectileEntityNode>(GetWorld()->GetLayerRoot(eWorldLayer::ProjectilesLayer));

		const sf::Texture* pTex = GetWorld()->GetContext()->GetContentManager()->Textures().Get(m_pRangedWeaponTmpl->m_ProjectileTexId);

		pProjectile->InitProjectile(this, ShootDir, m_pRangedWeaponTmpl->m_ProjectileSpeed, m_pRangedWeaponTmpl->m_Damage, GetBulletTraceMask(), pTex);

		pProjectile->SetLocalPosition(GetWorldPosition());
	}
}

void CharacterEntityNode::UseCloseCombatWeapon()
{
	if (m_pCloseCombatWeaponTmpl)
	{
		m_CloseCombatWeaponUseTime = m_pCloseCombatWeaponTmpl->m_SwingTime;
		m_pLastWeaponTmpl = m_pCloseCombatWeaponTmpl;
	}
}

void CharacterEntityNode::OnHit(int Damage)
{
	m_Health -= Damage;

	if (m_Health <= 0)
	{
		QuadTreeNode::HitList Objects;
		GetWorld()->GetQuadTree()->GetObjects(GetBounds(), GetWorldTransform(), eCollisionGroup::BloodSplash, 0, Objects);
		
		if (Objects.empty())
		{
			StaticSpriteEntityNode* pNode = GetWorld()->CreateNode<StaticSpriteEntityNode>(GetWorld()->GetLayerRoot(eWorldLayer::LandscapeLayer));
			StaticSpriteTemplate* pNodeTmpl = TemplateManager::Instance().GetTemplate<StaticSpriteTemplate>("StaticSpritesBlood");
			pNode->InitFromTemplate(pNodeTmpl);
			pNode->SetCollisionGroup(eCollisionGroup::BloodSplash);
			pNode->SetLocalPosition(GetWorldPosition());
		}
	}
}

float CharacterEntityNode::GetSpeed()const
{
	return m_pCharacterTmpl->m_MoveSpeed;
}

int CharacterEntityNode::GetHealth()const
{
	return m_Health;
}

int CharacterEntityNode::GetMaxHealth()const
{
	return m_pCharacterTmpl->m_MaxHealth;
}

}