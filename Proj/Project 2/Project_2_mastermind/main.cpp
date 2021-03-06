/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Josh Drentlaw
 *
 * Created on February 05, 2018, 8:53 PM
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Function prototypes
string readCode();
string computerCode(const char []);
string validateCode(int, const char (&)[6]);
string computerGuess();
string getHints(string, string);
string getWinner(int, int);
int getAmtOfColor(char, int, char);

int search();

/*
 * Mastermind
 */
int main(int argc, char** argv) {
    /*
     * Declare and initialize variables
     */
    
    // Player variables
    int humans = 0;
    
    int maker = 1;
    
    int winner = 1;
    
    int p1Pts = 0;
    int p1Total = 0;
    int p2Pts = 0;
    int p2Total = 0;
    
    // Game variables
    const int GUESSES = 12;
    const int SIZE = 6;
    char colors[SIZE] = {'r', 'o', 'y', 'g', 'b', 'p'};
    
    int matches = 0;
    string code, guess, hints, snitch;
    
    cout << "Welcome to MASTERMIND! The game of code breaking!" << endl << endl;
    
    cout << "RULES OF THE GAME:" << endl;
    cout << "Valid colors: Red, Orange, Yellow, Green, Blue, Purple." << endl;
    cout << "Colors may be used multiple times." << endl;
    cout << "Enter exactly 4 colors!" << endl;
    cout << "Enter the code in the first line of the code-doc.txt file." << endl;
    cout << "When entering guesses, enter like so: royg" << endl;
    cout << "Use the first letter of the color, and do not separate with a space." << endl;
    cout << "After The Breaker has guessed, The Maker enters hints: o for correct color, and x for correct color and position." << endl;
    cout << "Enter a dash (-) if the color is not in the code." << endl << endl;
    
    cout << "Example of a round when code is royg:" << endl;
    cout << "rybg" << endl;
    cout << "xxo" << endl << endl;
    
    cout << "The order of the hints do not correspond with the order of the guess." << endl;
    cout << "The Breaker will have 12 tries to guess the code." << endl;
    cout << "Both players will agree on an even number of matches, and points are earned as The Maker at the end of each match." << endl;
    cout << "Players alternate between The Maker and Breaker roles." << endl;
    cout << "1 point is awarded for each incorrect guess made by The Breaker." << endl;
    cout << "An extra point is awarded if The Breaker does not guess correctly by the 12th round." << endl;
    cout << "The player with the most points at the end of the agreed upon matches wins!" << endl << endl;
    
    cout << "LET THE CODE BREAKING BEGIN!" << endl << endl;
    
    // Validate # of human players
    do {
        cout << "Make a selection:" << endl;
        cout << "   1. Human vs. Computer" << endl;
        cout << "   2. Human vs. Human" << endl << endl;
        cout << "Enter 1 or 2: ";
        cin >> humans;
    } while (humans < 1 || humans > 2);
    
    // Validate # of matches
    do {
        cout << "Enter an even number of matches: ";
        cin >> matches;
    } while (matches > 0 && matches % 2 == 1);
    
    switch (humans) {
        // Play with the computer
        case 1:
            while (matches > 0) {
                cout << endl;
                cout << "Player 1 Score: " << p1Total << "  Player 2 Score: " << p2Total << endl;

                // Human is The Maker
                if (maker == 1) {
                    // Validate code
                    code = validateCode(maker, colors);
                }
                // Computer is The Maker
                else {
                    // Get computer code
                    code = computerCode(colors);
                }

                // Guessing begins
                cout << endl << endl;
                cout << "Start guessing!" << endl;

                // The Breaker will have 12 attempts at guessing the code
                for (int i = 0; i < GUESSES; i++) {
                    guess = "";
                    hints = "";
                    snitch = "";

                    cout << "Guess " << i+1 << ":" << endl;
                    if (maker == 2) {
                        cin >> setw(4) >> guess;
                    }
                    else {
                        // Computer guesses
                        //guess = (i == 0) ? "royg" : computerGuess();  This is
                        // what I wanted to do, but I did not have time to come
                        // up with the computerGuess() function. Instead, computer
                        // just makes random guesses using the same code that 
                        // generates a code.
                        guess = computerCode(colors);
                        cout << guess << endl;
                    }

                    // Snitch tattles on the human if it inputs wrong hints,
                    // but it's also just the hints from the computer.
                    snitch = getHints(guess, code);

                    // The code was guessed correctly
                    if (guess == code) {
                        cout << "Congratulations! You broke the code!" << endl;
                        cout << "Code: " << code << endl << endl;

                        cout << "Player " << maker << " earned "
                                << ((maker == 1) ? p1Pts : p2Pts) << " points this match." << endl << endl;

                        p1Total += p1Pts;
                        p2Total += p2Pts;
                        p1Pts = 0;
                        p2Pts = 0;

                        maker = (maker == 1) ? 2 : 1;
                        cout << "The Maker is now Player " << maker << endl;

                        i = GUESSES;
                    }
                    else {
                        if (maker == 1) {
                            // Check if proper hints were given
                            getline(cin, hints);
                            cin.ignore(100, '\n');
                            if (hints != snitch) {
                                cout << "The Maker isn't being honest..." << endl;
                                cout << "Actual hint: " << snitch << endl;
                            }
                        }
                        else {
                            cout << snitch << endl;
                        }

                        // Give The Maker points if The Breaker guesses wrong
                        if (i == GUESSES-1) {
                            cout << "Oh no! The code was not broken... I guess you'll never know what it was..." << endl << endl;
                            (maker == 1) ? p1Pts += 2 : p2Pts += 2;

                            cout << "Player " << maker << " earned "
                                    << ((maker == 1) ? p1Pts : p2Pts) << " points this match." << endl << endl;

                            p1Total += p1Pts;
                            p2Total += p2Pts;
                            p1Pts = 0;
                            p2Pts = 0;

                            maker = (maker == 1) ? 2 : 1;
                            cout << "The Maker is now Player " << maker << endl;
                        }
                        else {
                            (maker == 1) ? p1Pts++ : p2Pts++;
                            cout << "p1Pts: " << p1Pts << " p2Pts: " << p2Pts << endl;
                        }
                    }
                }
            }
            break;
        // Play against a friend
        case 2:
            // Loop thru all matches
            while (matches > 0) {
                cout << endl;
                cout << "Player 1 Score: " << p1Total << "  Player 2 Score: " << p2Total << endl;
                cout << "PLayer " << ((maker == 1) ? 2 : 1) << ", TURN AROUND!! NO PEAKING!!" << endl;
                // Validate code
                code = validateCode(maker, colors);

                // Guessing begins
                cout << endl << endl;
                cout << "Start guessing!" << endl;

                // The Breaker will have 12 attempts at guessing the code
                for (int i = 0; i < GUESSES; i++) {
                    guess = "";
                    hints = "";
                    snitch = "";

                    cout << "Guess " << i+1 << ":" << endl;
                    cin >> setw(4) >> guess;

                    // Compare guess to code. With 2 human players, this is to keep The Maker honest!
                    snitch = getHints(guess, code);

                    // The code was guessed correctly
                    if (guess == code) {
                        cout << "Congratulations! You broke the code!" << endl;
                        cout << "Code: " << code << endl << endl;

                        cout << "Player " << maker << " earned "
                                << ((maker == 1) ? p1Pts : p2Pts) << " points this match." << endl << endl;

                        p1Total += p1Pts;
                        p2Total += p2Pts;
                        p1Pts = 0;
                        p2Pts = 0;

                        maker = (maker == 1) ? 2 : 1;
                        cout << "The Maker is now Player " << maker << endl;

                        i = GUESSES;
                    }
                    else {
                        // Check if proper hints were given
                        getline(cin, hints);
                        cin.ignore(100, '\n');
                        if (hints != snitch) {
                            cout << "The Maker isn't being honest..." << endl;
                            cout << "Actual hint: " << snitch << endl;
                        }

                        // Give The Maker points if The Breaker guesses wrong
                        if (i == GUESSES-1) {
                            cout << "Oh no! The code was not broken... I guess you'll never know what it was..." << endl << endl;
                            (maker == 1) ? p1Pts += 2 : p2Pts += 2;

                            cout << "Player " << maker << " earned "
                                    << ((maker == 1) ? p1Pts : p2Pts) << " points this match." << endl << endl;

                            p1Total += p1Pts;
                            p2Total += p2Pts;
                            p1Pts = 0;
                            p2Pts = 0;

                            maker = (maker == 1) ? 2 : 1;
                            cout << "The Maker is now Player " << maker << endl;
                        }
                        else {
                            (maker == 1) ? p1Pts++ : p2Pts++;
                            cout << "p1Pts: " << p1Pts << " p2Pts: " << p2Pts << endl;
                        }
                    }
                }
                matches--;
            }
            break;
    }
     
    cout << "GAME OVER!!" << endl;
    cout << "Final Score" << endl;
    cout << "Player 1: " << p1Total << "  Player 2: " << p2Total << endl;
    cout << "WINNER: " << getWinner(p1Total, p2Total) << endl;

    return 0;
}

