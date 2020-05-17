/*********************************************
 -------------Creator: Trung Xì---------------*/
 
#include <stdio.h>
#include "console.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <string>
#include <iostream>
using namespace std;

int ColorWall = 11;
int ColorSnake = 10;
int ColorSnake2 = 12;
int ColorFruit = 14;
int ColorTable = 15;

int Width = 40;
int	Height = 20;
int defaultWidth = Width;
int defaultHeight = Height;

#define len			4

#define Head		233
#define Body		111
#define Fruit		232
#define Impediment	177
#define WallTop		220
#define WallBottom	223
#define WallEdge	219

enum Status {UP, DOWN, LEFT, RIGHT};
enum Level {HARD = 20, NORMAL = 25, EASY = 30, CUSTOM = 31};

#define MAXPLAYER 11
struct player {
	char name[13];
	int score;
}player[MAXPLAYER];

struct toado {
	int x, y;
};

struct snake {
	toado dot[1000];
	int n;
	Status sta;
}snake, snake2;

struct fruit {
	toado toado;
}fruit;

struct impe {
	toado toado;
	Status sta = DOWN;
}impe, impe2, impe3;

int TIME = 155;
Level level = EASY;
int numOfSnake = 1;
int numOfImpe = 1;
int MODE = 1;
FILE *info;

void hidePointer();

void createSnake();
void createFruit();
void createImpe();

void display();
void displayWall();
void displayOver(int over);
void displayInfo(Level level);
void dynamicText(char text[]);
void printInfo();

int handling();
void controlMove();
void testScore();

void readInfo();
void updateInfo();

int Menu(int &choose, int option);

