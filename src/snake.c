#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

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

// Linked List
struct Node* new_ll(WINDOW* board, int x, int y) {
	struct Node* ll = malloc(sizeof(struct Node));
	ll->pos = new_coord(x, y);
	ll->next = NULL;
	
	mvwaddch(board, y, x, 'O');
	return ll;
}

void delete_ll(struct Node* ll) {
	if(ll->next != NULL) {
		delete_ll(ll->next);
	}
	free(ll->pos);
	free(ll);
}

void add_node(WINDOW* board, struct Node* ll, int x, int y) {
	int tx = ll->pos->x;
	int ty = ll->pos->y;
	set_coord(ll->pos, x, y);

	mvwaddch(board, ty, tx, ' ');
	mvwaddch(board, y, x, 'O');

	if(ll->next == NULL) {
		ll->next = new_ll(board, tx, ty);
	} else {
		add_node(board, ll->next, tx, ty);
	}
}

void update_head(WINDOW* board, struct Node* ll, int x, int y) {
	int tx = ll->pos->x;
	int ty = ll->pos->y;
	set_coord(ll->pos, x, y);

	mvwaddch(board, ty, tx, ' ');
	mvwaddch(board, y, x, 'O');
	
	if(ll->next != NULL) {
		update_head(board, ll->next, tx, ty);
	}
}

// Snake
struct Snake* new_snake(WINDOW* board, int x, int y) {
	struct Snake* snake = malloc(sizeof(struct Snake));
	snake->dir = new_coord(0, 0);
	snake->ll = new_ll(board, x, y);
	return snake;
}

void delete_snake(struct Snake* snake) {
	delete_coord(snake->dir);
	delete_ll(snake->ll);
	free(snake);
}

void update_snake_dir(struct Snake* snake, int dirx, int diry) {
	set_coord(snake->dir, dirx, diry);
}

void move_snake(WINDOW* board, struct Snake* snake) {
	if(snake->dir->x != 0 || snake->dir->y != 0) {
		update_head(board,
					snake->ll,
					get_snake_next_x(snake),
					get_snake_next_y(snake));
	}
}

void grow_snake(WINDOW* board, struct Snake* snake) {
	add_node(board, snake->ll,
			 get_snake_next_x(snake),
			 get_snake_next_y(snake));
}

int get_snake_next_x(struct Snake* snake) {
	return get_x(snake->ll->pos) + get_x(snake->dir);
}

int get_snake_next_y(struct Snake* snake) {
	return get_y(snake->ll->pos) + get_y(snake->dir);
}
