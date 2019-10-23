#include "GridBuilder.h"
#include "RecBuilder.h"

using namespace std;

GridBuilder::GridBuilder(Plum& context) : m_context(context)
{
	m_margin = 3;
}

GridBuilder& GridBuilder::setWidth(float w)
{
	m_width = w;
	return *this;
}

float GridBuilder::getWidth() const
{
	return m_width;
}

GridBuilder& GridBuilder::setMargin(int m)
{
	m_margin = m;
	return *this;
}

int GridBuilder::getMargin() const
{
	return m_margin;
}

GridBuilder& GridBuilder::setHeight(float h)
{
	m_height = h;
	return *this;
}

float GridBuilder::getHeight() const
{
	return m_height;
}

GridBuilder& GridBuilder::setRows(int rows)
{
	m_rows = rows;
	return *this;
}

int GridBuilder::getRows() const
{
	return m_rows;
}

GridBuilder& GridBuilder::setCols(int cols)
{
	m_cols = cols;
	return *this;
}

int GridBuilder::getCols() const
{
	return m_cols;
}

GridBuilder& GridBuilder::setColor(Color color)
{
	m_color = color;
	return *this;
}

const Color& GridBuilder::getColor() const
{
	return m_color;
}

shared_ptr<SpriteNode2D> GridBuilder::build() const
{
	auto gridNode = SpriteNode2DBuilder(m_context);
	float width = (m_width - m_rows * m_margin) / m_rows;
	float height = (m_height - m_cols * m_margin) / m_cols;
	float posX;
	float posY;

	RecBuilder recBuilder = RecBuilder(m_context).setHeight(height).setWidth(width).setColor(m_color);

	for (int i = 0; i < m_rows; i++) {
		posX = (i * (m_width / m_rows)) - (m_width * 0.5) + ((width +m_margin) * 0.5);
		for (int y = 0; y < m_cols; y++) {
			posY = y * (m_height / m_cols) - (m_height * 0.5) + ((height+ m_margin) * 0.5);
			gridNode.addNode(recBuilder.setPos(posX, posY).build());
		}
	}

	return gridNode.build();
}
