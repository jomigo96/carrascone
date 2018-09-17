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

bool Tile::operator[](const TileType& other) const{

	if(other.getTile() != INCOMPLETE_TILE){
		throw std::logic_error("Bad function call, must be incomplete tile");
	}
	
	ItemType true_up, true_right, true_down, true_left;
	
	switch(orientation){
	
		case 0: 
			true_up = TileType::up;
			true_right = TileType::right;
			true_down = TileType::down;
			true_left = TileType::left;
			break;
		case 90:
			true_up = TileType::left;
			true_right = TileType::up;
			true_down = TileType::right;
			true_left = TileType::down;
			break;
		case 180:
			true_up = TileType::down;
			true_right = TileType::left;
			true_down = TileType::up;
			true_left = TileType::right;
			break;
		case 270:
			true_up = TileType::right;
			true_right = TileType::down;
			true_down = TileType::left;
			true_left = TileType::up;
			break;
		default:
			true_up = none;
			true_right = none;
			true_down = none;
			true_left = none;
	}

	bool flag = true;
	
	flag &= (other.getUp()==none || other.getUp()==true_up);
	flag &= (other.getRight()==none || other.getRight()==true_right);
	flag &= (other.getDown()==none || other.getDown()==true_down);
	flag &= (other.getLeft()==none || other.getLeft()==true_left);
	return flag;
}
