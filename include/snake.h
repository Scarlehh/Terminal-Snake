#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

struct Scale {
	struct Scale* next;
	struct Coord* pos;
};

struct Snake {
	struct Coord* dir;
	struct Scale* scales;
	WINDOW* board;
};

// Linked List
struct Scale* new_scale(WINDOW* board, int x, int y);
void delete_scale(struct Scale* scale);
void add_scale(WINDOW* board, struct Scale* scale, int x, int y);
void update_head(WINDOW* board, struct Scale* scale, int x, int y);

// Snake
struct Snake* new_snake(WINDOW* board, int x, int y);
void delete_snake(struct Snake* snake);
void update_snake_dir(struct Snake* snake, int dirx, int diry);
void move_snake(struct Snake* snake);
void update_snake_length(struct Snake* snake);
void grow_snake(struct Snake* snake);
char look_ahead_snake(struct Snake* snake);

// Getters
int get_snake_next_x(struct Snake* snake);
int get_snake_next_y(struct Snake* snake);

#endif
