#include "FFRenderer.h"
#include "FlowField2.h"
#include "GridBuilder.h"
#include <math.h>  

using namespace std;
using namespace powidl;

FFRenderer::FFRenderer()
{
	// TODO Default flowfield with default render options
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
	// TOTO: Add child Plums here...
	addChild(usePlum<ISpriteSceneGraph2DFactory>().createSpriteSceneGraph2D());
	addChild(usePlum<ICamera2DManagerFactory>().createCamera2DManager());
	addChild(usePlum<ILineRenderer2DFactory>().createLineRenderer());


	m_offsetX = (m_width / 2);
	m_offsetY = m_height / 2;

	m_field = std::make_unique<Vector2[]>(m_rows * m_cols);
	m_unitX = m_width / (m_cols-1);
	m_unitY = m_height / (m_rows-1);
	m_scale = 0.10f;


	for (int i = 0; i < m_rows * m_cols; i++) {
		powidl::Vector2 vec = convertIndexToCoordinates(i);
		if (vec.y > 250) {
			m_field[i] = m_ff->getVectorAt(vec);
		}
		m_field[i] = m_ff->getVectorAt(vec);
		
	}

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
			Vector2 vec = m_field[getIndexFromGrid(x, y)] * m_scale;
			Real posX = x * m_unitX - m_offsetX;
			Real posY = y * m_unitY - m_offsetY;

			lineRenderer.drawLine(posX, posY, posX + (vec.x * m_unitX), posY - (vec.y * m_unitY));
		}
	}

}

int FFRenderer::getIndexFromGrid(int x, int y) {
	return m_cols * y + x;
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


