#pragma once

#include <Sge.h>

class FFMoveable final : public powidl::Component {
public:
	// TODO: add component data members

	/** Constructor */
	FFMoveable()
	{
		// Intentionally left empty
	}

	// Use custom copy-constructor if necessary (deep copy)
	/** Copy-Constructor */
	// FFMoveable(const FFMoveable & o)
	// {
	//		// TODO copy or deep copy data
	// }

	// Inherited via Component
	virtual std::unique_ptr<powidl::Component> clone() override;
};