#ifndef TILE_HPP
#define TILE_HPP

#include "TileType.hpp"


class Tile : public TileType{
	
public:
	Tile();
	Tile(char a);
	~Tile();
	
	bool operator[](const TileType& other) const;
	
	int rotate_clockwise(void);
	int rotate_counter_clockwise(void);
	int get_orientation(void) const;
	
	ItemType getUp()const;
	ItemType getRight()const;
	ItemType getDown()const;
	ItemType getLeft()const;
	
private:
	int orientation;
};


#endif /* TILE_HPP */
