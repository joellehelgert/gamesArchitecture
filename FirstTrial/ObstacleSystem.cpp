#include "ObstacleSystem.h"
#include "Obstacle.h"
#include "FlowField2.h"

using namespace std;
using namespace powidl;


// TODO Add required entity components to family
// e.g., FAMILY = EntityFamily::create<Pose2D, SpriteVisual>();
const EntityFamily ObstacleSystem::FAMILY = EntityFamily::create<Pose2D, Obstacle>();

ObstacleSystem::ObstacleSystem(const std::string & timelineName)
	: IteratingEntitySystem(FAMILY, FAMILY, timelineName)
{
	// Intentionally left empty
}


void ObstacleSystem::onActivation()
{
	// TODO Place initialization code here...
}

void ObstacleSystem::onDeactivation()
{
	// TODO Place cleanup code here...
}

void ObstacleSystem::processEntity(Entity & e)
{
}

void ObstacleSystem::onEntityAdded(powidl::Entity & e)
{
	shared_ptr<FlowField2> flowField = findPlum<FlowField2>();
	Pose2D pose = e.getComponent<Pose2D>();
	Obstacle obs = e.getComponent<Obstacle>();
	flowField->addObstacle(pose.pos, obs);

	
}

void ObstacleSystem::onEntityRemoved(powidl::Entity & e)
{
	shared_ptr<FlowField2> flowField = findPlum<FlowField2>();
	Pose2D pose = e.getComponent<Pose2D>();
	Obstacle obs = e.getComponent<Obstacle>();
	flowField->removeObstacle(obs);
}
