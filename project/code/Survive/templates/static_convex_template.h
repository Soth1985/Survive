#pragma once

#include <Survive/templates/static_object_template.h>
#include <Survive/collision/convex_polygon_shape.h>

namespace Survive
{

SURVIVE_DECL_TYPE(Survive::StaticConvexTemplate)

class StaticConvexTemplate : public StaticObjectTemplate
{
public:

	virtual Type* GetType()const;

	typedef std::pair<ConvexPolygonShape, float> ShapePair;
	std::vector< ShapePair > m_Shapes;
};

}