#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 4
#define ARRAY(i, j) (array[SIZE * (i) + (j)])
#define SWAP(a, b) ((a) ^= (b) ^= (a) ^= (b))

// cursor position
#define CLEAR() printf("\033[2J") // clear screen
#define CLEAR_LINE() printf("\r\033[K") //clear line
#define SET(x, y) printf("\033[%d;%dH", x, y)
#define SETCOM() SET(2 * SIZE + 3, 0)
#define SETMSG() SET(2 * SIZE + 4, 0)

// font style
#define RESET() printf("\033[0m")
#define RED() printf("\033[31m")

int score;
int array[SIZE * SIZE];

void init()
{
		score = 0;
		for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
						ARRAY(i, j) = 0;
}

void print()
{
		CLEAR();
		SET(0, 0);
		printf("Score: %d\n", score);
		printf("|");
		for (int i = 0; i < SIZE; i++)
				printf("-----|");
		puts("");
		for (int i = 0; i < SIZE; i++) {
				printf("|");
				for (int j = 0; j < SIZE; j++)
						if (ARRAY(i, j) == 0)
								printf("     |");
						else
								printf("%5d|", ARRAY(i, j));
				puts("");
				printf("|");
				for (int i = 0; i < SIZE; i++)
						printf("-----|");
				puts("");
		}
}

void add()
{
		int index;
		while (1) {
				index = rand() % (SIZE * SIZE);
				if (array[index] == 0)
						break;
		}
		array[index] = 2;
}

void squeeze(int *(*array)(int, int))
{
		for (int i = 0; i < SIZE; i++) {
				for (int current = 0; current + 1 < SIZE;) {
						if (*array(i, current) &&
							*array(i, current) == *array(i, current + 1)) {
								score += *array(i, current);
								*array(i, current) <<= 1;
								*array(i, current + 1) = 0;
						} else if (*array(i, current) && *array(i, current + 1)) {
								current++;
								continue;
						}
						int j;
						for (j = current + 1; j < SIZE; j++)
								if (*array(i, j))
										break;
						if (j == SIZE || *array(i, j) == 0)
								break;
						if (*array(i, current))
								SWAP(*array(i, current + 1), *array(i, j));
						else
								SWAP(*array(i, current), *array(i, j));
				}
		}
}

int *up(int i, int j)
{
		return &array[i + SIZE * j];
}

int *down(int i, int j)
{
		return &array[i + SIZE * (SIZE - 1 - j)];
}

int *left(int i, int j)
{
		return &array[SIZE * i + j];
}

int *right(int i, int j)
{
		return &array[SIZE * i + SIZE - 1 - j];
}

int main()
{
		srand(time(0));
start:
		init();
		CLEAR();
		add();
		print();
		while (1) {
				SETCOM();
				CLEAR_LINE();
				printf("command: ");
				char command = getchar();
				switch (command) {
				case 'w':
						squeeze(up);
						add();
						print();
						break;
				case 'a':
						squeeze(left);
						add();
						print();
						break;
				case 's':
						squeeze(down);
						add();
						print();
						break;
				case 'd':
						squeeze(right);
						add();
						print();
						break;
				case 'q':
						SETMSG();
						CLEAR_LINE();
						RED();
						puts("Game Over!");
						RESET();
						return 0;
				case 'r':
						goto start;
				case '\n':
						break;
				default:
						SETMSG();
						CLEAR_LINE();
						RED();
						puts("Invalid input!");
						RESET();
				}
		}
}
