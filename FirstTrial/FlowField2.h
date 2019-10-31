#pragma once

#include <string>
#include <Sge.h>

using namespace std;

class FlowField2 : public powidl::Plum {
public:

	/**
	 * Constructor.
	 * 
	 * @param keyPath	the path to the data depot
	 */
	FlowField2();

	// shared_ptr<Vector2[]> getData();
	std::shared_ptr<Plum> createFlowField();
	void drawFF();

	// Inherited via Plum
	virtual void onFirstActivation() override;
	virtual void onActivation() override;
	virtual void onDeactivation() override;

private:
	// Add private members here.
	friend class FlowFieldRenderer;

	vector<powidl::Vector2> m_data;
	int m_rows;
	int m_cols;
};

