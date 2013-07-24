#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <functional>
#include <type_traits>
#include <queue>
#include <cassert>

namespace sf
{

class RenderWindow;
class Transform;
class Image;
class Sprite;
class Texture;
class RenderTarget;
class RenderStates;
class Event;

}

namespace Survive
{

class Type;
class Rtti;

class Application;

class Settings;
typedef std::unique_ptr<Settings> SettingsPtr;

class BigTexture;
class BigSprite;

class Action;
class ActionQueue;

class State;
typedef std::unique_ptr<State> StatePtr;

class StateStack;

class GameState;
class SandboxState;
class MainMenuState;
class GameOverState;

class Context;
typedef std::unique_ptr<Context> ContextPtr;

class Gui;
typedef std::unique_ptr<Gui> GuiPtr;

class ContentManager;
typedef std::unique_ptr<ContentManager> ContentManagerPtr;

class SceneNode;
typedef std::unique_ptr<SceneNode> SceneNodePtr;

class DynamicEntityNode;
class StaticEntityNode;
class StaticSpriteEntityNode;
class StaticConvexEntityNode;
class CharacterEntityNode;
class MonsterEntityNode;
class PickupEntityNode;
class PlayerEntityNode;
class LandscapeNode;
class RespawnEntityNode;
class ProjectileEntityNode;

class World;
typedef std::unique_ptr<World> WorldPtr;

class Template;
typedef std::unique_ptr<Template> TemplatePtr;

class CharacterTemplate;
class ContentTemplate;
class MonsterTemplate;
class PickupTemplate;
class PlayerTemplate;
class StaticObjectTemplate;
class StaticSpriteTemplate;
class StaticConvexTemplate;
class WeaponTemplate;
class RangedWeaponTemplate;
class CloseCombatWeaponTemplate;
class RespawnTemplate;

class CollisionShape;
class AlignedBoxShape;
class OrientedBoxShape;
class ConvexPolygonShape;
class Ray;
class LineSegment;

class QuadTreeNode;
typedef std::unique_ptr<QuadTreeNode> QuadTreeNodePtr;

class DebugRender;
typedef std::unique_ptr<DebugRender> DebugRenderPtr;

struct eBigTextureID
{
	enum Val
	{
		Landscape,
		BigTextureCount
	};
};

struct eTextureID
{
	enum Val
	{
		MainMenuBackground,
		GameOverBackground,
		ChaosLordBody,
		ChaosLordWeaponSword,
		ChaosLordWeaponBolter,
		ChaosLordWeaponPlasma,
		ChaosLordWeaponMelta,
		OrkBadrukkBody,
		OrkThrakaBody,
		OrkBoyChoppaBody1,
		OrkBoyChoppaBody2,
		OrkBoyChoppaBody3,
		OrkBoyChoppaBody4,
		OrkBoyShootaBody1,
		OrkBoyShootaBody2,
		OrkBoyShootaBody3,
		OrkBoyShootaBody4,
		OrkWarbossBody,
		OrkWarbossWeaponShoota,
		ProjectileBullet,
		ProjectilePlasma,
		BloodSplash1,
		BloodSplash2,
		BloodSplash3,
		BloodSplash4,
		BloodSplash5,
		BloodSplash6,
		TerrainOrkFortress,
		TerrainOrkWatchtower,
		TerrainOrkBuilding,
		TerrainOrkGarage,
		TerrainOrkHut,
		TextureCount
	};
};

struct eFontID
{
	enum Val
	{
		Arial,
		FontCount
	};
};

struct eStateID
{
	enum Val
	{
		None,
		MainMenu,
		Game,
		GameOver,
		Sandbox
	};
};

struct eWorldLayer
{
	enum Val
	{
		LandscapeLayer,
		GroundLayer,
		ProjectilesLayer,
		LayerCount
	};	
};

struct eSceneNodeFlags
{
	enum Val
	{
		MarkToDelete = 1 << 0
	};
};

struct eCollisionGroup
{
	enum Val
	{
		Landscape = 1 << 0,
		Player = 1 << 1,
		Monster = 1 << 2,
		Pickup = 1 << 3,
		Characters = Player | Monster,
		Dynamic = Player | Monster | Pickup,		
		Static = 1 << 4,
		Respawn = 1 << 5,
		Projectile = 1 << 6,
		BloodSplash = 1 <<7,
		All = 0xffffffff
	};
};

struct eCollisionShapeKind
{
	enum Val
	{
		AlignedBox,
		OrientedBox,
		ConvexPolygon
	};
};

}