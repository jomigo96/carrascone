#ifndef TILE_HPP
#define TILE_HPP

#include "TileType.hpp"


class Tile : public TileType{
	
public:
	Tile();
	Tile(char a);
	~Tile();
	
	int rotate_clockwise(void);
	int rotate_counter_clockwise(void);
	int get_orientation(void) const;
	
private:
	int orientation;
};


#endif /* TILE_HPP */
