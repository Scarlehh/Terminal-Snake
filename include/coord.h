#ifndef COORD_H
#define COORD_H

struct Coord {
	int x, y;
};

// Coord
struct Coord* new_coord();
void delete_coord(struct Coord* coord);
void set_coord(struct Coord* coord, int x, int y);
int get_x(struct Coord* coord);
int get_y(struct Coord* coord);


#endif
