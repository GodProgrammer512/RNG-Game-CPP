// Run once time:
#ifndef _RNG_GAME_CPP_
#define _RNG_GAME_CPP_

// Importations:
#include <cutils.h>
#include <iostream>
#include <fstream>
#include <filesystem>


// Global Variables:
long double attempts;      // Number of attempts global variable.
long double wins_percent;  // Percentage of wins global variable.
long double loses_percent; // Percentage of loses global variable.
long double wins;          // Number of wins global variable.
long double loses;         // Number of loses global variable.

// Save statistics function:
void save_data()
{
	if(!std::filesystem::exists("data"))
	{
		std::filesystem::create_directory("data");
	}

	std::ofstream file("data/statistics.csv");
	if(file.is_open())
	{
		file << attempts << "," << wins_percent << "," << loses_percent << "," << wins << "," << loses << "\n";
		file.close();
	}
}

// Load data function:
void load_data()
{
	if(std::filesystem::exists("data/statistics.csv"))
	{
		std::ifstream file("data/statistics.csv");
		std::string line;

		if(file.is_open() && std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string value;

			if(std::getline(ss, value, ',')) {attempts = std::stold(value);}
			if(std::getline(ss, value, ',')) {wins_percent = std::stold(value);}
			if(std::getline(ss, value, ',')) {loses_percent = std::stold(value);}
			if(std::getline(ss, value, ',')) {wins = std::stold(value);}
			if(std::getline(ss, value, ',')) {loses = std::stold(value);}

			file.close();
		}
	}

	else
	{
		attempts = 0.0L, wins_percent = 0.0L, loses_percent = 0.0L, wins = 0.0L, loses = 0.0L;
		save_data();
	}
}

// Main code:
int main()
{
	// Start random seed:
	srand((signed int) time(NULL));

	// Variables:
	#define RNG_GAME_VERSION "3.0.2"        // RNG Game version variable.
	#define MIN 0                           // Minimum value variable.
	#define MAX 10                          // Maximum value variable.
	signed char loop1 = 1;                  // First loop variable.
	signed int number;                      // Number variable.
	signed int old_random_number;           // Old random number variable.
	signed int random_number = rand() % 11; // Random number between 0 and 10 variable.
	std::string option1;                    // First option variable.

	// Initializations:
	enable_vt_and_utf8();
	load_data();

	// Main loop:
	while(loop1 == 1)
	{
		clear_terminal();
		puts("========================================");
		printf("============ RNG Game %s ============\n", RNG_GAME_VERSION);
		puts("========================================");
		printf("         %s[ 0 ] Options...%s\n", RED_COLOR, BASE_TERMINAL);
		puts("         [ 1 ] Play game!");
		fputs("\t   Your answer: ", stdout);
		std::cin >> std::ws >> option1;
		clear_terminal();

		if(option1 == "0")
		{
			++loop1;

			while(loop1 == 2)
			{
				puts("==================================");
				puts("============ Options =============");
				puts("==================================");
				puts("  [ 0 ] Return");
				printf("  %s[ 1 ] Exit...%s\n", RED_COLOR, BASE_TERMINAL);
				puts("  [ 2 ] Read \"READ-ME\"");
				puts("  [ 3 ] View statistics");
				puts("  [ 4 ] Change the random number");
				fputs("\t Your answer: ", stdout);
				std::cin >> std::ws >> option1;

				if(option1 == "0")
				{
					--loop1;
				}

				else if(option1 == "1")
				{
					loop1 = 0, clear_terminal();
				}

				else if(option1 == "2")
				{
					clear_terminal();
					rrmf();
				}

				else if(option1 == "3")
				{
					clear_terminal();
					// Falta colocar as estatisticas aqui (faça tudo em .csv, no caso texto comum, baseado em dados com vírgula).
				}

				else if(option1 == "3.14" || option1 == "3.1415" || option1 == "3.14159" || option1 == "3,14" || option1 == "3,1415" || option1 == "3,14159")
				{
					clear_terminal();
					easter_egg_function();
					clear_terminal();
				}

				else if(option1 == "4")
				{
					clear_terminal();
					old_random_number = random_number;
					printf("Now your attempts have been reseted and the random number has changed to a new value! (Old random number: %d)\n", old_random_number);
					random_number = rand() % 11, attempts = 0.0L;
					petc();
					clear_terminal();
				}

				else
				{
					clear_terminal();
				}
			}
		}

		else if(option1 == "1")
		{
			printf("Type the number that you think it is (%sMin: 0%s, %sMax: 10%s, if you type another number below 0 it will be rounded to 0, and the same will hapend to the number above 10...): ", BOLD, BASE_TERMINAL, BOLD, BASE_TERMINAL);
			scanf("%d", &number);
			clear_terminal();
			fputs("Soo... ", stdout);

			if(number > MAX)
			{
				number = MAX;

				if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below 10!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++attempts;
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 10!\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					printf("Number of attempts: %0.Lf\n", attempts + 1.0L);
					attempts = 0.0L;
					random_number = rand() % 11;
				}
			}

			else if(number < MIN)
			{
				number = MIN;

				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above 0!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++attempts;
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 0\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					printf("Number of attempts: %0.Lf\n", attempts + 1.0L);
					attempts = 0.0L;
					random_number = rand() % 11;
				}
			}

			else
			{
				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++attempts;
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, number);
					puts("Now the random number has changed to a new value!");
					printf("Number of attempts: %0.Lf\n", attempts + 1.0L);
					attempts = 0.0L;
					random_number = rand() % 11;
				}

				else if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++attempts;
				}
			}

			petc();
		}
	}

	return 0;
}

// End code:
#endif
