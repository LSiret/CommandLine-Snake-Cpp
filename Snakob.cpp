#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

bool gameOver, newline;

const int width = 20;
const int height = 20;

int snakeX, snakeY, fruitX, fruitY, score;
enum eDirection {NONE, LEFT, RIGHT, UP, DOWN};
eDirection dir;

struct snakePart
{
	int xPos = -1, yPos = -1;
};

snakePart snake[50];

void Setup()
{
	gameOver = false;
	dir = NONE;
	
	snakeX = width / 2;
	snakeY = height / 2;

	fruitX = rand() % (width - 2);
	fruitY = rand() % (height-1);

	score = 0;

	snake[0].xPos = snakeX - 1;
	snake[0].yPos = snakeY - 1;
}

void Draw()
{
	// Clear Console
	system("cls");

	// Top Border
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}

	cout << endl; // Newline

	for (int i = 0; i < height; i++)
	{
		// Left Border
		cout << "#";

		for (int j = 0; j < width - 2; j++)
		{
			// Draw snake body
			for (int part = score + 1; part > 0; part--)
			{
				if (snake[part].yPos == i && snake[part].xPos == j)
				{
					newline = true;
				}
			}

			if (newline)
			{
				cout << "S";
				newline = false;
			} 
			else if (snakeY == i && snakeX == j)
			{
				cout << "*";
			}
			else if (fruitY == i && fruitX == j)
			{
				cout << "O";
			}
			else
			{
				cout << " ";
			}
		}

		// Right Border
		cout << "#";

		cout << endl; // Newline
	}

	// Bottom Border
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}

	cout << endl;

	cout << "Score:" << score;
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
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}

void Logic()
{

	// Update snake body
	for (int i = score; i > 0; i--)
	{
		// Check self-collision
		if (snakeX == snake[i].xPos && snakeY == snake[i].yPos)
		{
			gameOver = true;
		}

		// Move New snake part to previous part position
		snake[i].xPos = snake[i - 1].xPos;
		snake[i].yPos = snake[i - 1].yPos;
	}

	// Get snake head position
	snake[0].xPos = snakeX;
	snake[0].yPos = snakeY;

	switch (dir)
	{
	case LEFT:
		snakeX--;
		break;
	case RIGHT:
		snakeX++;
		break;
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	default:
		break;
	}

	if (snakeX == fruitX && snakeY == fruitY)
	{
		score++;
		fruitX = rand() % (width-2);
		fruitY = rand() % height;
	}

	if (snakeX >= width-2 || snakeX < 0 || snakeY < 0 || snakeY >= height)
	{
		gameOver = true;
	}

}

int main()
{

	// Initialise Game
	Setup();

	// Run Game
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}

	// End Game
	return 0;
}