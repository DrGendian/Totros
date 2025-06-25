#pragma once
#include "IShape.h"

class TShape : public IShape
{
public: 
	TShape();
	void rotate() override;
};

