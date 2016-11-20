#include "snake.h"
#include <stdlib.h>

struct Snake* new_snake() {
	struct Snake* snake = malloc(sizeof(struct Snake));
	snake->length = 1;
	snake->x = 0;
	snake->y = 0;
	return snake;
}

void delete_snake(struct Snake* snake) {
	free(snake);
}

void move_snake(struct Snake* snake, int dirx, int diry) {
	snake->x = dirx;
	snake->y = diry;
}

int get_x(struct Snake* snake) {
	return snake->x;
}

int get_y(struct Snake* snake) {
	return snake->y;
}
