#include "snake.h"
#include <stdlib.h>

struct Coord* new_coord(int x, int y) {
	struct Coord* coord = malloc(sizeof(struct Coord));
	coord->x = x;
	coord->y = y;
	return coord;
}

void delete_coord(struct Coord* coord) {
	free(coord);
}

struct Snake* new_snake() {
	struct Snake* snake = malloc(sizeof(struct Snake));
	snake->length = 1;
	snake->dir = new_coord(0, 0);
	return snake;
}

void delete_snake(struct Snake* snake) {
	delete_coord(snake->dir);
	free(snake);
}

void move_snake(struct Snake* snake, int dirx, int diry) {
	snake->dir->x = dirx;
	snake->dir->y = diry;
}

void update_snake_length(struct Snake* snake) {
	snake->length++;
}

int get_snake_x(struct Snake* snake) {
	return snake->dir->x;
}

int get_snake_y(struct Snake* snake) {
	return snake->dir->y;
}

int get_snake_len(struct Snake* snake) {
	return snake->length;
}