/*
 * 
 * FUNCTION DEFINITIONS
 * 
 */


/*
 * readCode reads the code from the code-doc.txt file and returns the string it gets.
 * It takes no arguments.
 */
string readCode() {
    ifstream codeDoc;
    string code;
    
    codeDoc.open("code-doc.txt");
    if (codeDoc) {
        codeDoc >> code;
        codeDoc.close();
    }
    
    return code;
}

/*
 * This function generates a random color combination.
 * It takes the colors array as an argument.
 * It returns a string containing the code. 
 */
string computerCode(const char colors[]) {
    unsigned seed = time(0);
    const int MIN_VAL = 1;
    const int MAX_VAL = 6;
    int x;
    
    string code = "";
    char color;
    
    
    // Seed random number generator
    srand(seed);
    
    // Create a random number 4 times and use those as indices 
    // in the colors array and add them to code to create the code
    for (int i = 0; i < 4; i++) {
        x = (rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL)-1;
        color = colors[x];
        code += color;
    }
    
    return code;
}

/*
 * This function asks The Maker to enter a code and then validates it. 
 * It takes who The Maker is and a const array containing the valid colors as arguments.
 * It returns a string containing the code written in 'code-doc.txt'.
 */
string validateCode(int maker, const char (&colors)[6]) {
    char val = 0;
    bool notVal = false;
    char codePc;
    string code;
    ifstream codeDoc;
    
    do {
        do {
            cout << "Player " << maker << " is Code Maker. Enter a code into the 'code-doc.txt' file, then enter 1 here to continue: ";
            cin.ignore(100, '\n');
            cin >> val;
        } while (val != 49);
        val = 0;
        
        code = readCode();

        for (int i = 0; i < 4; i++) {
            codePc = tolower(code[i]);
            for (char color : colors) {
                if (color == codePc) {
                    notVal = false;
                }
            }
        }
    } while (notVal);
    
    return code;
}

