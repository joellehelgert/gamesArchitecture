#include "FFMoveable.h"

using namespace std;
using namespace powidl;

std::unique_ptr<powidl::Component> FFMoveable::clone()
{
	// Use copy-constructor to create clone of this component.
	return std::make_unique<FFMoveable>(*this);
}
