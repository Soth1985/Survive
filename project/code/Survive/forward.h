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
class CharacterEntityNode;
class MonsterEntityNode;
class PickupEntityNode;
class PlayerEntityNode;
class LandscapeNode;
class RespawnNode;

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
		ChaosLordBody,
		ChaosLordSword,
		ChaosLordBolter,
		ChaosLordPlasma,
		ChaosLordMelta,
		TextureCount
	};
};

struct eStateID
{
	enum Val
	{
		None,
		MainMenu,
		Game,
		Sandbox
	};
};

struct eWorldLayer
{
	enum Val
	{
		LandscapeLayer,
		GroundLayer,
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

}