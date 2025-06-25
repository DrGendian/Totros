#pragma once
#include "GameBoard.h"
#include <iostream>
#include <chrono>
#include <thread>

class Game
{
public:
	Game();
	void startGame();
	IShape* randomShape();
private:

};

