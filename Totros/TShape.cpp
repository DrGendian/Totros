#include "TShape.h"

TShape::TShape() : IShape() {
	position.push_back({ 4, 0 });
	position.push_back({ 3, 1 });
	position.push_back({ 4, 1 });
	position.push_back({ 5, 1 });
}

void TShape::rotate() {
	const int& mainX = position.at(2).x;
	const int& mainY = position.at(2).y;

	for (auto& block : position) {
		int newX = mainX - (block.y - mainY);
		int newY = mainY + (block.x - mainX);
		if (newX > 0 && newX < 10 && newY >= 0 && newY <= 19) {
			block.x = newX;
			block.y = newY;
		}
	}
}