int main() {
	int over, choose = 1;
	hidePointer();
	readInfo();
	int color[6] = {10, 11, 12, 13, 14, 15};
	int numColor = 6;
	int timeTmp;
	int key = 0;
	int tmpW = defaultWidth;
	int tmpH = defaultHeight;
	int maxW = 90, minW = 20, maxH = 29, minH = 15;
	char ran[] = "RANDOM";
	while (choose != 0) {
		choose = 1;

		clrscr();
		displayWall();

		gotoXY(Width / 2 - 2 * len, Height / 2 - 7);
		puts("*** SNAKE GAME ***");
		gotoXY(Width / 2 - len, Height / 2 -4);
		puts("NEW GAME");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
		puts("LEVEL");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
		puts("MODE");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
		puts("SETTING");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 8);
		puts("HIGH SCORE");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 10);
		puts("ABOUT");
		gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
		puts("EXIT");
		choose = Menu(choose, 7);
		switch(choose) {
			case 1: 
				choose = 1;
				clrscr();
				displayWall();
				gotoXY(Width / 2 - len - 1, Height / 2 - 4 - 3);
				puts("CHOOSE MODE: ");
				gotoXY(Width / 2 - len, Height / 2 - 4 );
				puts("1 PLAYER");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				puts("2 PLAYER");
				choose = Menu(choose, 2);

				switch (choose) {
				case 1:
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 1;
					break;
				case 2:
					if (level == EASY)
						TIME = 155;
					else if (level == NORMAL)
						TIME = 95;
					else if (level == HARD)
						TIME = 50;
					numOfSnake = 2;
					TIME -= TIME/7;
					break;
				}
				createSnake();
				createFruit();
				if (MODE == 2)
					createImpe();
				break;
			case 2:
				choose = 1;
				clrscr();
				displayWall();
				gotoXY(Width / 2 - len, Height / 2 - 4);
				puts("EASY");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				puts("NORMAL");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
				puts("HARD");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
				puts("CUSTOM");
				choose = Menu(choose, 4);

				switch (choose) {

				case 1:
					level = EASY;
					TIME = 155;
					numOfImpe = 1;
					clrscr();
					break;
				case 2:
					level = NORMAL;
					TIME = 95;
					numOfImpe = 2;
					clrscr();
					break;
				case 3:
					level = HARD;
					TIME = 50;
					numOfImpe = 3;
					clrscr();
					break;
				case 4:
					level = CUSTOM;
					timeTmp = TIME;
					key = 0;
					clrscr();
					displayWall();
					gotoXY(Width / 2 - 2*len, Height / 2 -2);
					puts("ENTER SLEEP TIME: ");
					while (key != 13) {
						gotoXY(Width / 2 - 2*len, Height / 2);
						cout  << timeTmp << " ";
						key = _getch();
						if ((key == 'w' || key == 'W' || key == 72) && timeTmp < 200)
							timeTmp++;
						else if ((key == 's' || key == 'S' || key == 80) && timeTmp > 10)
							timeTmp--;
					}
					TIME = timeTmp;
					break;
				}
				continue;
			case 3:
				choose = 1;

				clrscr();
				displayWall();
				gotoXY(Width / 2 - len - 1, Height / 2 - 4 - 3);
				puts("CHOOSE MODE: ");
				gotoXY(Width / 2 - len, Height / 2 - 4);
				puts("CLASSIC");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				puts("SURVIVAL");
				choose = Menu(choose, 2);

				switch (choose) {
				case 1:
					MODE = 1;
					break;
				case 2:
					MODE = 2;
					break;
				}
				continue;
			case 4:
				choose = 1;

				clrscr();
				displayWall();
				gotoXY(Width / 2 - len, Height / 2 - 4);
				puts("COLOR CUSTOM");
				gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
				puts("WALL CUSTOM");
				choose = Menu(choose, 2);

				switch (choose) {
				
				case 1:
					choose = 1;
					clrscr();
					displayWall();

					gotoXY(Width / 2 - len, Height / 2 - 4);
					puts("PLAYER 1");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
					puts("PLAYER 2");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 4);
					puts("FRUIT COLOR");
					gotoXY(Width / 2 - len, Height / 2 - 4 + 6);
					puts("WALL COLOR");
					choose = Menu(choose, 4);
					switch (choose) {
					case 1:
						choose = 1;
						clrscr();
						displayWall();
		
						for (int i = 0, j = 0; i < numColor; i++, j+=2) {
							TextColor(color[i]);
							gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
							putchar(Head);
							for (int i = 0; i < 5; i++) {
								gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
								putchar(Body);
							}
						}
						gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
						for (int i = 0; i < 6; i++) {
							TextColor(color[i]);
							cout << ran[i];
						}
						choose = Menu(choose, 7);
						switch (choose) {
						case 1:
							ColorSnake = 10;
							break;
						case 2:
							ColorSnake = 11;
							break;
						case 3:
							ColorSnake = 12;
							break;
						case 4:
							ColorSnake = 13;
							break;
						case 5:
							ColorSnake = 14;
							break;
						case 6:
							ColorSnake = 15;
							break;
						case 7:
							srand((int)time(NULL));
							ColorSnake = 1 + rand() % 15;
							break;
						}
						break;
					case 2:
						choose = 1;
						clrscr();
						displayWall();

						for (int i = 0, j = 0; i < numColor; i++, j += 2) {
							TextColor(color[i]);
							gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
							putchar(Head);
							for (int i = 0; i < 5; i++) {
								gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
								putchar(Body);
							}
						}
						gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
						for (int i = 0; i < 6; i++) {
							TextColor(color[i]);
							cout << ran[i];
						}
						choose = Menu(choose, 7);
						switch (choose) {
						case 1:
							ColorSnake2 = 10;
							break;
						case 2:
							ColorSnake2 = 11;
							break;
						case 3:
							ColorSnake2 = 12;
							break;
						case 4:
							ColorSnake2 = 13;
							break;
						case 5:
							ColorSnake2 = 14;
							break;
						case 6:
							ColorSnake2 = 15;
							break;
						case 7:
							srand((int)time(NULL));
							ColorSnake2 = 1 + rand() % 15;
							break;
						}
						break;
					case 3:
						choose = 1;
						clrscr();
						displayWall();

						for (int i = 0, j = 0; i < numColor; i++, j += 2) {
							TextColor(color[i]);
							gotoXY(Width / 2 - len + 5, Height / 2 - 4 + j);
							putchar(Fruit);
						}
						gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
						for (int i = 0; i < 6; i++) {
							TextColor(color[i]);
							cout << ran[i];
						}
						choose = Menu(choose, 7);
						switch (choose) {
						case 1:
							ColorFruit = 10;
							break;
						case 2:
							ColorFruit = 11;
							break;
						case 3:
							ColorFruit = 12;
							break;
						case 4:
							ColorFruit = 13;
							break;
						case 5:
							ColorFruit = 14;
							break;
						case 6:
							ColorFruit = 15;
							break;
						case 7:
							srand((int)time(NULL));
							ColorFruit = 1 + rand() % 15;
							break;
						}
						break;
					case 4:
						choose = 1;
						clrscr();
						displayWall();
						for (int i = 0, j = 0; i < numColor; i++, j += 2) {
							TextColor(color[i]);
							for (int i = 0; i < 8; i++) {
								gotoXY(Width / 2 - len + i, Height / 2 - 4 + j);
								putchar(WallTop);
							}
						}
						gotoXY(Width / 2 - len, Height / 2 - 4 + 12);
						for (int i = 0; i < 6; i++) {
							TextColor(color[i]);
							cout << ran[i];
						}
						choose = Menu(choose, 7);
						switch (choose) {
						case 1:
							ColorWall = 10;
							break;
						case 2:
							ColorWall = 11;
							break;
						case 3:
							ColorWall = 12;
							break;
						case 4:
							ColorWall = 13;
							break;
						case 5:
							ColorWall = 14;
							break;
						case 6:
							ColorWall = 15;
							break;
						case 7:
							srand((int)time(NULL));
							ColorWall = 1 + rand() % 15;
							break;
						}
						break;
					}
					break;
				case 2:
					choose = 1;
					clrscr();
					displayWall();
					gotoXY(Width / 2 - len, Height / 2 - 4);
					puts("DEFAULT");
					gotoXY(Width / 2 - 3 * len, Height / 2 - 4 + 1);
					cout << "(Width: " << defaultWidth << ", Height : " << defaultHeight << ")";
					gotoXY(Width / 2 - len, Height / 2 - 4 + 2);
					puts("CUSTOM");

					choose = Menu(choose, 2);
					switch (choose) {

					case 1:
						clrscr();
						Width = defaultWidth;
						Height = defaultHeight;
						break;
					case 2:
						clrscr();
						displayWall();

						gotoXY(Width / 2 - 10, Height / 2 - 4);
						cout << "Num Of WIDTH (MAX: " << maxW << ",MIN: " << minW << ")";
						while (1) {
							gotoXY(Width / 2 + 4, Height / 2 - 4 + 1);
							cin >> tmpW;
							if (tmpW > maxW || tmpW < minW) {
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 1);
								cout << "Please ENTER again:      ";
								continue;
							}
							if (tmpW <= maxW && tmpW >= minW)
								break;
						}
						fflush(stdin);
						gotoXY(Width / 2 - 10, Height / 2 - 4 + 4);
						cout << "Num Of Height(MAX: " << maxH << ",MIN: " << minH << ")";
						while (1) {
							gotoXY(Width / 2 + 4, Height / 2 - 4 + 5);
							cin >> tmpH;
							if (tmpH > maxH || tmpH < minH) {
								gotoXY(Width / 2 - 4 * 2, Height / 2 - 4 + 5);
								cout << "Please ENTER again:      ";
								continue;
							}
							else if (tmpH <= maxH && tmpH >= minH)
								break;
						}
						Height = tmpH;
						Width = tmpW;
						break;
					}
					break;
				}
				continue;
			case 5:
				clrscr();
				displayWall();
				printInfo();
				_getch();
				continue;
			case 6:
				clrscr();
				displayWall();
				gotoXY(Width / 2 - 2 * len, Height / 2 - 1);
				puts("Creator: Trung Xi");
				_getch();
				continue;
			case 7:
				while (1) {
					gotoXY(Width / 2 - len - 2, Height / 2 - 4 + 12);
					puts("EXIT GAME....");
					Sleep(250);
					gotoXY(Width / 2 - len - 2, Height / 2 - 4 + 12);
					for (int i = 0; i < strlen("EXIT GAME...."); i++) {
						cout << " ";
					}
					Sleep(250);
					if (_kbhit()) {
						if (_getch() == 13)
							break;
					}
				}
				break;
		}
		if (choose == 7) {
			updateInfo();
			break;
		}
		clrscr();
		display();
		displayWall();
		dynamicText("PRESS ENTER");

		while (1) {
			// move
			controlMove();
			// display
			display();
			// handling
			over = handling();
			if (numOfSnake == 1) {
				if (over == -1 || over == 1){
					displayOver(over);
					testScore();
					break;
				}
			if (snake.sta == UP || snake.sta == DOWN)
				Sleep(TIME+(TIME / 2));
			else Sleep(TIME);
			}

			else if (numOfSnake == 2) {
				if (over == -2 || over == 2 || over == 3) {
					displayOver(over);
					clrscr();
					break;
				}
				if (snake.sta == UP || snake.sta == DOWN || snake2.sta == UP || snake2.sta == DOWN)
					Sleep(TIME + (TIME / 2));
				else Sleep(TIME);
				Sleep(TIME);
			}
		}
	}
	return 0;
}

