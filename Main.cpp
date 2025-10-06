/* Include guard: */
#ifndef _RNG_GAME_CPP_
#define _RNG_GAME_CPP_

/* Importations: */
#define IMPORT_TERMINAL_COLORS
#include <cutils.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#if defined(_WIN32) || defined(_WIN64)
	#include <direct.h>
	#define MKDIR(dir) _mkdir(dir)
#else
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(dir) mkdir(dir, 0755)
#endif


/* Classes and functions: */
class Game
{
public:
	static long double all_attempts; /* Number of attempts global variable. */
	static long double wins;         /* Number of wins global variable. */
	static long double loses;        /* Number of loses global variable. */

	static void save_data()
	{
		MKDIR("data");
		FILE *statistics = std::fopen("data/statistics.csv", "w");
		std::fprintf(statistics, "%Lf,%Lf,%Lf\n", Game::all_attempts, Game::wins, Game::loses);
		std::fclose(statistics);
	}

	static void load_data()
	{
		FILE *statistics = std::fopen("data/statistics.csv", "r");
		if(!statistics)
		{
			Game::all_attempts = 0.0L, Game::wins = 0.0L, Game::loses = 0.0L;
			save_data();
			return;
		}

		char buffer[BUFSIZ];
		if(std::fgets(buffer, BUFSIZ, statistics) != NULL)
		{
			long double values[3] = {0.0L, 0.0L, 0.0L};
			int itens = std::sscanf(buffer, "%Lf,%Lf,%Lf", &values[0], &values[1], &values[2]);
			if(itens == 3)
			{
				Game::all_attempts = values[0], Game::wins = values[1], Game::loses = values[2];
			}

			else
			{
				Game::all_attempts = 0.0L, Game::wins = 0.0L, Game::loses = 0.0L;
				save_data();
			}
		}

		else
		{
			Game::all_attempts = 0.0L, Game::wins = 0.0L, Game::loses = 0.0L;
			save_data();
		}

		std::fclose(statistics);
	}
};

/* Initialize static variables: */
long double Game::all_attempts = 0.0L;
long double Game::wins = 0.0L;
long double Game::loses = 0.0L;

/* Main code: */
int main()
{
	/* Start seed: */
	std::srand(static_cast<unsigned>(std::time(NULL)));

	/* RNG Game version variables: */
	#define RNG_GAME_FULL_VERSION  201.0L   /* RNG Game full version variable (2.0.1). */
	#define RNG_GAME_MAJOR_VERSION 2.0L     /* RNG Game major version variable (2). */
	#define RNG_GAME_MINOR_VERSION 0.0L     /* RNG Game minor version variable (0). */
	#define RNG_GAME_PATCH_VERSION 1.0L     /* RNG Game patch version variable (1). */

	/* Main variables: */
	#define MIN                    0        /* Minimum value variable. */
	#define MAX                    10       /* Maximum value variable. */
	signed char loop1 = 1;                  /* First loop variable. */
	signed int number;                      /* Number variable. */
	signed int old_random_number;           /* Old random number variable. */
	signed int random_number = rand() % 11; /* Random number between 0 and 10 variable. */
	long double round_attempts = 0.0L;      /* Attempts variable. */
	std::string option1;                    /* First option variable. */
	std::string snumber;                    /* String number variable. */

	/* Initializations before the game (load): */
	enable_vt_and_utf8();
	Game::load_data();

	/* Main loop: */
	while(loop1 == 1)
	{
		CLEAR_TERMINAL();
		puts("========================================");
		printf("============ RNG Game %.0Lf.%.0Lf.%.0Lf ============\n", RNG_GAME_MAJOR_VERSION, RNG_GAME_MINOR_VERSION, RNG_GAME_PATCH_VERSION);
		puts("========================================");
		puts("         [ 0 ] Options...");
		puts("         [ 1 ] Play game!");
		fputs("\t   Your answer: ", stdout);
		std::cin >> std::ws >> option1;
		CLEAR_TERMINAL();

		if(option1 == "0")
		{
			++loop1;

			while(loop1 == 2)
			{
				puts("==================================");
				puts("============ Options =============");
				puts("==================================");
				printf("  %s[ 0 ] Return%s\n", BOLD, BASE_TERMINAL);
				printf("  %s[ 1 ] Save%s and %squit...%s\n", GREEN_COLOR, BASE_TERMINAL, RED_COLOR, BASE_TERMINAL);
				printf("  %s[ 2 ] Change the random number%s\n", CYAN_COLOR, BASE_TERMINAL);
				printf("  %s[ 3 ] View statistics%s\n", YELLOW_COLOR, BASE_TERMINAL);
				printf("  %s[ 4 ] Read \"READ-ME\"%s\n", YELLOW_COLOR, BASE_TERMINAL);
				fputs("\t Your answer: ", stdout);
				std::cin >> std::ws >> option1;

				if(option1 == "0")
				{
					--loop1;
				}

				else if(option1 == "1")
				{
					loop1 = 0, Game::save_data(), CLEAR_TERMINAL();
				}

				else if(option1 == "2")
				{
					CLEAR_TERMINAL();
					old_random_number = random_number;
					printf("Now your attempts have been reseted and the random number has changed to a new value! (Old random number: %d)\n", old_random_number);
					random_number = rand() % 11, round_attempts = 0.0L;
					petc();
					CLEAR_TERMINAL();
				}

				else if(option1 == "3")
				{
					CLEAR_TERMINAL();
					printf("Number of all attempts: %0.Lf\n", Game::all_attempts);
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					printf("Number of wins: %0.Lf\n", Game::wins);
					printf("Number of loses: %0.Lf\n", Game::loses);
					petc();
					CLEAR_TERMINAL();
				}

				else if(option1 == "3.14" || option1 == "3.1415" || option1 == "3.14159" || option1 == "3,14" || option1 == "3,1415" || option1 == "3,14159")
				{
					CLEAR_TERMINAL();
					easter_egg_function();
					CLEAR_TERMINAL();
				}

				else if(option1 == "4")
				{
					CLEAR_TERMINAL();
					read_me();
				}

				else
				{
					CLEAR_TERMINAL();
				}
			}
		}

		else if(option1 == "1")
		{
			printf("Type the number that you think it is (%sMin: 0%s, %sMax: 10%s, if you type another number below 0 it will be rounded to 0, and the same will hapend to the number above 10...): ", BOLD, BASE_TERMINAL, BOLD, BASE_TERMINAL);
			std::cin >> std::ws >> snumber;
			number = atoi(snumber.c_str());
			CLEAR_TERMINAL();
			fputs("Soo... ", stdout);

			if(number > MAX)
			{
				number = MAX;

				if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below 10!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++Game::all_attempts, ++round_attempts, ++Game::loses;
					Game::save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 10!\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					++Game::all_attempts, ++round_attempts, ++Game::wins;
					Game::save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}
			}

			else if(number < MIN)
			{
				number = MIN;

				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above 0!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++Game::all_attempts, ++round_attempts, ++Game::loses;
					Game::save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 0\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					++Game::all_attempts, ++round_attempts, ++Game::wins;
					Game::save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}
			}

			else
			{
				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++Game::all_attempts, ++round_attempts, ++Game::loses;
					Game::save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, number);
					puts("Now the random number has changed to a new value!");
					++Game::all_attempts, ++round_attempts, ++Game::wins;
					Game::save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}

				else if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++Game::all_attempts, ++round_attempts, ++Game::loses;
					Game::save_data();
				}
			}

			petc();
		}
	}

	return 0;
}

/* End code: */
#endif
