#include "Main.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int X, Y, PointX, PointY, score;
int tailX[100], tailY[100];
int nTail;
bool isHardMode;
enum _direction { STOP =0, LEFT, RIGHT, DOWN , UP  };
_direction dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	X = width / 2;
	Y = height / 2;
	PointX = rand() % width;
	PointY = rand() % height;
	score = 0;
	//Get the input for Easy or Hard Mode
	std:cout << "Enter e for easy and h for hard mode!" << std::endl;
	char inputMode;
	cin >> inputMode;
	if (inputMode == 'e')
	{
		isHardMode = false;
		std::cout << "You chose easy mode!" << std::endl;
	}
	else if (inputMode == 'h')
	{
		isHardMode = true;
		std::cout << "You chose hard mode" << std::endl;
	}
	Sleep(3000);
}

void Draw()
{	
	system("cls"); //clear console
	//Top Wall
	for (int i = 0; i < width+1; i++)
	{
		std::cout << "#";
	}
	std::cout << endl;
	//Print the Map
	for (int column = 0; column < height; column++)
	{
		for (int row = 0; row < width; row++)
		{
			if (row == 0 || row == width - 1)
			{
				std::cout << "#";
			}
			if (column == Y &&  row == X)
			{
				std::cout << "O";
			}
			else if (column == PointY && row == PointX)
			{
				std::cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == row && tailY[k] == column)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
		
				
			}
		}
		std::cout << std::endl;
	}

	//Bottom Wall
	for (int i = 0; i < width+1; i++)
	{
		std::cout << "#";
	}
	std::cout << endl;
	//Print the score:
	std::cout << "Score:" << score << std::endl;
}

void Input()
{
	if (_kbhit()) //if keyboard hit
	{
		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = TRUE;
				break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = X;
	tailY[0] = Y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		X--;
		break;
	case RIGHT:
		X++;
		break;
	case UP:
		Y--;
		break;
	case DOWN:
		Y++;
		break;
	default:
		break;
	}
	//Gameover Condition ( If hit the wall) (hard mode)
	if (isHardMode)
	{
		if (X < 0 || X > width - 2 || Y > height - 1 || Y < 0)
		{
			gameOver = TRUE;
		}
	}
	//easy mode ( No game over for hitting the wall)
	else
	{
		if (X >= width - 1)
		{
			X = 0;
		}
		else if (X < 0)
		{
			X = width - 2;
		}
		if (Y >= height)
		{
			Y = 0;
		}
		else if (Y < 0)
		{
			Y = height - 1;
		}

	}

	//Gameover Condition ( If hit the tail)
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == X && tailY[i] == Y)
		{
			gameOver = true;
		}
	}
	//If player eats the dot (F)
	if (X == PointX && Y == PointY)
	{
		PointX = rand() % width;
		PointY = rand() % height;
		nTail++;
		score++;
	}
	
}


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		if(dir == LEFT || dir == RIGHT)
		{
			Sleep(5);
		}

		Sleep(60);

		if (dir == UP || dir == DOWN)
		{
			Sleep(60);
		}
	}
}