void hidePointer() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void createSnake() {
	//snake 1
	snake.n = 5;
	for (int i = snake.n - 1, j = 2; i >= 0; i--, j++) {
		snake.dot[i].x = j;
		snake.dot[i].y = 2;
	}
	snake.sta = RIGHT;
	// snake 2
	if (numOfSnake == 2) {
		snake2.n = 5;
		for (int i = snake2.n - 1, j = 2; i >= 0; i--, j++) {
			snake2.dot[i].x = j;
			snake2.dot[i].y = Height - 5;
		}
		snake2.sta = RIGHT;
	}
}
void createFruit() {
	srand((unsigned int)time(0));
	int flag = 0;
	while (1) {
		flag = 0;
		fruit.toado.x = 1 + rand() % (Width - 1);
		fruit.toado.y = 1 + rand() % (Height - 1);
		for (int i = 0; i < snake.n; i++) {
			if (snake.dot[i].x == fruit.toado.x && snake.dot[i].y == fruit.toado.y)
				flag = 1;
			else if (snake2.dot[i].x == fruit.toado.x && snake2.dot[i].y == fruit.toado.y)
				flag = 1;
		}
		if (fruit.toado.x == 0 && fruit.toado.y == 0)
			flag = 1;
		if (flag == 0)
			break;
	}
}
void createImpe() {
	if (numOfImpe == 1) {
		impe.toado.x = Width / 2;
		impe.toado.y = 2;
		impe.sta = UP;
	}
	else if (numOfImpe == 2) {
		impe.toado.x = Width / 2 - Width / 4;
		impe.toado.y = 2;
		impe.sta = DOWN;

		impe2.toado.x = Width / 2 + Width / 4;
		impe2.toado.y = Height - 1;
		impe2.sta = UP;
	}
	else if (numOfImpe == 3) {
		impe.toado.x = Width / 2 - Width / 3 + 1;
		impe.toado.y = 2;
		impe.sta = DOWN;

		impe2.toado.x = Width / 2;
		impe2.toado.y = Height / 2;
		impe2.sta = UP;

		impe3.toado.x = Width / 2 + Width / 3;
		impe3.toado.y = Height - 1;
		impe3.sta = UP;
	}
}

