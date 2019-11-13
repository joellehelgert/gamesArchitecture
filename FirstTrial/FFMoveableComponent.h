#pragma once

#include <Sge.h>

class FFMoveableComponent final : public powidl::Component {
public:
	powidl::Real speed;
	powidl::Real duration;

	/** Constructor */
	FFMoveableComponent()
	{}

	// Inherited via Component
	virtual std::unique_ptr<powidl::Component> clone() override;
};