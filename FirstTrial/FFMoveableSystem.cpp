#include "FFMoveableSystem.h"
#include "FlowField2.h"
#include "FFMoveable.h"
#include <iostream>
#include <cstdlib>
#include "ViewsEnum.h"

#define pi 3.14159265
using namespace std;
using namespace powidl;

const EntityFamily FFMoveableSystem::FAMILY = EntityFamily::create<Pose2D, SpriteVisual, FFMoveable>();

FFMoveableSystem::FFMoveableSystem(const std::string& timelineName)
	: IteratingEntitySystem(FAMILY, FAMILY, timelineName) 
	, _BACK_VIEW_ANGLE_FACTOR(1)
	, _FRONT_VIEW_ANGLE_FACTOR(0)
	, _WIDEVIEW_RADIUS_FACTOR(0.3)
	, _LIMITEDVIEW_RADIUS_FACTOR(0.7)
	, _NARROWVIEW_RADIUS_FACTOR(1.2)
{
	_STEERINGFORCE = 1; 
	_SEPARATION_FACTOR = 1;
}


powidl::Vector2 FFMoveableSystem::calculateCohesion(powidl::Real length, powidl::Vector2 vector)
{
	float scale = (length - m_minDistance) / length;
	return vector * scale;
}

powidl::Vector2 FFMoveableSystem::calculateAlignment(powidl::Vector2 vector, powidl::Vector2 neighbour)
{
	powidl::Vector2 halfVec = vector / 2;
	powidl::Vector2 halfNeighbour = neighbour / 2;
	return halfVec + halfNeighbour;
}

powidl::Vector2 FFMoveableSystem::calculateSeperation(powidl::Real length, powidl::Vector2 vector)
{
	float scale = m_minDistance / length;
	return vector * scale * -1;
}

powidl::Vector2 FFMoveableSystem::calculateFlocking(Entity& entity, shared_ptr<FlowField2> flowField)
{
	Views view = entity.getComponent<FFMoveable>().getView();
	const std::vector< std::shared_ptr< Entity >>& entities = getEntities();
	int N;      // Number of neighbors
	Vector2 Pave;  // Average position vector
	Vector2 Vave;  // Average velocity vector
	Vector2 Fs;     // Net steering force
	Vector2 Pfs;    // Point of application of Fs
	Vector2 d, u, v, w;
	double m;
	bool InView;
	int RadiusFactor;

	Fs.x = Fs.y = 0;
	Pave.x = Pave.y = 0;
	Vave.x = Vave.y = 0;
	N = 0;
	Pfs.x = 0;
	Pfs.y = 0; // should be half of its entities length
	Pose2D pose = entity.getComponent<Pose2D>();
	for (const std::shared_ptr<Entity> e : entities) {
		Pose2D ePose = e->getComponent<Pose2D>();
		d, w = ePose.pos - pose.pos;
		if (d.x != 0 && d.y != 0) {
			InView = false;
			
			// maybe some rotation is still needed;

			if (view == WideView)
			{
				InView = ((w.y > 0) || ((w.y < 0) &&
					(fabs(w.x) >
						fabs(w.y)*
						_BACK_VIEW_ANGLE_FACTOR)));
				RadiusFactor = _WIDEVIEW_RADIUS_FACTOR;
			}

			if (view == LimitedView)
			{
				InView = (w.y > 0);
				RadiusFactor = _LIMITEDVIEW_RADIUS_FACTOR;
			}

			if (view == NarrowView)
			{
				InView = (((w.y > 0) && (fabs(w.x) <
					fabs(w.y) *
					_FRONT_VIEW_ANGLE_FACTOR)));
				RadiusFactor = _NARROWVIEW_RADIUS_FACTOR;
			}

			if (InView) {
				if (d.length() <= (pose.pos.length() *
					RadiusFactor))
				{
					Pave += ePose.pos;
					Vave += ePose.pos;
					N++;
				}

				// Seperation Rule
				if (d.length() <=
					(pose.pos.length() * _SEPARATION_FACTOR))
				{
					if (w.x < 0) m = 1;
					if (w.x > 0) m = -1;
					Fs.x += m * _STEERINGFORCE *
						(pose.pos.length() *
							_SEPARATION_FACTOR) /
						d.length();
				}
			}

			// Cohesion Rule:
			if (N > 0)
			{
				Pave = Pave / N;
				v = pose.pos;
				v.normalize();
				u = Pave - pose.pos;
				u.normalize();
				//w = VRotate2D(-Units[i].fOrientation, u);
			
				if (w.x < 0) m = -1;
				if (w.x > 0) m = 1;
				if (fabs(v.dot(u)) < 1)
					Fs.x += m * _STEERINGFORCE * acos(v.dot(u)) / pi;
			}

			// Alignment Rule:
			if (N > 0)
			{
				Vave = Vave / N;
				v = pose.pos;
				v.normalize();
				u = Pave - pose.pos;
				u.normalize();
				//w = VRotate2D(-Units[i].fOrientation, u);

				if (w.x < 0) m = -1;
				if (w.x > 0) m = 1;
				if (fabs(v.dot(u)) < 1)
					Fs.x += m * _STEERINGFORCE * acos(v.dot(u)) / pi;
			}
			
		}
	}

	return Fs;

}



void FFMoveableSystem::onActivation(){
	m_radius = 170;
	m_minDistance = 2;
}

void FFMoveableSystem::onDeactivation(){}

void FFMoveableSystem::processEntity(Entity& e)
{
	shared_ptr<FlowField2> flowField = findPlum<FlowField2>();
	auto& pose = e.getComponent<Pose2D>();

	powidl::Vector2 position = pose.pos;
	powidl::Vector2 flocking = calculateFlocking(e, flowField);
	
	Vector2 vector = flowField->getVectorAt(position);
	
    vector.add(flocking);
	Real delta = getDeltaTime() * 2;
	powidl::Vector2 newPosition = Vector2(position.x + (vector.getX() * delta), position.y + (vector.getY() * delta));
	pose.setPos(newPosition);
	/*float angle = atan2(newPosition.y, newPosition.x);
	pose.setAngle(angle);*/

}


void FFMoveableSystem::onEntityAdded(powidl::Entity& e){}

void FFMoveableSystem::onEntityRemoved(powidl::Entity& e)
{}


