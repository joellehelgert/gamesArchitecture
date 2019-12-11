#pragma once

#include <Sge.h>

class Obstacle final : public powidl::Component {
public:
	float m_strength;
	bool m_repulsive;
	float m_radius;

	/** Constructor */
	Obstacle();

	Obstacle(float strength, bool repulsive, float radius);

	float getRadius();
	int getRepulsiveness();
	float getStrength();

	void setRadius(float r);
	void setRepulsiveness(bool rep);
	void setStrength(float s);

	// Inherited via Component
	virtual std::unique_ptr<powidl::Component> clone() override;

	void printObstalce();
};