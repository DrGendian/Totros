#include "IShape.h"
IShape::IShape() {

}

void IShape::moveDown() {
	for (auto& block : position) {
		if (block.y >= 19) {
			return;
		}
		block.y += 1;
	}
}

void IShape::rotate() {
	const int& mainX = position.at(1).x;
	const int& mainY = position.at(1).y;

	for (auto& block : position) {
		int newX = mainX - (block.y - mainY);
		int newY = mainY + (block.x - mainX);
		if (newX > 0 && newX < 10 && newY >= 0 && newY <= 19) {
			block.x = newX;
			block.y = newY;
		}
	}
}

void IShape::moveLeftRight(int dir) {
	if (dir) {
		for (auto& block : position) {
			if (block.x + 1 > 9) {
				return;
			}
		}
		for (auto& block : position) {
			block.x += 1;
		}
	}
	else {
		for (auto& block : position) {
			if (block.x - 1 < 0) {
				return;
			}
		}
		for (auto& block : position) {
			block.x -= 1;
		}
	}
}