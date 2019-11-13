#pragma once

#include <Sge.h>

class FFMoveableSystem final : public powidl::IteratingEntitySystem {
public:

	// Constructor
	FFMoveableSystem(const std::string & timelineName = powidl::ITimekeeper::DEFAULT_TIMELINE_NAME);
	
private:
	/** The family of entities this system processes. */
	static const powidl::EntityFamily FAMILY;
	
	// Inherited via IteratingEntitySystem
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual void processEntity(powidl::Entity & e);
	virtual void onEntityAdded(powidl::Entity & e) override;
	virtual void onEntityRemoved(powidl::Entity & e) override;

};

