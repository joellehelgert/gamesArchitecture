#include "DemoState.h"
#include "RecBuilder.h"
#include "GridBuilder.h"
#include "FFRenderer.h"

using namespace std;
using namespace powidl;

DemoState::DemoState(const std::string & keyPath)
	: KeyPlum(keyPath)
{
	// Intentionally left empty
}

void DemoState::onFirstActivation()
{
	// Add child Plums here...
	addChild(usePlum<ISpriteSceneGraph2DFactory>().createSpriteSceneGraph2D());
	addChild(usePlum<ICamera2DManagerFactory>().createCamera2DManager());
	addChild(usePlum<FFRenderer>().createFFRenderer());
}


void DemoState::onActivation()
{
	auto& scene = usePlum<ISpriteSceneGraph2D>();
	// Place initialization code here...
	
	// scene.addNode(RecBuilder(*this).setHeight(200).setWidth(200).setColor(StandardColors::CORAL).setPos(0, 0).build());
	// scene.addNode(GridBuilder(*this).setCols(10).setRows(10).setWidth(200).setHeight(200).setColor(StandardColors::BISQUE).build());
}

void DemoState::onDeactivation()
{
	// Place cleanup code here...
}
