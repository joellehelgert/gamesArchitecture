#pragma once

#include <Sge.h>

class Obstacle final : public powidl::Component {
public:
	powidl::Real m_strength;
	bool m_repulsive;
	float m_radius;

	/** Constructor */
	Obstacle();

	Obstacle(powidl::Real strength, bool repulsive, float radius);

	float getRadius();
	int getRepulsiveness();
	powidl::Real getStrength();

	void setRadius(float r);
	void setRepulsiveness(bool rep);
	void setStrength(powidl::Real s);

	// Inherited via Component
	virtual std::unique_ptr<powidl::Component> clone() override;

	void printObstalce();
};