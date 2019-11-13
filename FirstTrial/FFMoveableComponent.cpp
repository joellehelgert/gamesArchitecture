#include "FFMoveableComponent.h"

using namespace std;
using namespace powidl;

std::unique_ptr<powidl::Component> FFMoveableComponent::clone()
{
	// Use copy-constructor to create clone of this component.
	return std::make_unique<FFMoveableComponent>(*this);
}
