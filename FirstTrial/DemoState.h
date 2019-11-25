#pragma once

#include <string>
#include <Sge.h>

enum class PlayState {
	setAgent,
	setObstacle,
	setTarget
};

class DemoState : public powidl::KeyPlum, public powidl::IMouseListener, public powidl::IKeyboardListener {
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
	virtual bool onKeyDown(powidl::Keycode code) override;
	virtual bool onKeyUp(powidl::Keycode code) override;

private:
	// Add private members here.
	PlayState m_playState;

};

