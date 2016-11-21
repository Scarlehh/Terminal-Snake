#include "powerup.h"
#include "coord.h"
#include <stdlib.h>

struct Powerup* new_powerup(WINDOW* board, int x, int y, char icon) {
	struct Powerup* powerup = malloc(sizeof(struct Powerup));
	powerup->pos = new_coord(x, y);
	powerup->board = board;
	powerup->icon = icon;
	
	mvwaddch(board, y, x, icon);
	return powerup;
}

void delete_powerup(struct Powerup* powerup) {
	mvwaddch(powerup->board, get_y(powerup->pos), get_x(powerup->pos), ' ');
	delete_coord(powerup->pos);
	free(powerup);
}

void relocate_powerup(struct Powerup* powerup, int x, int y) {
	set_coord(powerup->pos, x, y);
	mvwaddch(powerup->board, y, x, powerup->icon);
}
