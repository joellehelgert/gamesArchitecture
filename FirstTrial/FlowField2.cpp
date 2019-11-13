#include "FlowField2.h"
#include "FFRenderer.h"

using namespace std;
using namespace powidl;

static Real randommizer() {
	return Real(rand() % 21 + (-10));
}


FlowField2::FlowField2()
{
	m_rows = 20;
	m_cols = 20;
	m_width = 800;
	m_height = 800;
	m_data = std::make_unique<Vector2[]>(m_rows * m_cols);

}

FlowField2::FlowField2(int rows, int cols, float width, float height)
{
	m_rows = rows;
	m_cols = cols;
	m_width = width;
	m_height = height;
	m_data = std::make_unique<Vector2[]>(m_rows * m_cols);

}

void FlowField2::onFirstActivation()
{

	m_offsetX = m_width / 2;
	m_offsetY = m_height / 2;
	m_unitX = m_width / (m_cols - 1);
	m_unitY = m_height / (m_rows - 1);

	for (int i = 0; i < m_rows * m_cols; i++) {
		Real randomX = randommizer();
		Real randomY = randommizer();
		m_data[i] = powidl::Vector2(randomX, randomY);
	}
}

void FlowField2::onActivation()
{
}


powidl::Vector2 FlowField2::getVectorAt(float x, float y)
{
	float vectorsX = mapRealXToFF_X(x);
	float vectorsY = mapRealYToFF_Y(y);
	int left = static_cast<int>(floor(vectorsX));
	int right = left + 1;
	int top = static_cast<int>(floor(vectorsY));
	int bottom = top + 1;

	Vector2 leftTop = m_data[mapCoordinatesToIndex(left, top)];
	Vector2 leftBottom = m_data[mapCoordinatesToIndex(left, bottom)];
	Vector2 rightTop = m_data[mapCoordinatesToIndex(right, top)];
	Vector2 rightBottom = m_data[mapCoordinatesToIndex(right, bottom)];

	float tx = right - vectorsX;
	float ty = bottom - vectorsY;

	powidl::Vector2 r1 = (tx * leftTop) + (1 - tx) * rightTop;
	powidl::Vector2 r2 = (tx * leftBottom) + (1 - tx) * rightBottom;

	return ty * r1 + (1 - ty) * r2;;
}


int FlowField2::mapCoordinatesToIndex(int x, int y) {
	int corrigatedX = x;
	if (x < 0) {
		corrigatedX = 0;
	}

	if (x > m_cols - 1) {
		corrigatedX = m_cols - 1;
	}

	int corrigatedY = y;
	if (y < 0) {
		corrigatedY = 0;
	}

	if (y > m_rows - 1) {
		corrigatedY = m_rows - 1;
	}

	return m_cols * corrigatedY + corrigatedX;
}

float FlowField2::mapRealYToFF_Y(float y)
{
	return (y + m_offsetY) / m_unitY;
}

float FlowField2::mapRealXToFF_X(float x)
{
	return (x + m_offsetX) / m_unitX;
}

powidl::Vector2 FlowField2::convertIndexToCoordinates(int i)
{
	Real x = (i % m_cols) * m_unitX - m_width / 2;
	Real y = int((i + m_cols - 1) / m_cols) * m_unitY - m_height / 2;

	return powidl::Vector2(x, y);
}

void FlowField2::onDeactivation()
{
}