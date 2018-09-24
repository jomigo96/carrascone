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

ItemType Tile::getSide(Direction d)const{

	switch(d){
		case Direction::up: return this->getUp();
		case Direction::right: return this->getRight();
		case Direction::down: return this->getDown();
		case Direction::left: return this->getLeft();
		default: return this->getLeft();
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


std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> Tile::getMapItems(Direction d)const{
	
	auto rotate_right = [](int a){ return (a==270) ? 0 : (a+90); };
	
	int angle = this->orientation;
	
	switch(d){
		case Direction::up:
			angle=rotate_right(angle);
		case Direction::right:	
			angle=rotate_right(angle);
		case Direction::down:
			angle=rotate_right(angle);
			break;
		case Direction::left:
			break;
	}
	
	std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> result;
	TypeIdentifier& first = std::get<0>(result);
	TypeIdentifier& second = std::get<1>(result);
	TypeIdentifier& third = std::get<2>(result);
	
	if(!this->isValid())
		throw std::logic_error("Must be called with a valid tile");
		
	std::runtime_error ex_runtime("Orientation and sides do not match");
	std::runtime_error ex_runtime2("Side and tiletype dont match");
	
	switch(this->getSide(d)){
		case castle:
			second=invalid;
			third=invalid;
			switch(this->tile){
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
					first=castle1;
					break;
				case 'h':
					switch(angle){
						case 0:
							first=castle2;
							break;
						case 180:
							first=castle1;
							break;
						default:
							throw ex_runtime;
							break;
					}
					break;
				case 'i':
					switch(angle){
						case 90:
							first=castle2;
							break;
						case 180:
							first=castle1;
							break;
						default:
							throw ex_runtime;
							break;
					}
					break;
				default:
					throw ex_runtime2;
					break;
			}
			break;
			
		case field:
			second=invalid;
			third=invalid;
			switch(this->tile){
				case 'a':
				case 'b':
				case 'd':
				case 'e':
				case 'h':
				case 'i':
				case 'j':
				case 'm':
				case 'n':
				case 'q':
				case 'r':
				case 'v':
				case 'w':
					first=field1;
					break;
				case 'k':
					first=field2;
					break;
				case 'u':
					if(angle == 0)
						first=field1;
					else if(angle == 180)
						first=field2;
					else
						throw ex_runtime;
					break;
				case 'f':
					if(angle == 90)
						first=field2;
					else if(angle == 270)
						first=field1;
					else
						throw ex_runtime;		
					break;
				case 'g':
					if(angle == 180)
						first=field1;
					else if(angle == 0)
						first=field2;
					else
						throw ex_runtime;								
					break;
				default:
					throw ex_runtime;
			}
			break;
		case road:
			switch(this->tile){
				case 'a':
					third=road1;
					second=field1;
					first=field1;
					break;
				case 'd':
					third=road1;
					if(angle == 90){
						first=field2;
						second=field1;
					}else if(angle == 270){
						first=field1;
						second=field2;						
					}else
						throw ex_runtime;
					break;
				case 'j':
					third=road1;
					if(angle == 90){
						first=field2;
						second=field1;
					}else if(angle == 180){
						first=field1;
						second=field2;
					}else
						throw ex_runtime;								
					break;
				case 'k':
					third=road1;
					if(angle == 0){
						first=field2;
						second=field1;
					}else if(angle == 270){
						first=field1;
						second=field2;
					}else
						throw ex_runtime;
					break;
				case 'l':
					switch(angle){
						case 0:
							third=road3;
							first=field3;
							second=field1;
							break;
						case 90:
							third=road2;
							first=field2;
							second=field3;
							break;
						case 270:
							third=road1;
							second=field2;
							first=field1;
							break;							
						default:
							throw ex_runtime;
					}
					break;
				case 'o':
				case 'p':
					third=road1;
					switch(angle){
						case 90:
							second=field1;
							first=field2;
							break;
						case 180:
							second=field2;
							first=field1;
							break;						
						default:
							throw ex_runtime;
					}
					break;
				case 's':
				case 't':
					third=road1;
					first=field1;
					second=field2;
					break;
				case 'u':
					third=road1;
					if(angle == 90){
						second=field1;
						first=field2;
					}else if(angle == 270){
						second=field2;
						first=field1;
					}else
						throw ex_runtime;
					break;
				case 'v':
					third=road1;
					if(angle == 0){
						second=field1;
						first=field2;
					}else if(angle == 90){
						second=field2;
						first=field1;
					}else
						throw ex_runtime;
					break;
				case 'w':
					switch(angle){
						case 0:
							third=road3;
							first=field3;
							second=field1;
							break;
						case 90:
							third=road2;
							first=field2;
							second=field3;
							break;
						case 180:
							third=road1;
							first=field1;
							second=field2;
							break;
						default:
							throw ex_runtime;
					}
					break;
				case 'x':
					switch(angle){
						case 0:
							third=road4;
							first=field4;
							second=field1;
							break;
						case 90:
							third=road3;
							first=field3;
							second=field4;
							break;
						case 180:
							third=road2;
							first=field2;
							second=field3;
							break;
						case 270:
							third=road1;
							first=field1;
							second=field2;
							break;
						default:
							throw ex_runtime2;
					}
					break;
				default:
					throw ex_runtime;
			}
			break;
		default: break;
	}
	return result;
}

