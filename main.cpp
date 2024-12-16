// Larry Wang final capstone for cs202 - Spring 24


// Thank you to the ta's and Dr. Scott. I feel like I learned a lot in
// this class and I very much enjoyed taking it. Can't wait to take 302 
// in the fall!


// REFERENCES/HELP
// List of valid guesses that player can enter-
//      https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93
// Word bank of possible wordle words to guess-
//      https://github.com/Kinkelin/WordleCompetition/blob/main/data/official/shuffled_real_wordles.txt


// Help with ______
//      rand/srand-
//          https://stackoverflow.com/questions/13896450/rand-returns-the-same-number-each-time-the-program-is-run
//      stl set-
//          https://www.geeksforgeeks.org/set-in-cpp-stl/ 
//      clearing screen- 
//          https://stackoverflow.com/questions/17335816/clear-screen-using-c
//      colored text-
//          https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
//          https://saturncloud.io/blog/how-to-print-colored-text-to-the-terminal/         


// ^ explanation for using vector over set is in log.txt. Basically the list of words is
//   small enough that traversing to find is still very fast. I did use a set for the list of characters that are
//   still possible to use


#include "wordle.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


bool load_file(vector<string> &vec, const string file_name) {
    string line;
    ifstream fin;
    fin.open(file_name);

    if(!fin.is_open()){
        cerr << "error: file did not open correctly" << '\n';
        return false;
    }

    while(getline(fin,line))
        vec.push_back(line);

    return true;
}


int get_rand(const int list_size) {
    return rand() % list_size;
}


bool check_guess(string guess, vector<string> &vec) {
    // checking for only letters in ascii
    for(int i = 0; i < 5; i++) {
        if(guess[i] < 'A' || (guess[i] > 'Z' && guess[i] < 'a') || guess[i] > 'z')
            return false;   
    }

    // checks if it is in the valid word bank
    vector<string>::iterator it;
    it = find(vec.begin(), vec.end(), guess);
    if(it == vec.end())
        return false;

    return true;
}



int main(int argc, char **argv) {
    // error checks usage
    if(argc != 3) {
        cerr << "usage: ./main input/valid-wordle-words.txt input/shuffled_real_wordles.txt" << '\n';
        return 1;
    }

    // loads list of valid words and error checks fin
    string guesses = argv[1];
    string words = argv[2];
    vector<string> w_bank;
    vector<string> valid_guesses;


    // stores lists in vectors
    if( !load_file(valid_guesses, guesses) ) {
        cerr << "Cannot open " << guesses << '\n';
        return 1;
    }

    if( !load_file(w_bank, words) ) {
        cerr << "Cannot open " << guesses << '\n';
        return 1;
    }


    // START OF GAME
    srand(time(NULL));
    // retrieving random word among list
    int rand_index = get_rand(w_bank.size());

    Wordle Wordle(w_bank[rand_index]);
    Wordle.print_instructions();
    string word_guess, input;
    int wins = 0;
    int games_played = 0;
    int attempts_wins[6];

    // While loop for game
    while(true){
        printf("Enter command: ('help'for instructions and 'new' to start game)\n");
        cin >> input;
        
        if(input == "help") {
            printf("    \nInstructions: \n    help - Print's instructions\n");
            printf("    new - Starts New Game\n");
            printf("    done - Quit game\n\n");
        }
        else if(input == "done") {
            break;
        }
        else if(input == "new") {
            
            printf("\n");
            while(Wordle.game_over != true && Wordle.attempts != 6) {
                
                // checking valid guesses
                cout << "\033[2J\033[1;1H";     // clearing screen from reference
                Wordle.print_guesses();
                Wordle.print_available_letters();
                printf("Attempt %d: ", Wordle.attempts + 1);


                while(true) {
                    cin >> word_guess;
                    if(word_guess.length() > 5)
                        printf("Word is too long!\n\n");
                    else if(word_guess.length() < 5)
                        printf("Word is too short!\n\n");
                    else if(!check_guess(word_guess, valid_guesses))
                        printf("Not in word bank!!\n\n");
                    else 
                        break;
                }
                Wordle.check_guess(word_guess);
            }
            

            // prints whether win or loss
            cout << "\033[2J\033[1;1H";     // clearing screen from reference
            Wordle.print_guesses();


            if(Wordle.win){
                printf("\nYou win! Yippeeeeee!\n");
                wins++;
                int n = Wordle.attempts;
                attempts_wins[n - 1]++;
            }
            else
                printf("\nBetter luck next time. :'(\n");


            // gets new game started and counts stats
            games_played++;
            cout << "Wordle was: " << w_bank[rand_index] << '\n' << '\n';
            rand_index = get_rand(w_bank.size());
            Wordle.new_game(w_bank[rand_index]);
        }
        // error checking input
        else {
            cout << "Unknown command." << '\n';
        }
    }

    // Printing stats
    printf("\n\nGames won out of played: %d/%d\n", wins, games_played);
    for(int i = 0; i < 6; i++) {
        printf("%d tries: %d wins\n", i+1, attempts_wins[i]);
    }
    return 0;
}