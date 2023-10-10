#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

//--------------------------------------------- For storing snake data--------------------------------
struct Position{
    int x;
    int y;
    Position* next;
};

void addHead(int x, int y, Position*& head){
    Position* temp = new Position;
    temp->x = x;
    temp->y = y;
    temp->next = head;
    head = temp;
}

void removeTail(Position*& head){
    Position* temp = head;
    while(temp->next != nullptr) temp = temp->next;
    delete temp;
}


//-------------------------------------------- Init data----------------------------------------
bool gameOver; //game state
const int borderHeight = 20, borderWidth = 10; //board size
Position* head; //snake head location
int fruitX, fruitY; //fruit location
int score; //score of player
enum Direction {Stop, Right, Left, Up, Down};
Direction dir; //current snake direction


//------------------------------------------- Game Functions-------------------------------------
void setUp(){
    gameOver = false;
    dir = Stop;
    addHead(borderWidth/2, borderHeight/2, head);
    fruitX = rand() % borderWidth;
    fruitY = rand() % borderHeight;
    score = 0;
}

void drawMap(){
    system("cls");

    //top border
    for (int i = 0; i < borderWidth; i++) cout << "#";
    cout << endl;

    //middle
    for (int j = 1; j < borderHeight - 1; j++){
        for (int i = 0; i < borderWidth; i++){
            if (i == 0) cout << "#";
            else if (i == borderWidth) cout << "#" << endl;
            // else if (i == x && j == y) cout << "O"; //head
        }
    }

    //bottom border
    for (int i = 0; i < borderWidth; i++) cout << "#";
}

void Control(){

}

void Logic(){

}

void cleanUp(Position*& head){
    Position* temp = head;
    while(head != nullptr){
        head = head->next;
        delete temp;
    }
}

int main(){

}