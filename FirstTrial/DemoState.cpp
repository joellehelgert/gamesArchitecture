#include "DemoState.h"
#include "RecBuilder.h"
#include "GridBuilder.h"
#include "FlowField2.h"
#include "FFRenderer.h"
#include "FFMoveable.h"
#include "FFMoveableSystem.h"
#include "ObstacleSystem.h"

using namespace std;
using namespace powidl;


DemoState::DemoState(const std::string& keyPath)
	: KeyPlum(keyPath)
{
	// Intentionally left empty-
}

void DemoState::onFirstActivation()
{

	// Add child Plums here...
	addChild(usePlum<ISpriteSceneGraph2DFactory>().createSpriteSceneGraph2D());
	// Zoomability
	// addChild(std::make_shared<Camera2DControlPlum>());
	addChild(usePlum<ICamera2DManagerFactory>().createCamera2DManager());
	addChild(std::make_shared<EntityManagerPlum>());
	addChild(std::make_shared<FFMoveableSystem>());
	addChild(std::make_shared<ObstacleSystem>());
	addChild(std::make_shared<SpriteVisualSystem>());
	addChild(std::make_shared<EntityFactoryPlum>());

	

	std::shared_ptr<FlowField2> flowField = make_shared<FlowField2>(9, 9, 800, 800);
	addChild(flowField);
	addChild(make_shared<FFRenderer>(90, 90, 800, 800, flowField));
	usePlum<IMouse>().addMouseListener(this);
	usePlum<IKeyboard>().addKeyboardListener(this);
	m_playState = PlayState::setAgent;
}


void DemoState::onActivation()
{
	auto& scene = usePlum<ISpriteSceneGraph2D>();

	scene.addNode(SpriteNode2DBuilder(*this)
		.addSprite(
			RectangleSpriteBuilder(*this)
			.width(800)
			.height(800)
			.color(StandardColors::BLUE_VIOLET)
			.filled(false)
			.lineWidth(3)
			.build()
		)
		.build());


	// ---------- AGENT --------------
	std::shared_ptr<Entity> agent = std::make_shared<Entity>();
	agent->addComponent(std::make_unique<Pose2D>());
	agent->addComponent(std::make_unique<FFMoveable>());
	agent->addComponent(std::make_unique<powidl::SpriteVisual>(
		SpriteNode2DBuilder(*this)
		.addSprite(
			RectangleSpriteBuilder(*this)
			.width(20)
			.height(20)
			.color(StandardColors::YELLOW)
			.build()
		)
		.build())
	);

	usePlum<IEntityFactory>().addPrototype("agent", agent);

	// ---------- OBSTALCE --------------
	std::shared_ptr<Entity> obstacle = std::make_shared<Entity>();
	obstacle->addComponent(std::make_unique<Pose2D>());
	obstacle->addComponent(std::make_unique<Obstacle>());
	obstacle->addComponent(std::make_unique<powidl::SpriteVisual>(
		SpriteNode2DBuilder(*this)
		.addSprite(
			CircleSpriteBuilder(*this)
			.radius(60)
			.color(StandardColors::ORANGE)
			.filled(false)
			.lineWidth(5)
			.build()
		)
		.build())
	);

	obstacle->getComponent<Obstacle>().setStrength(5);
	obstacle->getComponent<Pose2D>().setPos(20, 20);
	usePlum<IEntityFactory>().addPrototype("obstacle", obstacle);
	/*usePlum<IEntityManager>().addEntity(obstacle);*/

	// ---------- TARGET --------------
	std::shared_ptr<Entity> target = std::make_shared<Entity>();
	target->addComponent(std::make_unique<Pose2D>());
	target->addComponent(std::make_unique<Obstacle>());
	target->addComponent(std::make_unique<powidl::SpriteVisual>(
		SpriteNode2DBuilder(*this)
		.addSprite(
			CircleSpriteBuilder(*this)
			.radius(30)
			.color(StandardColors::GREEN)
			.filled(false)
			.lineWidth(2)
			.build()
		)
		.build())
	);

	usePlum<IEntityFactory>().addPrototype("target", target);
	target->getComponent<Obstacle>().setStrength(5);
	target->getComponent<Obstacle>().setRepulsiveness(false);
	usePlum<IEntityManager>().addEntity(target);
}

void DemoState::onDeactivation()
{
	usePlum<IMouse>().removeMouseListener(this);
}

bool DemoState::onMouseButtonDown(int x, int y, int button) {
	string type;
	switch (m_playState) {
	case PlayState::setAgent:
		type = "agent";
		break;
	case PlayState::setObstacle:
		type = "obstacle";
		break;
	case PlayState::setTarget:
		type = "target";
		break;
	default:
		type = "agent";
	}
	auto entity = usePlum<IEntityFactory>().createEntity(type);
	auto cam = usePlum<ICamera2DManager>().getCamera();
	auto worldPoint = cam->inverseTransformPoint(x, y);

	entity->getComponent<Pose2D>().pos.set(worldPoint);

	usePlum<IEntityManager>().addEntity(entity);

	return true;
}

bool DemoState::onKeyDown(powidl::Keycode code)
{
	if (code == powidl::Keycode::K_LEFT_SHIFT) {
		m_playState = PlayState::setObstacle;
	}

	if (code == powidl::Keycode::K_LEFT_CTRL) {
		m_playState = PlayState::setTarget;
	}

	return true;
}

bool DemoState::onKeyUp(powidl::Keycode code)
{
	if (code == powidl::Keycode::K_LEFT_SHIFT || code == powidl::Keycode::K_LEFT_CTRL) {
		m_playState = PlayState::setAgent;
	}


	return true;
}
