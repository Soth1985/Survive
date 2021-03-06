#include <Survive/world.h>
#include <Survive/content_manager.h>
#include <Survive/gui.h>
#include <Survive/scene_nodes/static_convex_node.h>
#include <Survive/templates/static_convex_template.h>
#include <Survive/math_utils.h>
#include <Survive/debug_render.h>

#include <SFML/Graphics.hpp>

namespace Survive
{

SURVIVE_REG_TYPE(StaticConvexEntityNode, SURVIVE_TYPELIST_1(StaticEntityNode))

Type* StaticConvexEntityNode::GetType()const
{
	return TypeImpl<StaticConvexEntityNode>::Instance();
}
	
void StaticConvexEntityNode::InitFromTemplate(const Template* Tmpl)
{
	const StaticConvexTemplate* pConvexTmpl = TypeCast<StaticConvexTemplate>(Tmpl);

	if (pConvexTmpl)
	{
		m_Collision = MathUtils::GetRandomItem(pConvexTmpl->m_Shapes);
		m_Collision.SetCollisionGroup(eCollisionGroup::Static);
		GetWorld()->GetQuadTree()->AddObject(this);

		m_Shape.setPointCount(m_Collision.GetPointC());

		for (size_t Idx = 0; Idx < m_Collision.GetPointC(); ++Idx)
		{
			m_Shape.setPoint(Idx, m_Collision[Idx]);
		}

		m_Shape.setFillColor(sf::Color::Blue);
	}
	else
	{
		GetWorld()->GetContext()->GetGui()->MessageBox("Error", "Invalid static convex template type.");
	}
}

const CollisionShape* StaticConvexEntityNode::GetCollisionShape()const
{
	return &m_Collision;
}

void StaticConvexEntityNode::OnDraw(sf::RenderTarget& Target, sf::RenderStates States)const
{
	Target.draw(m_Shape, States);
	GetWorld()->GetContext()->GetDebugRender()->AddConvexPolygon(m_Collision, States.transform, 0.01f, sf::Color::Black);
}

void StaticConvexEntityNode::OnUpdate(float Dt)
{
	
}

AlignedBoxShape StaticConvexEntityNode::GetBounds()
{
	AlignedBoxShape Result;
	m_Collision.GetAlignedHull(&Result);
	return Result;
}

}