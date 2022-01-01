#include <iostream>
#include<time.h>
#include"MazeSolutions.h"
#include"PerfectMaze.h"

int main()
{
	srand((unsigned)time(NULL));
	std::cout << "请输入迷宫的尺寸:" << std::endl;
	std::cout << "例：10 10" << std::endl;
	int height, width;
	while (!(std::cin >> height >> width) || (std::cin.peek() != '\n' && std::cin.peek() != 32)||!(height>0&&width>0)) {
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		std::cout << "输入错误，请重新输入：." << std::endl;
	}

	//New
	Maze = new int* [height * 2 + 1];
	mark = new int* [height * 2 + 1];
	for (int i = 0; i < height * 2 + 1; i++) {
		Maze[i] = new int[width * 2 + 1];
		mark[i] = new int[width * 2 + 1];
	}

	targetX = height * 2 - 1;
	targetY = width * 2 - 1;

	Eller(height - 1, width);

	std::cout << std::endl;

	for (int i = 0; i < height * 2 + 1; i++) {
		for (int j = 0; j < width * 2 + 1; j++) {
			mark[i][j] = 0;
		}
	}

	if (SeekPath(1, 1)) {
		mark[1][1] = 2;
	}
	PrintMaze(height, width);
	int i = 0;
	while (!result.IsEmpty()) {
		offsets temp;
		result.Pop(temp);
		i++;
		std::cout << "(" << temp.x << "," << temp.y << ")," << "Direction: " << temp.direction<<"    ";
		if (i % 3 == 0) {
			std::cout << std::endl;
		}
	}
	//Delete
	for (int i = 0; i < height * 2 + 1; i++) {
		delete[]Maze[i];
		Maze[i] = NULL;
		delete[]mark[i];
		mark[i] = NULL;
	}
	delete[]Maze;
	delete[]mark;

	std::cout << "Hello world!" << std::endl;
}