#pragma once

#include "FlowField2.h"
#include <Sge.h>

class FFMoveableSystem final : public powidl::IteratingEntitySystem {
public:

	// Constructor
	FFMoveableSystem(const std::string & timelineName = powidl::ITimekeeper::DEFAULT_TIMELINE_NAME);
	
private:
	/** The family of entities this system processes. */
	static const powidl::EntityFamily FAMILY;
	int m_radius;
	int m_minDistance;
	const float _BACK_VIEW_ANGLE_FACTOR;
	const float _FRONT_VIEW_ANGLE_FACTOR;
	const float _WIDEVIEW_RADIUS_FACTOR;
	const float _LIMITEDVIEW_RADIUS_FACTOR;
	const float _NARROWVIEW_RADIUS_FACTOR;
	float _STEERINGFORCE;
	float _SEPARATION_FACTOR;


	powidl::Vector2 calculateCohesion(powidl::Real length, powidl::Vector2 vector);
	powidl::Vector2 calculateAlignment(powidl::Vector2 vector, powidl::Vector2 neighbour);
	powidl::Vector2 calculateSeperation(powidl::Real length, powidl::Vector2 vector);
	powidl::Vector2 calculateFlocking(powidl::Entity& entity, shared_ptr<FlowField2> flowField);
	
	// Inherited via IteratingEntitySystem
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual void processEntity(powidl::Entity & e);
	virtual void onEntityAdded(powidl::Entity & e) override;
	virtual void onEntityRemoved(powidl::Entity & e) override;

};

