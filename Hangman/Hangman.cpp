#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------Data init-----------------------------------
int wrong; // Number of wrong guesses
vector<vector<int>> board(10, vector<int>(15, 0)); // The current Board, size: height = 10, width = 15
bool gameOver, correct, used; // Flag to control game state
vector<string> dictionary; // Dictionary
string answer, chosen, temp; // Player answer and word picked for game
int submitted[26], found; // Controlled the player guessed word.


//----------------------------------------------------Game functions-------------------------------------
void importDict(){
    ifstream file("dictionary.txt");
    if(file.is_open()){
        string word;
        while(getline(file, word)) dictionary.push_back(word);
        file.close();
    }
    else cout << "Unable to import file";
}

void setUp(){
    // Prepare the board
    for(int i = 0; i < 10; i ++)
        for (int j = 0; j < 15; j++){
            if (i == 0 && j >= 2 && j <= 13) board[i][j] = 1; // symbol '-'
            else if ((j == 0 && i == 9) || (j == 1 && i == 8)) board[i][j] = 2; // symbol '/'
            else if ((j == 3 && i == 8) || (j == 4 && i == 9)) board[i][j] = 3; // symbol '\'
            else if ((j == 2 && i < 8) || (j == 13 && (i == 1 || i == 2))) board[i][j] = 4; // symbol '|'
            else board[i][j] = 0; // add a space
        }
    
    // Reset word storage from previous run
    chosen.clear();
    answer.clear();
    temp.clear();

    // Prepare the word
    chosen = dictionary[rand() % dictionary.size()]; // The chosen word for the game
    for (int i = 0; i < chosen.length(); i++){
        answer += '_';
    }
    temp = chosen;


    // Reset the submitted word
    for (int i = 0; i < 26; i++) submitted[i] = 0;

    // Prepare other data
    found = 0;
    gameOver = false;
    wrong = 0;
    used = false;
}

void Draw(){
    system("cls");

    // draw board
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 15; j++){
            switch (board[i][j]) {
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << "-";
                    break;
                case 2:
                    cout << "/";
                    break;
                case 3:
                    cout << "\\";
                    break;
                case 4:
                    cout << "|";
                    break;
                case 5: 
                    cout << "O";
                    break;
                default: 
                    break;
            }
        }
        cout << endl;
    }

    // Draw answer 
    if(!gameOver){
        cout << "        ";
        for (int i = 0; i < answer.length(); i++) cout << answer[i];
        cout << "  (" << chosen.length() << " letters)";
        cout << endl << endl << "Used words:";
        for (int i = 0; i < 26; i++){
            if(submitted[i] == 1) cout << " " << static_cast<char>('a' + i);
        }
        cout << endl << endl;
    }

    //If the previous letter was used
    if (used == true) cout << "Used letter. Please choose a different one." << endl;
}

void Logic(char Input){
    // Reset flag
    correct = false;
    used = false;

    // Check if the word is used
    if (submitted[Input - 'a'] == 1) used = true;
    else{
        // Turn on the used list
        submitted[Input - 'a'] = 1;

        // Check answer
        while (temp.find(Input) != string::npos){
            correct = true;
            found++;
            answer.replace(temp.find(Input), 1, 1, temp[temp.find(Input)]); 
            temp.replace(temp.find(Input), 1, "_"); 
        }

        // Process wrong guess
        if (!correct) wrong++;
        switch (wrong){
            case 1:
                board[3][13] = 5;
                break;
            case 2:
                board[4][13] = 4;
                break;
            case 3:
                board[4][12] = 1;
                break;
            case 4:
                board[4][14] = 1;
                break;
            case 5:
                board[5][12] = 2;
                break;
            case 6:
                board[5][14] = 3;
                gameOver = true;
                break;
            default:
                break;
        }

        //Check if every letters are found
        if (found == chosen.length() || wrong == 6) gameOver = true;
    }
}

//--------------------------------------------------------Main part---------------------------------------

int main(){
    importDict();
    srand(static_cast<unsigned>(time(0)));
    while(1){
        char processedInput;
        string Input;
        setUp();
        while(!gameOver){
            Draw();
            cout << "Choose your next letter: ";
            cin >> Input;
            processedInput = Input[0];
            Logic (processedInput);
        }
        Draw();
        if(found == chosen.length()) cout << endl <<  "\033[32mCongratulation!!! You win!" << endl << endl;
        else cout <<  "\033[31mYou didn't guess the correct word." << endl << endl; 
        cout << "\033[32mThe word was: " << chosen << endl;
        cout << "---------------------------------------------------------" << endl << "Play again? (Y/N): ";
        cin >> Input;
        processedInput = Input[0];
        switch (processedInput){
            case 'n':
                return 0;
            case 'N':
                return 0;
            default:
                break;
        }
        std::cout << "\x1b[0m";
    }
}