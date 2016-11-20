#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
	int x, y;
	int length;
};

struct Snake* new_snake();
void delete_snake(struct Snake* snake);
void move_snake(struct Snake* snake, int dirx, int diry);

int get_x(struct Snake* snake);
int get_y(struct Snake* snake);

#endif
