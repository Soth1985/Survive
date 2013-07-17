#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <array>

namespace sf
{

class RenderWindow;
class Transform;
class Image;
class Sprite;
class Texture;
class RenderTarget;
class RenderStates;

}

namespace Survive
{

class Application;

class BigTexture;

class BigSprite;

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

	};
};

}