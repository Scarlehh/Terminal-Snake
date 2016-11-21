#include "coord.h"
#include <stdlib.h>

// Coord
struct Coord* new_coord(int x, int y) {
	struct Coord* coord = malloc(sizeof(struct Coord));
	coord->x = x;
	coord->y = y;
	return coord;
}

void delete_coord(struct Coord* coord) {
	free(coord);
}

void set_coord(struct Coord* coord, int x, int y) {
	coord->x = x;
	coord->y = y;
}

int get_x(struct Coord* coord) {
	return coord->x;
}

int get_y(struct Coord* coord) {
	return coord->y;
}
