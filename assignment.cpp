#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

// Global variable for the game board
string board[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};

// Function to draw the game board
void draw() {
    cout << "     |     |      \n";
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
    cout << "_____|_____|_____ \n";
    cout << "     |     |      \n";
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
    cout << "_____|_____|_____ \n";
    cout << "     |     |      \n";
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
    cout << "     |     |      \n";
    cout << "\n";
}

// Class to handle the game board display
class GameBoard {
public:
    void displayBoard(int position, char letter = ' ', int number = -1) {
        system("CLS");

        // Clear the board
        for (int i = 0; i < 9; ++i) {
            board[i] = " ";
        }

        // Update the board array with the current position, letter, or number
        if (position >= 0 && position < 9) {
            if (number != -1) {
                board[position] = to_string(number);
            } else if (letter != ' ') {
                board[position] = letter;
            } else {
                board[position] = "X";
            }
        }
        draw();  // Draw the updated board
    }
};

class SequenceManager { // Class to manage sequences
private:
    vector<int> positionSequence;
    vector<char> letterSequence;
    vector<int> numberSequence;
public:
    void generateSequence(int size) {
        positionSequence.clear();
        letterSequence.clear();
        numberSequence.clear();
        for (int i = 0; i < size; ++i) {
            positionSequence.push_back(rand() % 9); // Positions 0-8 on a 3x3 grid
            letterSequence.push_back('A' + rand() % 26); // Letters A-Z
            numberSequence.push_back(rand() % 10); // Numbers 0-9
        }
    }

    int getPosition(int step) {
        return positionSequence[step];
    }

    char getLetter(int step) {
        return letterSequence[step];
    }

    int getNumber(int step) {
        return numberSequence[step];
    }

    void addPosition(int position) {
        positionSequence.push_back(position);
    }

    void addLetter(char letter) {
        letterSequence.push_back(letter);
    }

    void addNumber(int number) {
        numberSequence.push_back(number);
    }

    bool isMatch(int currentStep, int n, int level) {
        if (currentStep < n) return false;
        bool positionMatch = positionSequence[currentStep] == positionSequence[currentStep - n];
        bool letterMatch = (level == 3) ? (letterSequence[currentStep] == letterSequence[currentStep - n]) : true;
        bool numberMatch = (level == 2) ? (numberSequence[currentStep] == numberSequence[currentStep - n]) : true;
        return positionMatch && letterMatch && numberMatch;
    }

    int getSequenceSize() {
        return positionSequence.size();
    }

    void Nback(int step, int n, int level) {
        if (step == 0) { system("pause"); }
        if (step > 0 && step < 2 && n == 2) { system("pause"); }
        if (step > 0 && step < 3 && n == 3) { system("pause"); }
        if (step == 7 /*&& level == 2*/) {system("pause");};
        if (step == 14 && level > 1) {system("pause");};
    }
};

class Player { // Class to track player details
private:
    int score;
public:
    Player() : score(0) {}

    void incrementScore() {
        ++score;
    }

    void decrementScore() {
        --score;
    }

    int getScore() {
        return score;
    }

    void saveScore(const string &playerName) {
        ofstream outFile("scores.txt", ios::app);
        if (outFile.is_open()) {
            outFile << playerName << ": " << score << endl;
            outFile.close();
        } else {
            cout << "Unable to open file to save score." << endl;
        }
    }
};

int main() {
    srand(time(0)); // Seed for random number generation

    string playerName;
    cout << "\tWelcome... \nTo the Dual N back game ! \n\nEnter your name: \n";
    cin >> playerName;

    GameBoard gameBoard;
    SequenceManager sequenceManager;
    Player player;

    int n;
    cout << "\nEnter the number of N back to set the difficulty:\n";
    cin >> n;

    int level;
    cout << "\nEnter the starting level (1 for position only, 2 for numbers and position, 3 for letters and position):\n";
    cin >> level;

    char userInput;
    int steps = 0;
    bool continuePlaying = true;
    bool lastRoundResult = true; // Store the result of the last round
    int correctInCurrentBlock = 0; // Track correct answers in current block of 7 steps

    while (continuePlaying) {
        steps = 0; // Reset steps for each new game
        sequenceManager.generateSequence(0); // Clear the sequence at the start of each round
        correctInCurrentBlock = 0;

        while (true) {
            int position = rand() % 9;
            char letter = 'A' + rand() % 26;
            int number = rand() % 10;

            sequenceManager.addPosition(position);
            if (level == 2) {
                sequenceManager.addNumber(number);
            } else if (level == 3) {
                sequenceManager.addLetter(letter);
            }

            gameBoard.displayBoard(position, level == 3 ? letter : ' ', level == 2 ? number : -1);

            sequenceManager.Nback(steps, n, level);

            if (steps >= n) {
                if (steps > n && steps != 7 && steps != 8 && steps != 14 && steps != 15) { // Only display the result from last round in the current round
                    cout << (lastRoundResult ? "Correct" : "Incorrect") << endl;
                    cout << "Current score: " << player.getScore() << endl;
                }

                if (steps != 7 && steps != 14) {
                    cout << "Does this match the position of " << n << " steps back? (y/n): ";
                    cin >> userInput;

                    lastRoundResult = ((userInput == 'y' && sequenceManager.isMatch(steps, n, level)) ||
                                       (userInput == 'n' && !sequenceManager.isMatch(steps, n, level)));

                    if (lastRoundResult) {
                        player.incrementScore();
                        ++correctInCurrentBlock;
                    } else {
                        player.decrementScore();
                    }
                }
            }

            ++steps;

            if (steps % 7 == 0) { // Ask the user if they want to raise the level every 7 steps
                if (correctInCurrentBlock > 3) {
                    system("CLS");
                    cout << "\nYou are doing great so far...\n\nWe have more for you,\n" << endl;
                    cout << "Do you want to raise the level? (y/n): ";
                    cin >> userInput;
                    if (userInput == 'y' && level < 3) {
                        ++level;
                        system("CLS");
                        cout << "Level increased to level " << level << "!" << endl;
                        system("pause");
                    }
                }
                correctInCurrentBlock = 0; // Reset the count for the next block of 7 steps
            }

            if (steps == 21) { // Limit the game to 21 steps for each round
                system("CLS");
                cout << "\t.\n\t.\n\t.\nEnd of round.\n\nDo you want to continue playing? (y/n): ";
                cin >> userInput;
                if (userInput != 'y') {
                    continuePlaying = false;
                }
                break; // Exit the inner loop and start a new game
            }
        }
    }

    player.saveScore(playerName);

    system("CLS");
    cout << "This is the end of the game\n\nThank you " << playerName << " for playing." << endl;
    cout << "\nYour final score is " << player.getScore() << " out of " << steps << endl;

    return 0;
}
