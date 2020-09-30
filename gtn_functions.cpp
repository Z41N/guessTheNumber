#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <mmsystem.h>
#include <dshow.h>
#include "gtn_header.h"
#include <stdio.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


// Maximize and fullscreen the game


void format_window() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

// Obtain user and start main menu
void start_game() {

    // Create User Class
    class User {
        std::string rank = "Bronze";
    public:
        std::string user_name;
        std::string get_rank()
        {
            if (user_name == "Zain" || user_name == "zain") {
                return "Diamond";
            }
            else {
                return rank;
            }
        }
    };

    // Instantiate user object
    User user;

    // Declare user choice
    int user_choice;

    // Request and store username input

    SetConsoleTextAttribute(hConsole, 4);
    std::cout << "\n>Enter your username: \n";
    std::cin >> user.user_name;

    // Force first letter of username to uppercase. 
    user.user_name[0] = toupper(user.user_name[0]);

    // Play music
    PlaySound(TEXT("intro_music.wav"), NULL, SND_ASYNC);

    // Clear console for main menu initiation.
    system("CLS");

    // Greet user and provide their current rank
    // Launch Main Menu do-while loop
    do {
        SetConsoleTextAttribute(hConsole, 8);
        std::cout << "--------------------------------------------------------------------------------";
        std::cout << "\nWelcome to Guess-The-Number, " << user.user_name << "! Your current rank is: " << user.get_rank() << ".\n";
        std::cout << "\n---MAIN MENU--- \n";
        std::cout << "\n0. Quit" << std::endl;
        std::cout << "1. Play Game" << std::endl;
        std::cout << "2. Instructions" << std::endl;
        std::cout << "3. Rank Information" << std::endl;
        std::cout << "4. Toggle Music OFF" << std::endl;
        std::cout << "5. Toggle Music ON" << std::endl;
        std::cout << "\nWhat would you like to do? Type the option number and hit enter: ";
        std::cin >> user_choice;

        if (user_choice == 0) {
            std::cout << "\n---GAME TERMINATED---\n\n";
            exit(0);
        }
        else if (user_choice == 1) {
            system("CLS");
            play_game();
            continue;
        }
        else if (user_choice == 2) {
            system("CLS");
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "\n---INSTRUCTIONS---\n";
            std::cout << ">You have 10 tries to enter a number between 1 and 10.\n";
            std::cout << ">If you guess a wrong number, you lose 1 try.\n";
            std::cout << ">If you enter something that's not a number, you also lose a try.\n";
            std::cout << ">The game will tell you if you're too high or too low, so watch out.\n";

            std::cout << "\n>Press any key to return to the main menu...";
            std::cin.ignore();
            std::cin.get();
            system("CLS");
        }
        else if (user_choice == 3) {
            system("CLS");
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << "\n---RANK INFORMATION---\n";
            std::cout << "You're currently ranked at " << user.get_rank() << ".\n";
            std::cout << ">Each player begins at the lowest rank, Bronze. Ranks are broken-down as follows: \n";
            std::cout << "\t>Bronze = 9-10 tries\n";
            std::cout << "\t>Silver = 6-8 tries\n";
            std::cout << "\t>Gold = 2-5 tries\n";
            std::cout << "\t>Diamond = FIRST TRY!\n";
            std::cout << ">Your rank is recorded and carries with you each game.\n";
            std::cout << ">Promotions and demotions occur depending on how many tries you made vs. your current high score.\n";

            std::cout << "\n>Press any key to return to the main menu...";
            std::cin.ignore();
            std::cin.get();
            system("CLS");
        }
        else if (user_choice == 4) {
            PlaySound(NULL, 0, 0);
            system("CLS");
        }
        else if (user_choice == 5) {
            PlaySound(TEXT("intro_music.wav"), NULL, SND_ASYNC);
            system("CLS");
        }
        else {
            std::cout << "\n---INVALID SELECTION! Please select a valid option.\n";
        }
    } while (user_choice != 0);
}

// Game logic
void play_game() {
    int answer = 0;
    int guess = 0;
    int misses = 0;

    // Create randomization seed
    srand(time(NULL));

    // A number between 1 and 10. + 1 just scales up.
    answer = (rand() % 10) + 1;
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "---GAME STARTED---\n";
    //std::cout << answer;
    std::cout << ">Enter your guess (0 - 10): ";

    while (true && misses < 10 && guess != answer) {
        std::cin >> guess;
        if (std::cin.good()) {
            if (guess == answer) {
                misses++;
                std::cout << "\n>YOU WIN!!! The answer was " << answer << "." << std::endl;
            }
            else if (guess > answer) {
                misses++;
                std::cout << "Too high!" << " You have " << (10 - misses) << " tries left.\n";
            }
            else if (guess < answer) {
                misses++;
                std::cout << "Too low!" << " You have " << (10 - misses) << " tries left.\n";
            }
        }
        else {
            std::cin.clear();
            std::string str;
            std::cin >> str;
            misses++;
            std::cout << "WARNING: Enter a number only. Tries remaining: " << (10 - misses) << ".\n";
            std::cout << ">Enter your guess (0 - 10): ";
        }
    }

    // Rank system START: -------IN PROGRESS--------
    std::ofstream ranks;

    // Number of seconds till returning to main menu
    int counter = 5;
    ranks.open("ranks.txt");
    if (misses <= 1) {
        ranks << "Diamond";
        std::cout << ">You've been promoted to Diamond!!!\n";

        // Automatically return to main menu after 5 seconds AND show it.
        while (counter >= 1)
        {
            std::cout << "\rReturning to main menu in: " << counter << std::flush;
            Sleep(1000);
            counter--;
        }
        system("CLS");
    }
    else if (misses >= 2 && misses <= 5) {
        ranks << "Gold";
        std::cout << ">Your rank has been changed to Gold!\n";
        while (counter >= 1)
        {
            std::cout << "\rReturning to main menu in: " << counter << std::flush;
            Sleep(1000);
            counter--;
        }
        system("CLS");
    }
    else if (misses >= 6 && misses <= 8) {
        ranks << "Silver";
        std::cout << ">Your rank has been changed to Silver!\n";
        while (counter >= 1)
        {
            std::cout << "\rReturning to main menu in: " << counter << std::flush;
            Sleep(1000);
            counter--;
        }
        system("CLS");
    }
    else if (misses >= 9 || misses == 10) {
        ranks << "Bronze";
        std::cout << ">Your rank has been changed to Bronze.\n";
        while (counter >= 1)
        {
            std::cout << "\rReturning to main menu in: " << counter << std::flush;
            Sleep(1000);
            counter--;
        }
        system("CLS");
    }
}