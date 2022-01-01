#pragma once
#include<iostream>
#include"LinkedStack.h"


int** Maze;//地图指针

int** mark;

int targetX, targetY;

struct offsets {
    int x, y;
    std::string direction;
};

LinkedStack<offsets>result;

const offsets Move[4] = { {-1, 0,"N"},
                        { 0, 1,"E"},
                        { 0,-1,"W"},
                        { 1, 0,"S" } };


bool SeekPath(int x, int y) {
    if (x == targetX && y == targetY) {
        return 1;
    }
    int m, n;//coordinate of the next position
    std::string direction;
    for (int i = 0; i < 4; i++) {
        m = x + Move[i].x;
        n = y + Move[i].y;
        direction = Move[i].direction;

        if (Maze[m][n] == 0 && mark[m][n] == 0) {
            mark[m][n] = 1;
            if (SeekPath(m, n)) {
                offsets step;
                step.x = m;
                step.y = n;
                step.direction = direction;
                result.Push(step);
                //std::cout << "(" << m << "," << n << ")," << "Direction: " << direction << "," << std::endl;
                mark[m][n] = 2;
                return true;
            }
        }
    }

    return false;

}

void PrintMaze(int m, int n) {
    std::cout << "迷宫地图:" << std::endl;
    //std::cout<<"          ";//10 spaces
    std::cout << "    ";
    for (int i = 0; i < m * 2 + 1; i++) {
        if (i < 10) {
            std::cout << " " << i;
        }
        else {
            std::cout << i ;//7 spaces
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < m * 2 + 1; i++) {
        if (i < 10) {
            std::cout << " " << i << "行";
        }
        else {
            std::cout << i << "行";
        }
        for (int j = 0; j < n * 2 + 1; j++) {
            if (1 == Maze[i][j]) {
                std::cout << " #";
            }
            else if (0 == Maze[i][j] && (0 == mark[i][j] || 1 == mark[i][j])) {
                std::cout << "  ";
            }
            else if (0 == Maze[i][j] && 2 == mark[i][j]) {
                std::cout << " X";
            }
        }
        std::cout << std::endl;
    }
}