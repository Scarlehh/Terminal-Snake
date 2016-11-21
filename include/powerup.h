#ifndef POWERUP_H
#define POWERUP_H

#include <ncurses.h>

struct Powerup {
	struct Coord* pos;
	WINDOW* board;
	char icon;
};

struct Powerup* new_powerup(WINDOW* board, int x, int y, char icon);
void delete_powerup(struct Powerup* powerup);
void relocate_powerup(struct Powerup* powerup, int x, int y);

#endif
