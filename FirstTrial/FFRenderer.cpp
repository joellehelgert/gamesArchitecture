#include "FFRenderer.h"
#include "GridBuilder.h"

using namespace std;
using namespace powidl;

Vector2* m_field;

FFRenderer::FFRenderer(const std::string& timelineName)
	: m_timelineName(timelineName)
{
	// Intentionally left empty
	m_field = new Vector2[20];
	
	for (int i = 0; i < 20; i++) {
		m_field[i] = Vector2(1,1);
	}
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

}

void FFRenderer::onActivation()
{
	// Retrieve timeline used by this Plum
	m_timeline = usePlum<ITimekeeper>().getOrCreateTimeline(m_timelineName);

	// TOTO: Place initialization code here...
	auto& scene = usePlum<ISpriteSceneGraph2D>();
	scene.addNode(GridBuilder(*this).setCols(20).setRows(20).setWidth(800).setHeight(800).setColor(StandardColors::BISQUE).build());

}

void FFRenderer::onDeactivation()
{
	// TOTO: Place cleanup code here...

	// Reset point to timeline.
	m_timeline.reset();
}

void FFRenderer::update() {
	auto& lineRenderer = usePlum<ILineRenderer2D>();
	for (Real i = 0; i > m_field->length(); i++) {
		lineRenderer.drawLine(i, i, 50, 50);
	}
}

