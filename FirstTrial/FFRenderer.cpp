#include "FFRenderer.h"
#include "FlowField2.h"
#include "GridBuilder.h"
#include <math.h>  

using namespace std;
using namespace powidl;

FFRenderer::FFRenderer()
{
}


FFRenderer::FFRenderer(int rows, int cols, float width, float height, std::shared_ptr<FlowField2> ff)
{
	m_rows = rows;
	m_cols = cols;
	m_width = width;
	m_height = height;
	m_ff = ff;
}


void FFRenderer::onFirstActivation()
{
	addChild(usePlum<ILineRenderer2DFactory>().createLineRenderer());


	m_offsetX = (m_width / 2);
	m_offsetY = m_height / 2;

	m_unitX = m_width / (m_cols-1);
	m_unitY = m_height / (m_rows-1);
	m_scale = 0.10f;

}

void FFRenderer::onActivation()
{
	// Retrieve timeline used by this Plum
	m_timeline = usePlum<ITimekeeper>().getOrCreateTimeline(m_timelineName);

	auto& scene = usePlum<ISpriteSceneGraph2D>();
	//scene.addNode(GridBuilder(*this).setCols(m_cols-1).setRows(m_rows-1).setWidth(m_width).setHeight(m_height).setColor(StandardColors::DARK_RED).build());
}

void FFRenderer::onDeactivation()
{
	// TOTO: Place cleanup code here...

	// Reset point to timeline.
	m_timeline.reset();
}

void FFRenderer::update() {
	auto& lineRenderer = usePlum<ILineRenderer2D>();
	lineRenderer.setColor(StandardColors::WHITE);

	for (int x = 0; x < m_cols; x++) {
		for (int y = 0; y < m_rows; y++) {
			int index = mapFFCoordinatesToIndex(x, y);
			Vector2 RWCoor = convertIndexToCoordinates(index);
			Vector2 vec = m_ff->getVectorAt(RWCoor) * m_scale;
			Real posX = x * m_unitX - m_offsetX;
			Real posY = y * m_unitY - m_offsetY;

			lineRenderer.drawLine(posX, posY, posX - (vec.x * m_unitX), posY - (vec.y * m_unitY));
		}
	}

}

int FFRenderer::getIndexFromGrid(int x, int y) {
	return m_cols * y + x;
}

int FFRenderer::mapFFCoordinatesToIndex(int x, int y)
{
	return y*m_cols -1 + x;
}

int FFRenderer::convertCoordinatesToIndex(float x, float y)
{
	float posX = round(x / m_unitX);
	float posY = round(y / m_unitY);
	int index = static_cast<int>(posY) * m_rows + static_cast<int>(posX) * m_cols;

	return index;
}


powidl::Vector2 FFRenderer::convertIndexToCoordinates(int i)
{
	Real x = (i % m_cols) * m_unitX - m_offsetX;
	Real y = int(i / m_cols) * m_unitY - m_offsetY;

	return powidl::Vector2(powidl::Vector2(x, y));
}


