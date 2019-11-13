#pragma once

#include <string>
#include <Sge.h>

class DemoState : public powidl::KeyPlum, public powidl::IMouseListener {
public:

	/**
	 * Constructor.
	 * 
	 * @param keyPath	the path to the data depot
	 */
	DemoState(const std::string & keyPath = "");

	// Inherited via Plum
	virtual void onFirstActivation() override;
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual bool onMouseButtonDown(int x, int y, int button) override;

private:
	// Add private members here.

};

