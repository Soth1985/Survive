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

class Application;

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

class LandscapeNode;
typedef std::unique_ptr<LandscapeNode> LandscapeNodePtr;

class World;
typedef std::unique_ptr<World> WorldPtr;

struct eBigTextureID
{
	enum Val
	{
		Landscape
	};
};

struct eTextureID
{
	enum Val
	{
		MainMenuBackground
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

}