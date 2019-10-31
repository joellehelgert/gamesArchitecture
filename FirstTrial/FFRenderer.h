#pragma once

#include <string>
#include <memory>
#include <Sge.h>

using namespace powidl;

class FFRenderer : public powidl::UpdatablePlum {
public:

	/**
	 * Constructor.
	 * 
	 * @param timelineName	the name of the timeline to use
	 */
	FFRenderer(const std::string & timelineName = powidl::ITimekeeper::DEFAULT_TIMELINE_NAME);

	std::shared_ptr<Plum> createFFRenderer();

	// Inherited via Plum
	virtual void onFirstActivation() override;
	virtual void onActivation() override;
	virtual void onDeactivation() override;
	virtual void update() override;

	// Function to convert from x/y to array index
	int convertCoordinatesToIndex(float x, float y);

	// Function to convert from array index to  x/y 
	std::shared_ptr<Vector2> convertIndexToCoordinates(int i);

private:
	/** The name of the timeline used by this Plum. */
	std::string m_timelineName;

	int getIndexFromGrid(int x, int y);

	/** The timeline used by this Plum. */
	std::shared_ptr<powidl::ITimeline> m_timeline;
	
	/**
	 * Convenient method returning the current delta time.
	 *
	 * @return the elapsed time since the last update in seconds
	 */
	powidl::Real getDeltaTime() { m_timeline->getDeltaTime(); }

	int m_rows;
	int m_cols;
	float m_width;
	float m_height;
	float m_unitX;
	float m_unitY;
	float m_offsetX;
	float m_offsetY;
	std::unique_ptr<Vector2[]> m_field;
	
	// Add additional private members here.
};

