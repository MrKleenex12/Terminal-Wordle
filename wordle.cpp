#include "wordle.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

// constructor
Wordle::Wordle(const string word) {
    this->correct_w = word;
    attempts = 0;
    game_over = false;
    win = false;

    for(char i = 97; i < 123; i++){
        availible_letters.insert(i);
    }
}

void Wordle::new_game(const string new_word){
    this->correct_w = new_word;
    attempts = 0;
    prev_guesses.resize(0);
    prev_hints.resize(0);
    game_over = false;
    win = false;

    availible_letters.clear();
    for(char i = 97; i < 123; i++)
        availible_letters.insert(i);
}


// 31 is red, 33 is yellow, 32 is green
void Wordle::print_color(const int color, const char let) {
    cout << "\033[1;" << color << "m" << let << " \033[0m";
}

void Wordle::print_available_letters() {
    printf("Available letters: \n");
    for(auto set : availible_letters) {
        printf("%c ", set);
    }
    printf("\n");
}

void Wordle::check_guess(const string guess) {
    // finds hints if incorrect word
    if(guess != correct_w){
        prev_guesses.push_back(guess);

        // resets letters for hints 
        for(int i = 0; i < 5; i++)
            correct_letters[i] = correct_w[i];


        // checks for greens and reds
        for(int i = 0; i < 5; i++) {
            if(correct_w[i] == guess[i]) {  // sets g color
                hints[i] = 32;
                correct_letters[i] = '?';
                // changes it to '?' instead of removing. prioritizing 
                // traversing speed of array over constant delete of something like lists
            }
            else{
                hints[i] = 31;      // sets r color
            }
        }


        // going back to find yellows
        for(int i = 0; i < 5; i++) { 
            if(hints[i] != 32 && find_letter(guess[i]) != -1){
                correct_letters[find_letter(guess[i])] = '?';
                hints[i] = 33;      // sets y color
            }
            // removes letter from avaiible list
            else if(hints[i] == 31){
                availible_letters.erase(guess[i]);
            }
        }

        // printing hints and storing prev hints
        for(int i = 0; i < 5; i++)
            prev_hints.push_back(hints[i]);
        
        // print_guesses();
    }
    else {
        if(attempts != 6)
            win = true;
        game_over = true;
        prev_guesses.push_back(correct_w);
        for(int i = 0; i < 5; i++)
            prev_hints.push_back(32);
        printf("\n");

    }

    attempts++;
}

// finds and returns index if char is in list of correct letters(yellows)
int Wordle::find_letter(const char let) {
    for(int i = 0; i < 5; i++) {
        if(correct_letters[i] == let)
            return i;
    }
    return -1;
}


void Wordle::print_guesses(){
    if(prev_guesses.size() != 0) {
        printf("\nPrevious Guesses:\n");
        for(size_t i = 0; i < prev_guesses.size(); i++){
            for(int j = 0; j < 5; j++){
                print_color(prev_hints[i * 5 + j],prev_guesses[i][j]);
            } 
            printf("\n");
        }
    }
}

void Wordle::print_instructions(){
    printf("\nHow To Play: \n");
    printf("HINTS will be revealed in red, green, or yellow.\n");
    printf("Example:\nword:  trend\nguess: clear\n       ");
    
    print_color(31, 'c');
    print_color(31, 'l');
    print_color(32, 'e');
    print_color(31, 'a');
    print_color(33, 'r');

    printf("\n\n");
}
