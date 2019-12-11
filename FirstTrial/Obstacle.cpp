#include "Obstacle.h"

using namespace std;
using namespace powidl;

Obstacle::Obstacle()
{
	m_strength = 0.5;
	m_repulsive = true;
	m_radius = 40;
}

Obstacle::Obstacle(float strength, bool repulsive, float radius)
{
	m_strength = strength;
	m_repulsive = repulsive;
	m_radius = radius;

}

float Obstacle::getRadius()
{
	return m_radius;
}

int Obstacle::getRepulsiveness()
{
	return m_repulsive ? -1 : 1;
}

float Obstacle::getStrength()
{
	return m_strength;
}

void Obstacle::setRadius(float r)
{
	m_radius = r;
}

void Obstacle::setRepulsiveness(bool rep)
{
	m_repulsive = rep;
}

void Obstacle::setStrength(float s)
{
	m_strength = s;
}



std::unique_ptr<powidl::Component> Obstacle::clone()
{
	// Use copy-constructor to create clone of this component.
	return std::make_unique<Obstacle>(*this);
}

void Obstacle::printObstalce()
{
}
