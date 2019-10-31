#include "FFRenderer.h"
#include "GridBuilder.h"
#include <math.h>  

using namespace std;
using namespace powidl;

FFRenderer::FFRenderer(const std::string& timelineName)
	: m_timelineName(timelineName)
{
	// Intentionally left empty
}

std::shared_ptr<Plum> FFRenderer::createFFRenderer()
{

	return make_shared<FFRenderer>();
}

void FFRenderer::onFirstActivation()
{
	// TOTO: Add child Plums here...
	addChild(usePlum<ISpriteSceneGraph2DFactory>().createSpriteSceneGraph2D());
	addChild(usePlum<ICamera2DManagerFactory>().createCamera2DManager());
	addChild(usePlum<ILineRenderer2DFactory>().createLineRenderer());

	m_rows = 20;
	m_cols = 20;
	m_width = 800;
	m_height = 800;
	m_offsetX = (m_width / 2);
	m_offsetY = m_height / 2;

	m_field = std::make_unique<Vector2[]>(m_rows * m_cols); 
	// TODO unit if uneven rows and cols? origin than devides one 'unit'
	m_unitX = m_width / m_cols;
	m_unitY = m_height / m_rows;

	for (int i = 0; i < m_cols * m_rows; i++) {
		m_field[i] = powidl::Vector2(1, 1);
	}

}

void FFRenderer::onActivation()
{
	// Retrieve timeline used by this Plum
	m_timeline = usePlum<ITimekeeper>().getOrCreateTimeline(m_timelineName);


	// TOTO: Place initialization code here...
	auto& scene = usePlum<ISpriteSceneGraph2D>();
	scene.addNode(GridBuilder(*this).setCols(m_cols).setRows(m_rows).setWidth(m_width).setHeight(m_height).setColor(StandardColors::DARK_RED).build());
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
		for (int y = 0; y <m_rows; y++) {
			Vector2 vec = m_field[getIndexFromGrid(x, y)];
			// if uneven field minus half the unit ? negative different than positive..
			Real posX = x * m_unitX - m_offsetX;
			Real posY = (y + 1) * m_unitY - m_offsetY;	
			
			lineRenderer.drawLine(posX, posY, posX+ (vec.x * m_unitX), posY-(vec.y* m_unitY));
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
	int index = posY * m_rows + posX * m_cols;

	return index;
}

std::shared_ptr<Vector2> FFRenderer::convertIndexToCoordinates(int i)
{
	Real x = i * m_unitX;
	Real y = i * m_unitY;

	return shared_ptr<Vector2>(new Vector2(x,y));
}


