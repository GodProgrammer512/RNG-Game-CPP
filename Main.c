#ifndef _RNG_GAME_C_
#define _RNG_GAME_C_

// Importations:
#include <cutils.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Main code:
int main(void)
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
	long double option1;                    // First option variable.
	long double attempts = 0.0L;            // Number of attempts variable.

	// Enable Vitrual Terminal and use UTF-8:
	enable_vt_and_utf8();

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
		scanf("%Lf", &option1);
		clear_terminal();

		if(option1 == 0.0L)
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
				scanf("%Lf", &option1);

				if(option1 == 0.0L)
				{
					--loop1;
				}

				else if(option1 == 1.0L)
				{
					loop1 = 0, clear_terminal();
				}

				else if(option1 == 2.0L)
				{
					clear_terminal();
					rrmf();
				}

				else if(option1 == 3.0L)
				{
					clear_terminal();
					// Falta colocar as estatisticas aqui (faça tudo em .csv, no caso texto comum, baseado em dados com vírgula).
				}

				else if(option1 == 3.14L || option1 == 3.1415L)
				{
					clear_terminal();
					easter_egg_function();
					clear_terminal();
				}

				else if(option1 == 4.0L)
				{
					clear_terminal();
					old_random_number = random_number;
					printf("Now your attempts have been reseted and the random number has changed to a new value! (Old random number: %d)\n", old_random_number);
					random_number = rand() % 11, attempts = 0.0L;
					petc();
					clear_terminal();
				}
			}
		}

		else if(option1 == 1.0L)
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

#endif
