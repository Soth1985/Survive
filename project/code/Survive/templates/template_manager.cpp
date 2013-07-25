#include <Survive/templates/template_manager.h>

#include <Survive/templates/content_template.h>
#include <Survive/templates/player_template.h>
#include <Survive/templates/monster_template.h>
#include <Survive/templates/respawn_template.h>
#include <Survive/templates/close_combat_weapon_template.h>
#include <Survive/templates/ranged_weapon_template.h>
#include <Survive/templates/static_convex_template.h>
#include <Survive/templates/static_sprite_template.h>
#include <Survive/templates/pickup_template.h>

namespace Survive
{

TemplateManager::TemplateManager()
{
	CreateDefaultTemplates();
}

TemplateManager::~TemplateManager()
{

}

TemplateManager& TemplateManager::Instance()
{
	static TemplateManager Inst;
	return Inst;
}

TemplateManager::TemplateMap* TemplateManager::GetTemplateMap(Type* TmplType)
{
	TmplType = CheckType(TmplType);

	if (TmplType)
	{
		return &m_Templates[TmplType];
	}
	else
		return 0;
}

Type* TemplateManager::CheckType(Type* TmplType)
{
	Type* BaseType = TypeImpl<Template>::Instance();

	if (IsConvertible(TmplType, BaseType))
	{
		return TmplType;
	}
	else
	{
		assert(0 && "Not a template");
		return 0;
	}
}

void TemplateManager::CreateDefaultTemplates()
{
	{
		ConvexPolygonShape S1(4);
		S1[1] = sf::Vector2f(60.0f, 105.0f);
		S1[2] = sf::Vector2f(150.0f, 135.0f);
		S1[3] = sf::Vector2f(150.0f, -30.0f);

		ConvexPolygonShape S2(3);
		S2[1] = sf::Vector2f(90.0f, 90.0f);
		S2[2] = sf::Vector2f(135.0f, -45.0f);

		ConvexPolygonShape S3(6);
		S3[1] = sf::Vector2f(60.0f, 60.0f);
		S3[2] = sf::Vector2f(180.0f, 60.0f);
		S3[3] = sf::Vector2f(240.0f, 0.0f);
		S3[4] = sf::Vector2f(180.0f, -60.0f);
		S3[5] = sf::Vector2f(60.0f, -60.0f);

		StaticConvexTemplate* pConvexTmpl = new StaticConvexTemplate();
		pConvexTmpl->m_Shapes.push_back(StaticConvexTemplate::ShapePair(S1, 1.0f));
		pConvexTmpl->m_Shapes.push_back(StaticConvexTemplate::ShapePair(S2, 1.0f));
		pConvexTmpl->m_Shapes.push_back(StaticConvexTemplate::ShapePair(S3, 1.0f));
		AddTemplate<StaticConvexTemplate>("StaticConvexes", pConvexTmpl);
	}

	{
		RangedWeaponTemplate* pPlayerBolter = new RangedWeaponTemplate();

		pPlayerBolter->m_Texture = eTextureID::ChaosLordWeaponBolter;
		pPlayerBolter->m_Damage = 50;
		pPlayerBolter->m_ShootTime = 0.5f;
		pPlayerBolter->m_ProjectileSpeed = 700.0f;
		pPlayerBolter->m_ProjectileTexId = eTextureID::ProjectileBullet;
		AddTemplate<RangedWeaponTemplate>("PlayerBolter", pPlayerBolter);
	}

	{
		CloseCombatWeaponTemplate* pPlayerSword = new CloseCombatWeaponTemplate();

		pPlayerSword->m_Texture = eTextureID::ChaosLordWeaponSword;
		pPlayerSword->m_Damage = 75;
		pPlayerSword->m_SwingTime = 0.75f;
		pPlayerSword->m_SwingSize = sf::Vector2f(150.0f, 150.0f);
		AddTemplate<CloseCombatWeaponTemplate>("PlayerSword", pPlayerSword);
	}

	{
		RangedWeaponTemplate* pOrkShoota = new RangedWeaponTemplate();

		pOrkShoota->m_Damage = 20;
		pOrkShoota->m_ShootTime = 1.5f;
		pOrkShoota->m_ProjectileSpeed = 600.0f;
		pOrkShoota->m_ProjectileTexId = eTextureID::ProjectileBullet;
		AddTemplate<RangedWeaponTemplate>("OrkShoota", pOrkShoota);
	}

	{
		ContentTemplate* pContentTmpl = new ContentTemplate();

		pContentTmpl->m_BigTextures[eBigTextureID::Landscape] = "Textures/grass_map_150.jpg";

		pContentTmpl->m_Textures[eTextureID::GameOverBackground] = "Textures/game_over.jpg";
		pContentTmpl->m_Textures[eTextureID::MainMenuBackground] = "Textures/main_menu_background.jpg";

		pContentTmpl->m_Textures[eTextureID::ChaosLordBody] = "Textures/chaos_lord/chaos_lord_body.png";
		pContentTmpl->m_Textures[eTextureID::ChaosLordWeaponBolter] = "Textures/chaos_lord/chaos_lord_bolter.png";
		pContentTmpl->m_Textures[eTextureID::ChaosLordWeaponPlasma] = "Textures/chaos_lord/chaos_lord_plasma.png";
		pContentTmpl->m_Textures[eTextureID::ChaosLordWeaponMelta] = "Textures/chaos_lord/chaos_lord_melta.png";
		pContentTmpl->m_Textures[eTextureID::ChaosLordWeaponSword] = "Textures/chaos_lord/chaos_lord_sword.png";

		pContentTmpl->m_Textures[eTextureID::OrkBadrukkBody] = "Textures/ork_characters/ork_badrukk.png";
		pContentTmpl->m_Textures[eTextureID::OrkThrakaBody] = "Textures/ork_characters/ork_thraka.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyChoppaBody1] = "Textures/ork_boys/ork_boy_choppa_1.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyChoppaBody2] = "Textures/ork_boys/ork_boy_choppa_2.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyChoppaBody3] = "Textures/ork_boys/ork_boy_choppa_3.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyChoppaBody4] = "Textures/ork_boys/ork_boy_choppa_4.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyShootaBody1] = "Textures/ork_boys/ork_boy_shoota_1.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyShootaBody2] = "Textures/ork_boys/ork_boy_shoota_2.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyShootaBody3] = "Textures/ork_boys/ork_boy_shoota_3.png";
		pContentTmpl->m_Textures[eTextureID::OrkBoyShootaBody4] = "Textures/ork_boys/ork_boy_shoota_4.png";
		pContentTmpl->m_Textures[eTextureID::OrkWarbossBody] = "Textures/ork_warboss/ork_warboss_body.png";
		pContentTmpl->m_Textures[eTextureID::OrkWarbossWeaponShoota] = "Textures/ork_warboss/ork_warboss_shoota.png";
		pContentTmpl->m_Textures[eTextureID::ProjectileBullet] = "Textures/projectiles/bullet.png";
		pContentTmpl->m_Textures[eTextureID::ProjectilePlasma] = "Textures/projectiles/plasma_particle.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash1] = "Textures/blood/blood_1.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash2] = "Textures/blood/blood_2.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash3] = "Textures/blood/blood_3.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash4] = "Textures/blood/blood_4.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash5] = "Textures/blood/blood_5.png";
		pContentTmpl->m_Textures[eTextureID::BloodSplash6] = "Textures/blood/blood_6.png";
		pContentTmpl->m_Textures[eTextureID::TerrainOrkFortress] = "Textures/terrain/terrain_ork_fortress.png";
		pContentTmpl->m_Textures[eTextureID::TerrainOrkWatchtower] = "Textures/terrain/terrain_ork_watchtower.png";
		pContentTmpl->m_Textures[eTextureID::TerrainOrkBuilding] = "Textures/terrain/terrain_ork_building.png";
		pContentTmpl->m_Textures[eTextureID::TerrainOrkGarage] = "Textures/terrain/terrain_ork_garage.png";
		pContentTmpl->m_Textures[eTextureID::TerrainOrkHut] = "Textures/terrain/terrain_ork_hut.png";

		pContentTmpl->m_Textures[eTextureID::PickupHealthPack] = "Textures/pickups/health.png";

		pContentTmpl->m_Fonts[eFontID::Arial] = "Fonts/arial.ttf";

		AddTemplate<ContentTemplate>("Content", pContentTmpl);
	}	

	{
		PlayerTemplate* pPlayerTmpl = new PlayerTemplate();
		pPlayerTmpl->m_MaxHealth = 5000;
		pPlayerTmpl->m_MoveSpeed = 200.0f;
		pPlayerTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::ChaosLordBody, 1.0f));
		pPlayerTmpl->m_RangedWeapon.SetTemplateName("PlayerBolter");
		pPlayerTmpl->m_CloseCombatWeapon.SetTemplateName("PlayerSword");
		AddTemplate<PlayerTemplate>("Player", pPlayerTmpl);
	}

	{
		StaticSpriteTemplate* pStaticSpriteTemplate = new StaticSpriteTemplate();
		pStaticSpriteTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::TerrainOrkFortress, 0.2f));
		pStaticSpriteTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::TerrainOrkWatchtower, 1.0f));
		pStaticSpriteTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::TerrainOrkBuilding, 1.0f));
		pStaticSpriteTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::TerrainOrkGarage, 1.0f));
		pStaticSpriteTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::TerrainOrkHut, 1.0f));
		AddTemplate<StaticSpriteTemplate>("StaticSprites", pStaticSpriteTemplate);
	}

	{
		StaticSpriteTemplate* pStaticSpriteBloodTemplate = new StaticSpriteTemplate();
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash1, 1.0f));
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash2, 1.0f));
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash3, 1.0f));
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash4, 1.0f));
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash5, 1.0f));
		pStaticSpriteBloodTemplate->m_Textures.push_back(StaticSpriteTemplate::TexIdPair(eTextureID::BloodSplash6, 1.0f));
		AddTemplate<StaticSpriteTemplate>("StaticSpritesBlood", pStaticSpriteBloodTemplate);
	}

	{
		MonsterTemplate* pOrkBoyChoppaTmpl = new MonsterTemplate();
		pOrkBoyChoppaTmpl->m_MaxHealth = 150;
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody1, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody2, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody3, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody4, 1.0f));
		pOrkBoyChoppaTmpl->m_RangedWeapon.SetTemplateName("OrkShoota");
		AddTemplate<MonsterTemplate>("OrkBoyChoppa", pOrkBoyChoppaTmpl);
	}

	{
		MonsterTemplate* pOrkBoyShootaTmpl = new MonsterTemplate();
		pOrkBoyShootaTmpl->m_MaxHealth = 100;
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody1, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody2, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody3, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody4, 1.0f));
		pOrkBoyShootaTmpl->m_RangedWeapon.SetTemplateName("OrkShoota");
		AddTemplate<MonsterTemplate>("OrkBoyShoota", pOrkBoyShootaTmpl);
	}

	{
		MonsterTemplate* pOrkBadrukkTmpl = new MonsterTemplate();
		pOrkBadrukkTmpl->m_MaxHealth = 300;
		pOrkBadrukkTmpl->m_MoveSpeed = 150.0f;
		pOrkBadrukkTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBadrukkBody, 1.0f));
		pOrkBadrukkTmpl->m_RangedWeapon.SetTemplateName("OrkShoota");
		AddTemplate<MonsterTemplate>("OrkBadrukk", pOrkBadrukkTmpl);
	}

	{
		MonsterTemplate* pOrkThrakaTmpl = new MonsterTemplate();
		pOrkThrakaTmpl->m_MaxHealth = 300;
		pOrkThrakaTmpl->m_MoveSpeed = 150.0f;
		pOrkThrakaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkThrakaBody, 1.0f));
		pOrkThrakaTmpl->m_RangedWeapon.SetTemplateName("OrkShoota");
		AddTemplate<MonsterTemplate>("OrkThraka", pOrkThrakaTmpl);
	}

	{
		MonsterTemplate* pOrkWarbossTmpl = new MonsterTemplate();
		pOrkWarbossTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkWarbossBody, 1.0f));
		pOrkWarbossTmpl->m_RangedWeapon.SetTemplateName("OrkShoota");
		AddTemplate<MonsterTemplate>("OrkWarboss", pOrkWarbossTmpl);
	}

	{
		PickupTemplate* pPickupTmpl = new PickupTemplate();
		pPickupTmpl->m_TexId = eTextureID::PickupHealthPack;
		pPickupTmpl->m_HealthToGive = 250;
		AddTemplate<PickupTemplate>("PickupHealth", pPickupTmpl);
	}

	{
		RespawnTemplate* pRespawnTmpl = new RespawnTemplate();
		pRespawnTmpl->m_Spawns.push_back(RespawnTemplate::SpawnPair(RespawnTemplate::Spawn("OrkBoyChoppa"), 1.0f));
		pRespawnTmpl->m_Spawns.push_back(RespawnTemplate::SpawnPair(RespawnTemplate::Spawn("OrkBoyShoota"), 0.4f));
		pRespawnTmpl->m_Spawns.push_back(RespawnTemplate::SpawnPair(RespawnTemplate::Spawn("OrkBadrukk"), 0.1f));
		pRespawnTmpl->m_Spawns.push_back(RespawnTemplate::SpawnPair(RespawnTemplate::Spawn("OrkThraka"), 0.1f));
		AddTemplate<RespawnTemplate>("MonsterRespawn", pRespawnTmpl);
	}
}

}