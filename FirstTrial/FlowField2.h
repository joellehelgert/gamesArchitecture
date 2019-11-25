#pragma once

#include <string>
#include <Sge.h>
#include "Obstacle.h"

using namespace std;

class FlowField2 : public powidl::Plum {
public:
	FlowField2();
	FlowField2(int rows, int cols, float width, float height);
	
	powidl::Vector2 getVectorAt(float x, float y);
	powidl::Vector2 getVectorAt(powidl::Vector2 vec) {
		return getVectorAt(vec.x, vec.y);
	};

	void addObstacle(powidl::Vector2 pos, Obstacle obstacle);

	void removeObstacle(Obstacle obstacle);

	// Inherited via Plum
	virtual void onFirstActivation() override;
	virtual void onActivation() override;
	virtual void onDeactivation() override;

private:
	powidl::Vector2 mapIndexToCoordinates(int i);
	int mapFFCoordinatesToIndex(int x, int y);
	friend class FlowFieldRenderer;
	float mapRealYToFF_Y(float y);
	float mapRealXToFF_X(float x);

	std::shared_ptr<powidl::Vector2[]> m_data;
	int m_rows;
	int m_cols;
	float m_width;
	float m_height;
	float m_unitX;
	float m_unitY;
	float m_offsetX;
	float m_offsetY;
};

