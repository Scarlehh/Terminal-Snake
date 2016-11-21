#include "snake.h"
#include "coord.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

const wchar_t SEG = L'\u2588';

// Linked List
struct Scale* new_scale(WINDOW* board, int x, int y) {
	struct Scale* scale = malloc(sizeof(struct Scale));
	scale->pos = new_coord(x, y);
	scale->next = NULL;
	
	//mvwaddch(board, y, x, SEG);
	mvwprintw(board, y, x, "%lc", SEG);
	return scale;
}

void delete_scale(struct Scale* scale) {
	if(scale->next != NULL) {
		delete_scale(scale->next);
	}
	free(scale->pos);
	free(scale);
}

void add_scale(WINDOW* board, struct Scale* scale, int x, int y) {
	int tx = get_x(scale->pos);
	int ty = get_y(scale->pos);
	set_coord(scale->pos, x, y);

	mvwaddch(board, ty, tx, ' ');
	//mvwaddch(board, y, x, SEG);
	mvwprintw(board, y, x, "%lc", SEG);

	if(scale->next == NULL) {
		scale->next = new_scale(board, tx, ty);
	} else {
		add_scale(board, scale->next, tx, ty);
	}
}

void update_head(WINDOW* board, struct Scale* scale, int x, int y) {
	int tx = get_x(scale->pos);
	int ty = get_y(scale->pos);
	set_coord(scale->pos, x, y);

	mvwaddch(board, ty, tx, ' ');
	//mvwaddch(board, y, x, SEG);
	mvwprintw(board, y, x, "%lc", SEG);
	
	if(scale->next != NULL) {
		update_head(board, scale->next, tx, ty);
	}
}

// Snake
struct Snake* new_snake(WINDOW* board, int x, int y) {
	struct Snake* snake = malloc(sizeof(struct Snake));
	snake->dir = new_coord(0, 0);
	snake->scales = new_scale(board, x, y);
	snake->board = board;
	return snake;
}

void delete_snake(struct Snake* snake) {
	delete_coord(snake->dir);
	delete_scale(snake->scales);
	free(snake);
}

void update_snake_dir(struct Snake* snake, int dirx, int diry) {
	set_coord(snake->dir, dirx, diry);
}

void move_snake(struct Snake* snake) {
	if(get_x(snake->dir) != 0 || get_y(snake->dir) != 0) {
		update_head(snake->board,
					snake->scales,
					get_snake_next_x(snake),
					get_snake_next_y(snake));
	}
}

void grow_snake(struct Snake* snake) {
	add_scale(snake->board,
			 snake->scales,
			 get_snake_next_x(snake),
			 get_snake_next_y(snake));
}

char look_ahead_snake(struct Snake* snake) {
	return mvwinch(snake->board,
				   get_snake_next_y(snake),
				   get_snake_next_x(snake));
}

int get_snake_next_x(struct Snake* snake) {
	return get_x(snake->scales->pos) + get_x(snake->dir);
}

int get_snake_next_y(struct Snake* snake) {
	return get_y(snake->scales->pos) + get_y(snake->dir);
}

int get_snake_dir_x(struct Snake* snake) {
	return get_x(snake->dir);
}

int get_snake_dir_y(struct Snake* snake) {
	return get_y(snake->dir);
}
