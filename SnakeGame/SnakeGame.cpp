#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
eDirection prevDir; // Added to store the previous direction.

void Setup() {
    gameOver = false;
    dir = STOP;
    prevDir = STOP; // Initialize the previous direction.
    x = width / 2;
    y = height / 2;
    // Check and reposition the fruit until it's in a valid location.
    do {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while (fruitX == x && fruitY == y);
    score = 0;
}

void Draw() {
    system("cls");

    // Draw the top border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // Draw left border

            if (i == y && j == x)
                cout << "O"; // Draw the snake's head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Draw the fruit
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Draw the tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // Draw right border
        }
        cout << endl;
    }

    // Draw the bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            // Check if the new direction is not the opposite of the previous direction.
            if (prevDir != RIGHT) {
                dir = LEFT;
                prevDir = dir; // Update the previous direction.
            }
            break;
        case 'd':
            if (prevDir != LEFT) {
                dir = RIGHT;
                prevDir = dir;
            }
            break;
        case 'w':
            if (prevDir != DOWN) {
                dir = UP;
                prevDir = dir;
            }
            break;
        case 's':
            if (prevDir != UP) {
                dir = DOWN;
                prevDir = dir;
            }
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic(int& speed) {
    // Shift the entire body from the previous Logic run
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Make new change on the head location
    switch (dir) {
    case LEFT:
        if (prevDir != RIGHT) // Prevent going in opposite direction
            x--;
        break;
    case RIGHT:
        if (prevDir != LEFT)
            x++;
        break;
    case UP:
        if (prevDir != DOWN)
            y--;
        break;
    case DOWN:
        if (prevDir != UP)
            y++;
        break;
    default:
        break;
    }

    // Update the previous direction
    prevDir = dir;

    // Collision with borders
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Collision with fruit
    if (x == fruitX && y == fruitY) {
        if (floor((score + 1) / 10) > floor(score / 10) && speed > 0) speed = speed - 10;
        score += 1;
        
        // Check if the fruit position is inside the snake's body and reposition if needed.
        bool validFruitPosition = false;
        while (!validFruitPosition) {
            validFruitPosition = true;
            fruitX = rand() % width;
            fruitY = rand() % height;

            // Check against the entire tail.
            for (int i = 0; i < nTail; i++) {
                if (tailX[i] == fruitX && tailY[i] == fruitY) {
                    validFruitPosition = false;
                    break; // Fruit is inside the tail, reposition it.
                }
            }
        }

        nTail++;
    }

    // Collision with tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
}

int main() {
    Setup();
    int speed = 100; // Game delay
    while (!gameOver) {
        Draw();
        Input();
        Logic(speed);

        _sleep(speed);
    }
    return 0;
}
