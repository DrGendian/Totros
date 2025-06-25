#include "Game.h"
#include "Square.h"
#include "TShape.h"
#include "RightL.h"
#include "ReverseL.h"
#include "Long.h"
#include "ReverseZ.h"
#include "RightZ.h"
#include <time.h>
#include <conio.h>
#include <thread>
#include <mutex>

Game::Game() {

}

void inputThreadFunc(IShape*& currentShape, std::mutex& mtx, std::atomic<bool>& running, std::atomic<int>& refreshSpeed) {
	bool reset = true;
	while (running) {
		if(reset) refreshSpeed = 300; else reset = true;
		int ch = _getch();
		if (ch == 224) {
			ch = _getch();
			std::lock_guard<std::mutex> lock(mtx);
			if (currentShape != nullptr) {
				switch (ch) {
					case 77: currentShape->moveLeftRight(1); break;  // Rechts
					case 75: currentShape->moveLeftRight(0); break;  // Links
					case 80: reset = false; refreshSpeed = 50; break; // Runter
					case 72: currentShape->rotate();    break;
				}
			}
		}
	}
}

void Game::startGame() {
	srand(time(NULL));
	std::vector<IShape*> nextShape;
	GameBoard gameBoard = GameBoard();
	nextShape.push_back(randomShape());
	IShape* currentShape = nextShape.at(0);
	std::mutex mtx;
	std::atomic<bool> running(true);
	std::atomic<int> refreshSpeed = 300;
	std::thread inputThread(inputThreadFunc, std::ref(currentShape), std::ref(mtx), std::ref(running), std::ref(refreshSpeed));
	int clearedRows = 0;
	while (1) {
		system("cls");
		{
			std::lock_guard<std::mutex> lock(mtx);
			std::cout << clearedRows << std::endl;
			gameBoard.printBoard(*currentShape);
		}
		{
			std::lock_guard<std::mutex> lock(mtx);
			if (gameBoard.checkCollision(currentShape)) {
				refreshSpeed = 300;
				clearedRows += gameBoard.savePos(currentShape->getPos());
				delete currentShape;
				nextShape.clear();
				nextShape.push_back(randomShape());
				currentShape = nextShape.at(0);
				if (gameBoard.checkCollision(currentShape)) {
					break;
				}
			}
			else {
				currentShape->moveDown();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(refreshSpeed));
	}
	running = false;
	inputThread.join();
}

IShape* Game::randomShape() {
	int random = rand() % 7;

	switch (random) {
	case 0:
		return new Square();
	case 1:
		return new Long();
	case 2:
		return new ReverseL();
	case 3:
		return new ReverseZ();
	case 4:
		return new RightL();
	case 5:
		return new RightZ();
	case 6: 
		return new TShape();
	default:
		return new Square();
	}
	return new Square();
}