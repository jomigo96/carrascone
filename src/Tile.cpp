/*!
 * \file Tile.cpp
 * \brief Tile class implementation
 * \author João Gonçalves
 */

#include "Tile.hpp"

Tile::Tile() : TileType(){
	
	orientation=0;

}

Tile::Tile(char a) : TileType(a){

	orientation=0;
	
}

Tile::Tile(const TileType& tile){
	*this=Tile(tile.getTile());
}

Tile::~Tile(){}
	
int Tile::rotate_clockwise(void){
	
	const char c = this->getTile();
	
	if((c != 'b')&&( c != 'c' )&&( c != 'x'))
		orientation = (orientation==270) ? 0 : (orientation+90);
	return orientation;
}

int Tile::rotate_counter_clockwise(void){
	
	const char c = this->getTile();
	
	if((c != 'b')&&( c != 'c' )&&( c != 'x'))
		orientation = (orientation==0) ? 270 : (orientation-90);
	return orientation;	
}
int Tile::getOrientation(void) const{
	return orientation;
}

ItemType Tile::getUp()const{
	switch(orientation){

		case 0:
			return TileType::up;
		case 90:
			return TileType::left;
		case 180:
			return TileType::down;
		case 270:
			return TileType::right;
		default:
			throw std::logic_error("orientation must be 0 90 180 or 270");
		
	}
}

ItemType Tile::getRight()const{
	switch(orientation){

		case 0:
			return TileType::right;
		case 90:
			return TileType::up;
		case 180:
			return TileType::left;
		case 270:
			return TileType::down;
		default:
			throw std::logic_error("orientation must be 0 90 180 or 270");
		
	}	
}

ItemType Tile::getDown()const{
	switch(orientation){

		case 0:
			return TileType::down;
		case 90:
			return TileType::right;
		case 180:
			return TileType::up;
		case 270:
			return TileType::left;
		default:
			throw std::logic_error("orientation must be 0 90 180 or 270");
		
	}	
}

ItemType Tile::getLeft()const{
	switch(orientation){

		case 0:
			return TileType::left;
		case 90:
			return TileType::down;
		case 180:
			return TileType::right;
		case 270:
			return TileType::up;
		default:
			throw std::logic_error("orientation must be 0 90 180 or 270");
		
	}	
}



bool fits(const Tile& tile, const TileType& space){
	
	if( !tile.isValid())
		throw std::invalid_argument("That tile does not exist");
		
	if( space.getTile() == EMPTY_TILE )
		return false;
		
	ItemType true_up, true_right, true_down, true_left, up, right, down, left;
	
	true_up = tile.getUp();
	true_down = tile.getDown();
	true_left = tile.getLeft();
	true_right = tile.getRight();	
	up = space.getUp();
	down = space.getDown();
	left = space.getLeft();
	right = space.getRight();
	
	return (
		((up == none)    || (up == true_up))     &&
		((left == none)  || (left == true_left)) &&
		((down == none)  || (down == true_down)) &&
		((right == none) || (right == true_right))  
		);
}
