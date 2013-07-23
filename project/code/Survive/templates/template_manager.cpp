#include <Survive/templates/template_manager.h>

#include <Survive/templates/content_template.h>
#include <Survive/templates/player_template.h>
#include <Survive/templates/monster_template.h>
#include <Survive/templates/respawn_template.h>

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
		ContentTemplate* pContentTmpl = new ContentTemplate();

		pContentTmpl->m_BigTextures[eBigTextureID::Landscape] = "Textures/grass_map_150.jpg";

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

		pContentTmpl->m_Fonts[eFontID::Arial] = "Fonts/arial.ttf";

		AddTemplate<ContentTemplate>("Content", pContentTmpl);
	}	

	{
		PlayerTemplate* pPlayerTmpl = new PlayerTemplate();
		pPlayerTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::ChaosLordBody, 1.0f));
		AddTemplate<PlayerTemplate>("Player", pPlayerTmpl);
	}

	{
		MonsterTemplate* pOrkBoyChoppaTmpl = new MonsterTemplate();
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody1, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody2, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody3, 1.0f));
		pOrkBoyChoppaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyChoppaBody4, 1.0f));
		AddTemplate<MonsterTemplate>("OrkBoyChoppa", pOrkBoyChoppaTmpl);
	}

	{
		MonsterTemplate* pOrkBoyShootaTmpl = new MonsterTemplate();
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody1, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody2, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody3, 1.0f));
		pOrkBoyShootaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBoyShootaBody4, 1.0f));
		AddTemplate<MonsterTemplate>("OrkBoyShoota", pOrkBoyShootaTmpl);
	}

	{
		MonsterTemplate* pOrkBadrukkTmpl = new MonsterTemplate();
		pOrkBadrukkTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkBadrukkBody, 1.0f));
		AddTemplate<MonsterTemplate>("OrkBadrukk", pOrkBadrukkTmpl);
	}

	{
		MonsterTemplate* pOrkThrakaTmpl = new MonsterTemplate();
		pOrkThrakaTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkThrakaBody, 1.0f));
		AddTemplate<MonsterTemplate>("OrkThraka", pOrkThrakaTmpl);
	}

	{
		MonsterTemplate* pOrkWarbossTmpl = new MonsterTemplate();
		pOrkWarbossTmpl->m_BodyTextures.push_back(CharacterTemplate::TexIdPair(eTextureID::OrkWarbossBody, 1.0f));
		AddTemplate<MonsterTemplate>("OrkWarboss", pOrkWarbossTmpl);
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