void displayInfo(Level level) {

	TextColor(ColorTable);
	gotoXY(Width + 3, 1);
	printf("LEVEL: ");

	if (level == EASY) {
		TextColor(ColorCode_Green);
		puts("EASY");
	}
	else if (level == NORMAL) {
		TextColor(ColorCode_Yellow);
		puts("NORMAL");
	}
	else if (level == HARD) {
		TextColor(ColorCode_Red);
		puts("HARD");
	}
	else if (level == CUSTOM) {
		TextColor(ColorCode_Grey);
		puts("CUSTOM");
	}

	TextColor(ColorTable);
	gotoXY(Width + 3, 3);
	printf("PLAYER 1'S SCORE: ");

	TextColor(ColorSnake);
	printf("%d", snake.n - 5);

	if (numOfSnake == 2) {
		TextColor(ColorTable);
		gotoXY(Width + 3, 5);
		printf("PLAYER 2'S SCORE: ");

		TextColor(ColorSnake2);
		printf("%d", snake2.n - 5);

	}
}

void display() {
	displayInfo(level);

	TextColor(ColorFruit);
	gotoXY(fruit.toado.x, fruit.toado.y);
	putchar(Fruit);

	//snake 1
	TextColor(ColorSnake);
	for (int i = 1; i < snake.n; i++) {
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		putchar(Body);
	}
	gotoXY(snake.dot[snake.n - 1].x, snake.dot[snake.n - 1].y);
	putchar(' ');
	gotoXY(snake.dot[0].x, snake.dot[0].y);
	putchar(Head);

	// snake 2
	if (numOfSnake == 2) {
		TextColor(ColorSnake2);
		for (int i = 1; i < snake.n; i++) {
			gotoXY(snake2.dot[i].x, snake2.dot[i].y);
			putchar(Body);
		}
		gotoXY(snake2.dot[snake2.n - 1].x, snake2.dot[snake2.n - 1].y);
		putchar(' ');
		gotoXY(snake2.dot[0].x, snake2.dot[0].y);
		putchar(Head);
	}
	if (MODE == 2) {
		TextColor(ColorCode_Red);
		gotoXY(impe.toado.x, impe.toado.y);
		putchar(Impediment);
		if (numOfImpe >= 2) {
			gotoXY(impe2.toado.x, impe2.toado.y);
			putchar(Impediment);
		}
		if (numOfImpe == 3) {
			gotoXY(impe3.toado.x, impe3.toado.y);
			putchar(Impediment);
		}
	}
}
// paint wall;
void displayWall() {
	TextColor(ColorWall);
	for (int i = 0; i <= Height; i++) {
		gotoXY(Width, i);
		putchar(WallEdge);
		gotoXY(0, i);
		putchar(WallEdge);
	}
	for (int i = 0; i <= Width; i++) {
		gotoXY(i, 0);
		putchar(WallTop);
		gotoXY(i, Height);
		putchar(WallBottom);
	}
}

