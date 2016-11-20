#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

struct Coord {
	int x, y;
};

struct Node {
	struct Node* next;
	struct Coord* pos;
};

struct Snake {
	struct Coord* dir;
	struct Node* ll;
};

// Coord
struct Coord* new_coord();
void delete_coord(struct Coord* coord);
void set_coord(struct Coord* coord, int x, int y);
int get_x(struct Coord* coord);
int get_y(struct Coord* coord);

// Linked List
struct Node* new_ll(WINDOW* board, int x, int y);
void delete_ll(struct Node* ll);
void add_node(WINDOW* board, struct Node* ll, int x, int y);
void update_head(WINDOW* board, struct Node* ll, int x, int y);

// Snake
struct Snake* new_snake(WINDOW* board, int x, int y);
void delete_snake(struct Snake* snake);
void update_snake_dir(struct Snake* snake, int dirx, int diry);
void move_snake(WINDOW* board, struct Snake* snake);
void update_snake_length(struct Snake* snake);
void grow_snake(WINDOW* board, struct Snake* snake);

// Getters
int get_snake_next_x(struct Snake* snake);
int get_snake_next_y(struct Snake* snake);

#endif
