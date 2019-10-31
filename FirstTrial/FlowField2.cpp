#include "FlowField2.h"
#include "FFRenderer.h"

using namespace std;
using namespace powidl;


FlowField2::FlowField2()
{
	// Intentionally left empty

}

void FlowField2::onFirstActivation()
{
	// Add child Plums here...
	m_cols = 20;
	m_rows = 20;

	for (int i = 0; i < m_rows * m_cols; i++) {
		Real randomX = rand() % 21 + (-10);
		Real randomY = rand() % 21 + (-10);
		m_data.push_back((new Vector2(randomX, randomY))->normalize());
	}

	addChild(usePlum<FFRenderer>().createFFRenderer());

}

std::shared_ptr<Plum> FlowField2::createFlowField()
{
	return make_shared<FlowField2>();
}


void FlowField2::onActivation()
{
	// Place initialization code here...
}

void FlowField2::onDeactivation()
{
	// Place cleanup code here...
}
