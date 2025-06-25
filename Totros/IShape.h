#pragma once
#include "Position.h"
#include <vector>
class IShape
{
public:
	IShape();
	virtual void rotate();
	virtual void moveDown();
	virtual void moveLeftRight(int);
	const std::vector<Position>& getPos() const { return position; };
	
protected:
	std::vector<Position> position;
};

