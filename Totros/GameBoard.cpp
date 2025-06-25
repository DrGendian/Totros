#include "GameBoard.h"
#include <algorithm>

GameBoard::GameBoard() : gameBoard() {
    for (auto& column : gameBoard) {
        for (auto& tile : column) {
            tile = 0;
        }
    }
}

void GameBoard::printBoard(IShape& shape) {
    std::vector<Position> shapeBlocks = shape.getPos();

    for (int y = 0; y < 20; ++y) {
        std::cout << "\t";
        for (int x = 0; x < 10; ++x) {
            bool isShapeBlock = false;

            for (const auto& block : shapeBlocks) {
                if (block.x == x && block.y == y) {
                    isShapeBlock = true;
                    break;
                }
            }

            if (isShapeBlock) {
                std::cout << "[]";
            }
            else if (gameBoard[y][x] == 1) {
                std::cout << "[]";
            }
            else {
                std::cout << "..";
            }
        }
        std::cout << "\n";
    }
}

int GameBoard::savePos(const std::vector<Position>& blocks) {
    for (const auto& pos : blocks) {
        if (pos.x >= 0 && pos.x < 10 && pos.y >= 0 && pos.y < 20) {
            gameBoard[pos.y][pos.x] = 1;
        }
    }

    std::vector<int> rowsToClear;
    for (const auto& pos : blocks) {
        int y = pos.y;
        if (std::find(rowsToClear.begin(), rowsToClear.end(), y) != rowsToClear.end()) {
            continue;
        }

        bool full = true;
        for (int i = 0; i < 10; i++) {
            if (gameBoard[y][i] == 0) {
                full = false;
                break;
            }
        }

        if (full) {
            rowsToClear.push_back(y);
        }
    }

    std::sort(rowsToClear.begin(), rowsToClear.end(), std::greater<int>());

    int clearedRows = 0;
    for (int row : rowsToClear) {
        clearedRows++;
        for (int y = row; y > 0; y--) {
            for (int i = 0; i < 10; i++) {
                gameBoard[y][i] = gameBoard[y - 1][i];
            }
        }
        for (int i = 0; i < 10; i++) {
            gameBoard[0][i] = 0;
        }
    }

    return clearedRows;
}

bool GameBoard::checkCollision(IShape* shape) {
    for (const auto& block : shape->getPos()) {
        if (block.y >= 19) {
            return true;
        }
        if (block.y + 1 < 20 && gameBoard[block.y + 1][block.x] == 1) {
            return true;
        }
    }
    return false;
}