#pragma once
#include <Sge.h>

using namespace powidl;
using namespace std;

class FlowField
{
public:
	// TODO should only be available for friends
	shared_ptr<Vector2[]> getData();

private:

	friend class FlowFieldRenderer;

};

