#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <string>
#include <vector>
#include <set>

// Wordle unlimited knockoff game
// https://www.nytimes.com/games/wordle/index.html

class Wordle {

    public:

        // set correct word and attempts to 0(6 attempts means game over)
        // clears hard_mode characters
        Wordle(const std::string);
        int attempts;
        bool game_over, win;
        // compares guess with correct_w and prints results
        void check_guess(const std::string);
        void print_guesses();
        void print_available_letters();
        void print_instructions();
        void new_game(const std::string);
        
    private:
        std::string correct_w;                      // correct word            
        std::vector <std::string> prev_guesses;     // stores guesses & hints
        std::vector <int> prev_hints;
        std::set <char> availible_letters;
        char correct_letters[5];   // letters of correct_w for check_guess
        int hints[5];              // '31's, '33's, or '32's relative to color code in terminal
        int find_letter(const char);            // finds yellows
        void print_color(const int, const char);
};

#endif