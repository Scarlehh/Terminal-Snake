#ifndef SNAKE_H
#define SNAKE_H

struct Coord {
	int x, y;
};

struct Snake {
	struct Coord* dir;
	int length;
};

struct Coord* new_coord();
void delete_coord(struct Coord* coord);

struct Snake* new_snake();
void delete_snake(struct Snake* snake);
void move_snake(struct Snake* snake, int dirx, int diry);
void update_snake_length(struct Snake* snake);

int get_snake_x(struct Snake* snake);
int get_snake_y(struct Snake* snake);
int get_snake_len(struct Snake* snake);

#endif
