#include "Tile.hpp"

Tile::Tile() : TileType(){
	
	orientation=0;

}

Tile::Tile(char a) : TileType(a){

	orientation=0;
	
}

Tile::~Tile(){}
	
int Tile::rotate_clockwise(void){
	orientation = (orientation==270) ? 0 : (orientation+90);
	return orientation;
}

int Tile::rotate_counter_clockwise(void){
	orientation = (orientation==0) ? 270 : (orientation-90);
	return orientation;	
}
int Tile::get_orientation(void) const{
	return orientation;
}
