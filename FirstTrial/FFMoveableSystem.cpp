#include "FFMoveableSystem.h"
#include "FlowField2.h"

using namespace std;
using namespace powidl;


// TODO Add required entity components to family
// e.g., FAMILY = EntityFamily::create<Pose2D, SpriteVisual>(); 
// sprite visual because i do not want to select all elements with pose2d, should be changed :D
const EntityFamily FFMoveableSystem::FAMILY = EntityFamily::create<Pose2D, SpriteVisual>();

FFMoveableSystem::FFMoveableSystem(const std::string& timelineName)
	: IteratingEntitySystem(FAMILY, FAMILY, timelineName)
{
}


void FFMoveableSystem::onActivation()
{
}

void FFMoveableSystem::onDeactivation()
{
	// TODO Place cleanup code here...
}

void FFMoveableSystem::processEntity(Entity& e)
{
	shared_ptr<FlowField2> flowField = findPlum<FlowField2>();
	auto& pose = e.getComponent<Pose2D>();

	powidl::Vector2 position = pose.pos;
	Vector2 vector = flowField->getVectorAt(position);
	Real delta = getDeltaTime() * 2;
	pose.setPos(position.x + (vector.getX() * delta), position.y + (vector.getY() * delta));
}


void FFMoveableSystem::onEntityAdded(powidl::Entity& e)
{
	// TODO Add entity initialization code
}

void FFMoveableSystem::onEntityRemoved(powidl::Entity& e)
{
	// TODO Add entity cleanup code
}
