#include "DemoState.h"
#include "RecBuilder.h"
#include "GridBuilder.h"
#include "FlowField2.h"
#include "FFRenderer.h"
#include "FFMoveableComponent.h"
#include "FFMoveableSystem.h"

using namespace std;
using namespace powidl;


DemoState::DemoState(const std::string& keyPath)
	: KeyPlum(keyPath)
{
	// Intentionally left empty
}

void DemoState::onFirstActivation()
{
	// Add child Plums here...
	addChild(usePlum<ISpriteSceneGraph2DFactory>().createSpriteSceneGraph2D());
	addChild(usePlum<ICamera2DManagerFactory>().createCamera2DManager());
	addChild(std::make_shared<EntityManagerPlum>());
	addChild(std::make_shared<FFMoveableSystem>());
	addChild(std::make_shared<SpriteVisualSystem>());
	addChild(std::make_shared<EntityFactoryPlum>());


	std::shared_ptr<FlowField2> flowField = make_shared<FlowField2>(40, 40, 1000, 1000);
	addChild(flowField);
	addChild(make_shared<FFRenderer>(50, 50, 2000, 2000, flowField));
	usePlum<IMouse>().addMouseListener(this);
}


void DemoState::onActivation()
{
	auto& scene = usePlum<ISpriteSceneGraph2D>();

	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->addComponent(std::make_unique<Pose2D>());
	entity->addComponent(std::make_unique<powidl::SpriteVisual>(
		SpriteNode2DBuilder(*this)
		.addSprite(
			RectangleSpriteBuilder(*this)
			.width(20)
			.height(20)
			.color(StandardColors::ORANGE)
			.build()
		)
		.build())
	);

	usePlum<IEntityFactory>().addPrototype("agent1", entity);
}

void DemoState::onDeactivation()
{
	usePlum<IMouse>().removeMouseListener(this);
}

bool DemoState::onMouseButtonDown(int x, int y, int button) {
	auto entity = usePlum<IEntityFactory>().createEntity("agent1");
	auto cam = usePlum<ICamera2DManager>().getCamera();
	auto worldPoint = cam->inverseTransformPoint(x, y);

	entity->getComponent<Pose2D>().pos.set(worldPoint);

	usePlum<IEntityManager>().addEntity(entity);

	return true;
}
