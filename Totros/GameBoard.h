#pragma once
#include <array>
#include "IShape.h"
#include <iostream>
class GameBoard
{
public:
	GameBoard();
	void printBoard(IShape&);
	int savePos(const std::vector<Position>& pos);
	bool checkCollision(IShape*);
private:
	std::array<std::array<int, 10>, 20> gameBoard;
};