/*
 * giveHints compares The Breakers guess to the code, and return what the hints
 * for the guess should be. In the 2 human player version, this keeps The Maker
 * honest. In the 1 human player version it will generate the hints for the computer.
 * It takes 2 strings: the guess and the code, and returns the chkHint string.
 */
string getHints(string guess, string code) {
    string correct = "";
    string almost = "";
    bool found = false;
    
    vector<char> check;
    
    for (char c : code) {
        check.push_back(c);
    }
    
    // Loop thru each char in the guess
    for (int i = 0; i < 4; i++) {
        int j = 0;
        found = false;
        // Search for the color
        while (j < 4 && !found) {
            // If the color is found at all
            if (guess[i] == check[j]) {
                // If it's in the correct position
                if (i == j) {
                    correct += "x";
                    // Blanking out the color ensures it won't be counted twice.
                    check[j] = ' ';
                    found = true;
                }
                else {
                    almost += "o";
                    check[j] = ' ';
                    found = true;
                }
            }
            j++;
        }
    }
    return correct+almost;
}


/*
 * Algorithm for the computer guessing the players code  
 */
string computerGuess() {
    
}

/*
 * getWinner returns who the winner is based off total accumulated points.
 * It takes both players scores as arguments.
 * It returns a string announcing the winner, or if there is a tie. 
 */
string getWinner(int p1, int p2) {
    if (p1 > p2) {
        return "Player 1";
    }
    else if (p1 < p2) {
        return "Player 2";
    }
    else {
        return "It's a Tie!";
    }
}


