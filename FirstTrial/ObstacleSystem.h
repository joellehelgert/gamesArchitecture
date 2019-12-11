#pragma once

#include <Sge.h>

class ObstacleSystem final : public powidl::IteratingEntitySystem {
public:

	// Constructor
	ObstacleSystem(const std::string & timelineName = powidl::ITimekeeper::DEFAULT_TIMELINE_NAME);
	
private:
	// only helper
	/** The family of entities this system processes. */
	static const powidl::EntityFamily FAMILY;
	
	// Inherited via IteratingEntitySystem
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual void processEntity(powidl::Entity & e);
	virtual void onEntityAdded(powidl::Entity & e) override;
	virtual void onEntityRemoved(powidl::Entity & e) override;

};