void dynamicText(char text[]) {
	while (1) {
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		puts(text);
		Sleep(250);
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		for (int i = 0; i < strlen(text); i++) {
			cout << " ";
		}
		Sleep(250);
		if (_kbhit()) {
			if (_getch() == 13)
				break;
		}
	}
}

void displayOver(int over) {
	if (over == -1) {
		dynamicText("GAME OVER !!!");
	}
	else if (over == 1) {
		gotoXY((Width / 2) - len - 3, Height / 2 - 1);
		dynamicText("YOU WON !!!");
	}
	else if (over == 2) {
		TextColor(ColorSnake2);
		dynamicText("PLAYER 2 WON !!!");
	}
	else if (over == -2) {
		TextColor(ColorSnake);
		dynamicText("PLAYER 1 WON !!!");
	}
	else if (over == 3) {
		TextColor(ColorCode_Cyan);
		dynamicText("MATCH DRAW !!!");
	}
}

void controlMove() {
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];

	for (int i = snake2.n - 1; i > 0; i--)
		snake2.dot[i] = snake2.dot[i - 1];

	if (_kbhit()) {
		int key = _getch();

		//snake 1
		if ((key == 'w' || key == 'W') && snake.sta != DOWN)
			snake.sta = UP;
		else if ((key == 's' || key == 'S') && snake.sta != UP)
			snake.sta = DOWN;
		else if ((key == 'd' || key == 'D') && snake.sta != LEFT)
			snake.sta = RIGHT;
		else if ((key == 'a' || key == 'A') && snake.sta != RIGHT)
			snake.sta = LEFT;

		//snake 2
		if (numOfSnake == 2) {
			if ((key == 53) && snake2.sta != DOWN)
				snake2.sta = UP;
			else if ((key == 50) && snake2.sta != UP)
				snake2.sta = DOWN;
			else if ((key == 51) && snake2.sta != LEFT)
				snake2.sta = RIGHT;
			else if ((key == 49) && snake2.sta != RIGHT)
				snake2.sta = LEFT;
		}
	}
	//snake 1
	if (snake.sta == UP)
		snake.dot[0].y--;
	else if (snake.sta == DOWN)
		snake.dot[0].y++;
	else if (snake.sta == LEFT)
		snake.dot[0].x--;
	else if (snake.sta == RIGHT)
		snake.dot[0].x++;

	//snake 2
	if (numOfSnake == 2) {
		if (snake2.sta == UP)
			snake2.dot[0].y--;
		else if (snake2.sta == DOWN)
			snake2.dot[0].y++;
		else if (snake2.sta == LEFT)
			snake2.dot[0].x--;
		else if (snake2.sta == RIGHT)
			snake2.dot[0].x++;
	}
	// impe
	if (MODE == 2) {
		gotoXY(impe.toado.x, impe.toado.y);
		cout << " ";
		if (impe.sta == UP)
			impe.toado.y--;
		else if (impe.sta == DOWN)
			impe.toado.y++;
		else if (impe.sta == LEFT)
			impe.toado.x--;
		else if (impe.sta == RIGHT)
			impe.toado.x++;

		if (numOfImpe >= 2) {
			gotoXY(impe2.toado.x, impe2.toado.y);
			cout << " ";
			if (impe2.sta == UP)
				impe2.toado.y--;
			else if (impe2.sta == DOWN)
				impe2.toado.y++;
			else if (impe2.sta == LEFT)
				impe2.toado.x--;
			else if (impe2.sta == RIGHT)
				impe2.toado.x++;
		}
		if (numOfImpe == 3) {
			gotoXY(impe3.toado.x, impe3.toado.y);
			cout << " ";
			if (impe3.sta == UP)
				impe3.toado.y--;
			else if (impe3.sta == DOWN)
				impe3.toado.y++;
			else if (impe3.sta == LEFT)
				impe3.toado.x--;
			else if (impe3.sta == RIGHT)
				impe3.toado.x++;
		}
	}
}

