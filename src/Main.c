// Importations:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cutils.h>


// Main code:
int main(void)
{
	// Start random seed:
	srand((unsigned int) time(NULL));

	// Variables:
	#define MIN 0
	#define MAX 10
	unsigned char loop1 = 1u;
	signed int number, old_random_number, random_number = rand() % 11;
	long double option1, attempts = 0.0L;

	while(loop1)
	{
		clear_terminal();
		puts("==================================");
		puts("============ RNG Game ============");
		puts("==================================");
		printf("  %s[ 0 ] Exit...%s\n", RED_COLOR, BASE_TERMINAL);
		puts("  [ 1 ] Read \"READ-ME\"");
		puts("  [ 2 ] Change the random number");
		puts("  [ 3 ] Play game!");
		fputs("\t Your answer: ", stdout);
		scanf("%Lf", &option1);
		clear_terminal();

		if(option1 == 0.0L)
		{
			--loop1;
		}

		else if(option1 == 1.0L)
		{
			rrmf();
		}

		else if(option1 == 2.0L)
		{
			old_random_number = random_number;
			printf("Now your attempts have been reseted and the random number has changed to a new value! (Old random number: %d)\n", old_random_number);
			random_number = rand() % 11;
			attempts = 0.0L;
			petc();
		}

		else if(option1 == 3.0L)
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

		else if(option1 == 3.14L || option1 == 3.1415L)
		{
			easter_egg_function();
		}
	}

	return 0;
}
