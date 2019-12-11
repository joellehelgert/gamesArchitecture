#pragma once

#include <string>
<<<<<<< HEAD
#include <Sge.h>
#include "FlowField2.h"
=======
#include <memory>
#include <Sge.h>
>>>>>>> master

using namespace powidl;

class FFRenderer : public powidl::UpdatablePlum {
public:
<<<<<<< HEAD
	FFRenderer();
=======

>>>>>>> master
	/**
	 * Constructor.
	 * 
	 * @param timelineName	the name of the timeline to use
	 */
<<<<<<< HEAD
	FFRenderer(int rows, int cols, float width, float height, std::shared_ptr<FlowField2> ff);
=======
	FFRenderer(const std::string & timelineName = powidl::ITimekeeper::DEFAULT_TIMELINE_NAME);

	std::shared_ptr<Plum> createFFRenderer();
>>>>>>> master

	// Inherited via Plum
	virtual void onFirstActivation() override;
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual void update() override;

<<<<<<< HEAD
	// Function to convert from x/y to array index


=======
>>>>>>> master
private:
	/** The name of the timeline used by this Plum. */
	std::string m_timelineName;

<<<<<<< HEAD
	int mapFFCoordinatesToIndex(int x, int y);
	int mapRCoordinatesToIndex(float x, float y);
	float mapFFYToRealY(int y);
	float mapFFXToRealX(int x);

	std::shared_ptr<powidl::ITimeline> m_timeline;
	powidl::Real getDeltaTime() { m_timeline->getDeltaTime(); }

	int m_rows;
	int m_cols;
	std::shared_ptr<FlowField2> m_ff;
	float m_width;
	float m_height;
	float m_unitX;
	float m_unitY;
	float m_offsetX;
	float m_offsetY;
	float m_scale;
	std::unique_ptr<Vector2[]> m_field;
=======
	/** The timeline used by this Plum. */
	std::shared_ptr<powidl::ITimeline> m_timeline;
	
	/**
	 * Convenient method returning the current delta time.
	 *
	 * @return the elapsed time since the last update in seconds
	 */
	powidl::Real getDeltaTime() { m_timeline->getDeltaTime(); }
>>>>>>> master
	
	// Add additional private members here.
};