int handling() {
	// handling eat fruit
	if (snake.dot[0].x == fruit.toado.x && snake.dot[0].y == fruit.toado.y) {
		snake.dot[snake.n] = snake.dot[snake.n - 1];
		snake.n++;
		createFruit();
		if (MODE == 2) {
			TIME -= 3;
		}
	}
	if (numOfSnake == 2) {
		if (snake2.dot[0].x == fruit.toado.x && snake2.dot[0].y == fruit.toado.y) {
			snake2.dot[snake.n] = snake2.dot[snake.n - 1];
			snake2.n++;
			createFruit();
		}
	}
	if (MODE == 2) {
		// xu ly cham bien
		if (impe.toado.y >= Height - 1) {
			impe.sta = UP;
		}
		else if (impe.toado.y <= 1) {
			impe.sta = DOWN;
		}
		if (numOfImpe >= 2) {
			if (impe2.toado.y >= Height - 1) {
				impe2.sta = UP;
			}
			else if (impe2.toado.y <= 1) {
				impe2.sta = DOWN;
			}
		}
		if (numOfImpe == 3) {
			if (impe3.toado.y >= Height - 1) {
				impe3.sta = UP;
			}
			else if (impe3.toado.y <= 1) {
				impe3.sta = DOWN;
			}
		}
	}
	switch (numOfSnake) {
	case 1:
		// xu ly cham tuong
		if (snake.dot[0].x <= 0 || snake.dot[0].x >= Width || snake.dot[0].y >= Height || snake.dot[0].y <= 0)
			return -1;
		// xu ly cham than
		for (int i = 4; i < snake.n; i++) {
			if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				return -1;
		}
		if (MODE == 2) {
			// xu ly thang
			if (snake.n == level)
				return 1;
			// cham chung ngai vat
			for (int i = 0; i < snake.n - 1; i++) {
				if (snake.dot[i].x == impe.toado.x && snake.dot[i].y == impe.toado.y)
					return -1;
			}
			if (numOfImpe >= 2) {
				// cham chung ngai vat
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe2.toado.x && snake.dot[i].y == impe2.toado.y)
						return -1;
				}
			}
			if (numOfImpe == 3) {
				// cham chung ngai vat
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe3.toado.x && snake.dot[i].y == impe3.toado.y)
						return -1;
				}
			}
		}
		return 0;
	case 2:
		//handling touch border, body
		if (snake.dot[0].x <= 0 || snake.dot[0].x >= Width || snake.dot[0].y >= Height || snake.dot[0].y <= 0)
			return 2;
		if (snake2.dot[0].x <= 0 || snake2.dot[0].x >= Width || snake2.dot[0].y >= Height || snake2.dot[0].y <= 0)
			return -2;

		for (int i = 4; i < snake.n; i++) {
			if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				return 2;
		}
		for (int i = 4; i < snake2.n; i++) {
			if (snake2.dot[0].x == snake2.dot[i].x && snake2.dot[0].y == snake2.dot[i].y)
				return -2;
		}

		//handling touch together
		for (int i = 1; i < snake.n - 1; i++) {
			if (snake2.dot[0].x == snake.dot[i].x && snake2.dot[0].y == snake.dot[i].y)
				return -2;
		}
		for (int i = 1; i < snake2.n - 1; i++) {
			if (snake.dot[0].x == snake2.dot[i].x && snake.dot[0].y == snake2.dot[i].y)
				return 2;
		}
		if ((snake.dot[0].x == snake2.dot[0].x && snake.dot[0].y == snake2.dot[0].y) || (snake2.dot[0].x == snake.dot[0].x && snake2.dot[0].y == snake.dot[0].y))
			return 3;

		if (MODE == 2) {
			// xu ly thang
			if (snake.n == level)
				return -2;
			else if (snake2.n == level)
				return 2;
			// xu ly cham chuong ngai vat
			for (int i = 0; i < snake.n - 1; i++) {
				if (snake.dot[i].x == impe.toado.x && snake.dot[i].y == impe.toado.y)
					return 2;
			}
			for (int i = 0; i < snake2.n - 1; i++) {
				if (snake2.dot[i].x == impe.toado.x && snake2.dot[i].y == impe.toado.y)
					return -2;
			}
			if (numOfImpe >= 2) {
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe2.toado.x && snake.dot[i].y == impe2.toado.y)
						return 2;
				}
				for (int i = 0; i < snake2.n - 1; i++) {
					if (snake2.dot[i].x == impe2.toado.x && snake2.dot[i].y == impe2.toado.y)
						return -2;
				}
			}
			if (numOfImpe == 3) {
				for (int i = 0; i < snake.n - 1; i++) {
					if (snake.dot[i].x == impe3.toado.x && snake.dot[i].y == impe3.toado.y)
						return 2;
				}
				for (int i = 0; i < snake2.n - 1; i++) {
					if (snake2.dot[i].x == impe3.toado.x && snake2.dot[i].y == impe3.toado.y)
						return -2;
				}
			}
		}
	}
	return 0;
}

