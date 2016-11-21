#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include "snake.h"
#include "powerup.h"

const int DELAY = 100;
const int B_COL = 29;
const int B_ROW = 29;
const char FRUIT_ICON = '@';

void init();
void end();
WINDOW *create_board(int height, int width, int starty, int startx);
void destroy_board(WINDOW* local_win);

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	init();
	refresh();	
	
	WINDOW* board = create_board(B_ROW, B_COL, 0, 0);
	wattron(board, COLOR_PAIR(1));
	timeout(DELAY);

	struct Snake* p1 = new_snake(board, 1, 1);
	struct Powerup* fruit = new_powerup(board,
										1 + (rand() % (B_COL-2)),
										1 + (rand() % (B_ROW-2)),
										FRUIT_ICON);
	int ch = '\0';
	int lost = 0;
	do {
		switch(ch) {
		case KEY_DOWN:
			update_snake_dir(p1, 0, 1);
			break;
		case KEY_UP:
			update_snake_dir(p1, 0, -1);
			break;
		case KEY_RIGHT:
			update_snake_dir(p1, 1, 0);
			break;
		case KEY_LEFT:
			update_snake_dir(p1, -1, 0);
			break;
		}
		// Get tile in next position
		char hit = look_ahead_snake(p1);
		// Stop snake if nowhere to go
		if(hit != ' ') {
			if(hit == FRUIT_ICON) {
				grow_snake(p1);
				relocate_powerup(fruit,
								 1 + (rand() % (B_COL-2)),
								 1 + (rand() % (B_ROW-2)));
			} else {
				if(get_snake_dir_x(p1) != 0 ||
				   get_snake_dir_y(p1) != 0) {
					lost = 1;
					update_snake_dir(p1, 0, 0);
				}
			}
		}
		move_snake(p1);

		// Tidy Board
		move(0, 0);
		wrefresh(board);
	} while((ch = getch()) != 'q' && !lost);

	delete_powerup(fruit);
	delete_snake(p1);
	destroy_board(board);
	end();

	return 0;
}

void init() {
	initscr();
	cbreak(); // Pass characters with generating signals
	noecho(); // Don't echo characters
	keypad(stdscr, TRUE); // Enable keypad function/arrow keys
	start_color();
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void end() {
	endwin();
}

WINDOW *create_board(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);

	return local_win;
}


void destroy_board(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
