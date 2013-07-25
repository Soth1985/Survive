Survive
=======

Binaries are located in project/bin/vc10_32 both release and debug

Controls: 

WSAD to move character.
Left click to shoot.
Right click to use melee weapon.
F2 to toggle debug rendering layer.

AI:

Simply chase the player and shoot him if the monster is in frustrum.

Pickups:

Health pack only.

Code guide:

The game logic is updated in World::Update method, world structure is based on scene graph concept, quad tree is used for rendering and collision requests. 

project/code/collision contains collision detection algorithms, aligned box oriented box and convex polygons are supported
project/code/scene_nodes contains the scene nodes logic
project/code/templates contains the templates which describe nodes properties, TemplateManager creates default ones.
