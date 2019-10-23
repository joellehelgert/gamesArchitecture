#pragma once
#include "Sge.h"

using namespace powidl;

class GridBuilder
{
private:
	float m_width;
	float m_height;
	int m_rows;
	int m_cols;
	int m_margin;
	Color m_color;
	Plum& m_context;

	
public:
	GridBuilder(Plum& context);

	GridBuilder& setWidth(float w);
	float getWidth() const;

	GridBuilder& setMargin(int m);
	int getMargin() const;

	GridBuilder& setHeight(float h);
	float getHeight() const;

	GridBuilder& setRows(int rows);
	int getRows() const;

	GridBuilder& setCols(int cols);
	int getCols() const;

	GridBuilder& setColor(Color color);
	const Color& getColor() const;

	std::shared_ptr<SpriteNode2D> build() const;


};

