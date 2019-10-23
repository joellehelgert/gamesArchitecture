#include "RecBuilder.h"
#include "sge.h"

using namespace std;
using namespace powidl;

RecBuilder::RecBuilder(Plum& context)
	:m_context(context) // reference is not allowed to be null so it needs to be initialized before the program starts
{
}

RecBuilder& RecBuilder::setColor(const Color& c) {
	m_color = c;
	return *this;
}

const Color& RecBuilder::getColor() const {
	return m_color;
}

RecBuilder& RecBuilder::setWidth(float w) {
	m_width = w;
	return *this;
}

float RecBuilder::getWidth() const {
	return m_width;
}

RecBuilder& RecBuilder::setHeight(float h) {
	m_height = h;
	return *this;
}

float RecBuilder::getHeight() const {
	return m_height;
}

RecBuilder& RecBuilder::setPos(float x, float y) {
	m_pos.setX(x).setY(y);
	return *this;
}

const powidl::Vector2& RecBuilder::getPos() const {
	return m_pos;
}

shared_ptr<SpriteNode2D> RecBuilder::build() const {
	shared_ptr<SpriteNode2D> recSprite = SpriteNode2DBuilder(m_context).position(m_pos).addSprite(
		RectangleSpriteBuilder(m_context)
		.width(m_width)
		.height(m_height)
		.color(m_color)
		.build()

	).build();

	return recSprite;
}