int Menu(int &choose, int option) {
	int key = 0;
	int leng = len + 5;
	while (key != 13) {
		for (int i = 0; i < option * 2; i += 2) {
			gotoXY(Width / 2 - leng, Height / 2 - 4 + i);
			cout << ' ';
		}
		if ((key == 'w' || key == 'W' || key == 72) && choose > 1)
			choose--;
		else if ((key == 's' || key == 'S' || key == 80) && choose < option)
			choose++;

		for (int i = 0; i <= option * 2; i += 2) {
			if (choose == i / 2 + 1) {
				gotoXY(Width / 2 - leng, Height / 2 - 4 + i);
				putchar(175);
			}
		}
		key = _getch();
	}
	return choose;
}
void readInfo() {
	info = fopen("Player Info.txt", "r");
	if (info != NULL) {
		for (int i = 0; i < MAXPLAYER - 1; i++) {
			fgets(player[i].name, 14, info);
			fscanf(info, "%d", &player[i].score);
			fseek(info, 2, SEEK_CUR);
		}
		fclose(info);
	}
	else puts("FILE ERROR !");

	// sort
	for (int i = 0; i < MAXPLAYER - 1; i++) {
		for (int j = i; j < MAXPLAYER - 1; j++) {
			if (player[j].score > player[i].score) {
				player[10] = player[j];
				player[j] = player[i];
				player[i] = player[10];
			}
		}
	}

}
void printInfo() {
	for (int i = 0, j = 0; i < MAXPLAYER - 1; i++, j += 2) {
		gotoXY(Width / 2 - 2 * len - 2, Height / 2 - 9 + j);
		printf("%2d. %-13s\t%d", i + 1, player[i].name, player[i].score);
	}
}
void updateInfo() {
	info = fopen("Player Info.txt", "w+");
	if (info != NULL) {
		for (int i = 0; i < MAXPLAYER - 1; i++) {
			fprintf(info, "%13s%d\n", player[i].name, player[i].score);
		}
		fclose(info);
	}
	else puts("FILE ERROR !");
}
void testScore() {
	int i;
	char tmp[100];
	clrscr();
	displayWall();
	for (i = 0; i < 10; i++) {
		if (snake.n - 5 >= player[i].score) {
			fflush(stdin);
			gotoXY(Width / 2 - 3 * len, Height / 2 - 3);
			cout << "PLEASE ENTER YOUR NAME: ";
			gotoXY(Width / 2 - len - 2, Height / 2 - 1);
			gets_s(tmp);

			strncpy(player[9].name, tmp, 13);
			player[9].score = snake.n - 5;
			for (int i = 0; i < MAXPLAYER - 1; i++) {
				for (int j = i; j < MAXPLAYER - 1; j++) {
					if (player[j].score > player[i].score) {
						player[10] = player[j];
						player[j] = player[i];
						player[i] = player[10];
					}
				}
			}
			break;
		}
	}
}