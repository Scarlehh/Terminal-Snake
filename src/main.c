#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

const int DELAY = 100;
const char WALL = '#';
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
	
	int r=1, c=1;
	int ch = '\0', pch = '\0';
	do {
		if(ch == ERR) {
			ch = pch;
		} else {
			pch = ch;
		}
		mvwaddch(board, r, c, ' ');

		switch(ch) {
		case KEY_DOWN:
			if(r+2 < B_ROW) {
				r++;
			}
			break;
		case KEY_UP:
			if(r-1 > 0) {
				r--;
			}
			break;
		case KEY_RIGHT:
			if(c+2 < B_COL) {
				c++;
			}
			break;
		case KEY_LEFT:
			if(c-1 > 0) {
				c--;
			}
			break;
		}
		
		mvwaddch(board, r, c, 'O');
		wmove(board, 0, 0);
		wrefresh(board);
	} while((ch = getch()) != 'q');
	
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
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}


void destroy_board(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
