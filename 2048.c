#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 4
#define UP(i, j) (array[(i) + SIZE * (j)])
#define DOWN(i, j) (array[(i) + SIZE * (SIZE - 1 - (j))])
#define LEFT(i, j) (array[SIZE * (i) + (j)])
#define RIGHT(i, j) (array[SIZE * (i) + SIZE - 1 - (j)])
#define SWAP(a, b) ((a) ^= (b) ^= (a) ^= (b))

//cursor position
#define CLEAR() printf("\033[2J") //clear screen
#define SAVE() printf("\033[2s")  //save cursor position
#define SET(x, y) printf("\033[%d;%dH", x, y)
#define SETMSG() SET(2 * SIZE + 4, 0)
#define SETCOM() SET(2 * SIZE + 3, 0)

//font style
#define RESET() printf("\033[0m")
#define RED() printf("\033[31m")

int score;
int array[SIZE * SIZE];

void init()
{
		score = 0;
		for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++)
						LEFT(i, j) = 0;
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
						if (LEFT(i, j) == 0)
								printf("     |");
						else
								printf("%5d|", LEFT(i, j));
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

void up()
{
		for (int i = 0; i < SIZE; i += 1) {
				for (int current = 0; current + 1 < SIZE;) {
						if (UP(i, current) && UP(i, current) == UP(i, current + 1)) { //current == next
								score += UP(i, current);
								UP(i, current) <<= 1;
								UP(i, current + 1) = 0;
						} else if (UP(i, current) && UP(i, current + 1)) { //current != next
								current++;
								continue;
						}
						int j;
						for (j = current + 1; j < SIZE; j++)
								if (UP(i, j))
										break;
						if (j == SIZE || UP(i, j) == 0)
								break;
						if (UP(i, current))
								SWAP(UP(i, current + 1), UP(i, j));
						else
								SWAP(UP(i, current), UP(i, j));
				}
		}
}

void down()
{
		for (int i = 0; i < SIZE; i++) {
				for (int current = 0; current + 1 < SIZE;) {
						if (DOWN(i, current) && DOWN(i, current) == DOWN(i, current + 1)) { //current == next
								score += DOWN(i, current);
								DOWN(i, current) <<= 1;
								DOWN(i, current + 1) = 0;
						} else if (DOWN(i, current) && DOWN(i, current + 1)) { //current != next
								current++;
								continue;
						}
						int j;
						for (j = current + 1; j < SIZE; j++)
								if (DOWN(i, j))
										break;
						if (j == SIZE || DOWN(i, j) == 0)
								break;
						if (DOWN(i, current))
								SWAP(DOWN(i, current + 1), DOWN(i, j));
						else
								SWAP(DOWN(i, current), DOWN(i, j));
				}
		}
}

void left()
{
		for (int i = 0; i < SIZE; i++) {
				for (int current = 0; current + 1 < SIZE;) {
						if (LEFT(i, current) && LEFT(i, current) == LEFT(i, current + 1)) { //current == next
								score += LEFT(i, current);
								LEFT(i, current) <<= 1;
								LEFT(i, current + 1) = 0;
						} else if (LEFT(i, current) && LEFT(i, current + 1)) { //current != next
								current++;
								continue;
						}
						int j;
						for (j = current + 1; j < SIZE; j++)
								if (LEFT(i, j))
										break;
						if (j == SIZE || LEFT(i, j) == 0)
								break;
						if (LEFT(i, current))
								SWAP(LEFT(i, current + 1), LEFT(i, j));
						else
								SWAP(LEFT(i, current), LEFT(i, j));
				}
		}
}

void right()
{
		for (int i = 0; i < SIZE; i++) {
				for (int current = 0; current + 1 < SIZE;) {
						if (RIGHT(i, current) && RIGHT(i, current) == RIGHT(i, current + 1)) { //current == next
								score += RIGHT(i, current);
								RIGHT(i, current) <<= 1;
								RIGHT(i, current + 1) = 0;
						} else if (RIGHT(i, current) && RIGHT(i, current + 1)) { //current != next
								current++;
								continue;
						}
						int j;
						for (j = current + 1; j < SIZE; j++)
								if (RIGHT(i, j))
										break;
						if (j == SIZE || RIGHT(i, j) == 0)
								break;
						if (RIGHT(i, current))
								SWAP(RIGHT(i, current + 1), RIGHT(i, j));
						else
								SWAP(RIGHT(i, current), RIGHT(i, j));
				}
		}
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
				printf("command: ");
				char command = getchar();
				switch (command) {
				case 'w':
						up();
						add();
						print();
						break;
				case 'a':
						left();
						add();
						print();
						break;
				case 's':
						down();
						add();
						print();
						break;
				case 'd':
						right();
						add();
						print();
						break;
				case 'q':
						SETMSG();
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
						RED();
						puts("Invalid input!");
						RESET();
				}
		}
}
