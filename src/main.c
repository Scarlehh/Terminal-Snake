#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "snake.h"

const int DELAY = 100;
const int B_COL = 29;
const int B_ROW = 29;

void init();
void end();
WINDOW *create_board(int height, int width, int starty, int startx);
void destroy_board(WINDOW* local_win);

int main() {
	init();
	refresh();	
	
	WINDOW* board = create_board(B_ROW, B_COL, 0, 0);
	wattron(board, COLOR_PAIR(1));
	timeout(DELAY);

	struct Snake* p1 = new_snake(board, 1, 1);
	int ch = '\0';
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
		case 'a':
			grow_snake(board, p1);
			break;
		}
		// Get tile in next position
		char hit = mvwinch(board,
						   get_snake_next_y(p1),
						   get_snake_next_x(p1));
		// Stop snake if nowhere to go
		if(hit != ' ') {
			update_snake_dir(p1, 0, 0);
		}
		move_snake(board, p1);

		// Tidy Board
		move(0, 0);
		wrefresh(board);
	} while((ch = getch()) != 'q');
	
	destroy_board(board);
	end();
	delete_snake(p1);
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
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}


void destroy_board(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
