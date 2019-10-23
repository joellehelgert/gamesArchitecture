#pragma once
#include "Sge.h"

class RecBuilder
{
public:
	// Constructor.
	RecBuilder(powidl::Plum& context);

	// Color attribute of rectangles to build.
	RecBuilder& setColor(const powidl::Color& c);
	const powidl::Color& getColor() const;

	// Dimension of rectangles to build.
	RecBuilder& setWidth(float w);
	float getWidth() const;
	RecBuilder& setHeight(float h);
	float getHeight() const;

	// Position of rectangle to build.
	RecBuilder& setPos(float x, float y);

	const powidl::Vector2& getPos() const;

	RecBuilder& setPos(const powidl::Vector2& p) { // TODO ASK!
		return setPos(p.x, p.y);
	}
	
	// Actually builds the 'rectangle' node.
	std::shared_ptr<powidl::SpriteNode2D> build() const;

private:
	/** The context used to retrieve services etc. */
	powidl::Plum& m_context;

	/** The current position where to create rectangles. */
	powidl::Vector2 m_pos;

	/** The current width of rectangles to create. */
	float m_width;

	/** The current height of rectangles to create. */
	float m_height;

	/** The color of the rectangles. */
	powidl::Color m_color;
};

