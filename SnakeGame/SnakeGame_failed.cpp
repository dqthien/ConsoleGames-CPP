#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct position {
    int x;
    int y;
};

//-------------------------------------------- Init data----------------------------------------
bool gameOver; // game state
const int borderHeight = 20, borderWidth = 10; // board size
vector<vector<int>> board(borderHeight, vector<int>(borderWidth, 0)); // Initialize the game board with zeros
int fruitX, fruitY; // fruit location
vector<position> snake; // snake location
int score; // score of the player
enum Direction { Stop, Right, Left, Up, Down };
Direction dir; // current snake direction
bool flag; // for various flag uses

//------------------------------------------- Game Functions-------------------------------------
void setUp() {
    gameOver = false;
    dir = Stop;

    // Initialize the snake's position at the center of the board
    position head;
    head.x = borderWidth / 2;
    head.y = borderHeight / 2;
    snake.push_back(head);

    for (int i = 0; i < 3; i++) {
        position bodyPart;
        bodyPart.x = head.x - i - 1;
        bodyPart.y = head.y;
        snake.push_back(bodyPart);
    }

    // Place the initial fruit
    fruitX = rand() % borderWidth;
    fruitY = rand() % borderHeight;

    // Ensure the initial fruit isn't placed at the snake position
    while (fruitX == head.x) fruitX = rand() % borderWidth;
    while (fruitY == head.y || fruitY == head.y - 1 || fruitY == head.y - 2 || fruitY == head.y - 3) fruitY = rand() % borderHeight;
    score = 0;
}

void drawMap() {
    system("cls");

    for (int i = 0; i < borderHeight; i++) {
        for (int j = 0; j < borderWidth; j++) {
            switch (board[i][j]) {
            case 0:
                cout << " ";
                break;
            case -1:
                cout << "#";
                break;
            case 1:
                cout << "o";
                break;
            case 2:
                cout << "O";
                break;
            case 3:
                cout << "F";
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}

void Control() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'w':
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Update the snake's position based on the current direction
    position newHead = snake[0];
    switch (dir) {
    case Left:
        newHead.x--;
        break;
    case Right:
        newHead.x++;
        break;
    case Up:
        newHead.y--;
        break;
    case Down:
        newHead.y++;
        break;
    default:
        break;
    }

    // Check for collisions with the game border
    // Collisions with left border
    if (newHead.x < 0) {
        newHead.x = borderWidth - 1;
    }
    // Collisions with right border
    else if (newHead.x >= borderWidth) {
        newHead.x = 0;
    }
    // Collisions with upper border
    else if (newHead.y < 0) {
        newHead.y = borderHeight - 1;
    }
    // Collisions with lower border
    else if (newHead.y >= borderHeight) {
        newHead.y = 0;
    }

    // Check for collisions with the fruit
    flag = false;
    if (newHead.x == fruitX && newHead.y == fruitY) {
        // Set flag
        flag = true;
        // Increase the score
        score += 10;
        // Place a new fruit
        fruitX = rand() % borderWidth;
        fruitY = rand() % borderHeight;
    }

    // Check self collisions
    for (int i = 1; i < snake.size(); i++) {
        if (newHead.x == snake[i].x && newHead.y == snake[i].y)
            gameOver = true;
    }

    // Update data and board
    board[newHead.y][newHead.x] = 2;
    snake.insert(snake.begin(), newHead);
    if (flag == false) {
        board[snake.back().y][snake.back().x] = 0;
        snake.pop_back();
    }
}

//-----------------------------------------------Main game------------------------------------------------
int main() {
    setUp();
    while (!gameOver) {
        drawMap();
        Control();
        Logic();
    }
    // TODO: Implement the game over

    return 0;
}
