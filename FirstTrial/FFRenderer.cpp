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
	// Reset point to timeline.
	m_timeline.reset();
}

void FFRenderer::update() {
	auto& lineRenderer = usePlum<ILineRenderer2D>();
	lineRenderer.setColor(StandardColors::WHITE);

	for (int x = 0; x < m_cols; x++) {
		for (int y = 0; y < m_rows; y++) {
			float realX = mapFFXToRealX(x);
			float realY = mapFFYToRealY(y);
			Vector2 vec = m_ff->getVectorAt(realX, realY) * m_scale;

			lineRenderer.drawLine(realX, realY, realX - (vec.x * m_unitX), realY - (vec.y * m_unitY));
		}
	}

}


int FFRenderer::mapFFCoordinatesToIndex(int x, int y)
{
	return y*m_cols -1 + x;
}

int FFRenderer::mapRCoordinatesToIndex(float x, float y)
{
	float posX = round(x / m_unitX);
	float posY = round(y / m_unitY);
	int index = static_cast<int>(posY) * m_rows + static_cast<int>(posX) * m_cols;

	return index;
}

float FFRenderer::mapFFYToRealY(int y)
{
	return y * m_unitY - m_offsetY;
}

float FFRenderer::mapFFXToRealX(int x)
{
	return x * m_unitX - m_offsetX;
}


//powidl::Vector2 FFRenderer::convertIndexToCoordinates(int i)
//{
//	Real x = (i % m_cols) * m_unitX - m_offsetX;
//	Real y = int(i / m_cols) * m_unitY - m_offsetY;
//
//	return powidl::Vector2(powidl::Vector2(x, y));
//}


