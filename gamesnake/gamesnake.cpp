// gamesnake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
const int witch = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
edirection dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = witch / 2;
	y = height / 2;
	fruitX = rand() % witch;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < witch+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < witch; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y and j == x)
				cout << "0";
			else if (i == fruitY and j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";
			}

			if (j == witch - 1)
				cout << "#";
		}
		cout << endl;
		
	}
	for (int i = 0; i < witch+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	if (_kbhit())
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
			gameOver = true;
			break;
        }
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++)
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
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > witch || x<0 || y>height || y < 0)
		gameOver = true;
	for (int i = 0; i < ntail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % witch;
		fruitY = rand() % height;
		ntail++;
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
		Sleep(200); 
		
	}
	return 0;
}