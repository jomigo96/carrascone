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


std::stack<TypeIdentifier>* Tile::getLeftMapItems()const{
	auto stack = new std::stack<TypeIdentifier>;
	
	if(!this->isValid())
		throw std::logic_error("Must be called with a valid tile");
	
	switch(this->getLeft()){
		case castle:
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
					stack->push(castle1);
					break;
				case 'h':
					switch(this->orientation){
						case 0:
							stack->push(castle2);
							break;
						case 180:
							stack->push(castle1);
							break;
						default:
							throw std::runtime_error("Orientation and sides do not match");
							break;
					}
				case 'i':
					switch(this->orientation){
						case 90:
							stack->push(castle2);
							break;
						case 180:
							stack->push(castle1);
							break;
						default:
							throw std::runtime_error("Orientation and sides do not match");
							break;
					}
					break;
				default:
					throw std::runtime_error("Side and tiletype dont match");
					break;
			}
			break;
			
		case field:
			switch(this->tile){
				case 'a':
				case 'b':
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
					stack->push(field1);
					break;
				case 'd':
				case 'k':
					stack->push(field2);
					break;
				case 'u':
					if(this->orientation == 0)
						stack->push(field2);
					else if(this->orientation == 180)
						stack->push(field1);
					else
						throw std::runtime_error("Orientation and sides do not match");
					break;
				case 'f':
					if(this->orientation == 90)
						stack->push(field1);
					else if(this->orientation == 270)
						stack->push(field2);
					else
						throw std::runtime_error("Orientation and sides do not match");					
					break;
				case 'g':
					if(this->orientation == 180)
						stack->push(field1);
					else if(this->orientation == 0)
						stack->push(field2);
					else
						throw std::runtime_error("Orientation and sides do not match");									
					break;
				default:
					throw std::runtime_error("Side and tiletype dont match");
			}
			break;
		case road:
			switch(this->tile){
				case 'a':
					stack->push(road1);
					stack->push(field1);
					break;
				case 'd':
					stack->push(road1);
					if(this->orientation == 90){
						stack->push(field2);
						stack->push(field1);
					}else if(this->orientation == 270){
						stack->push(field1);
						stack->push(field2);						
					}else
						throw std::runtime_error("Orientation and sides do not match");
					break;
				case 'j':
					stack->push(road1);
					if(this->orientation == 90){
						stack->push(field1);
						stack->push(field2);
					}else if(this->orientation == 180){
						stack->push(field2);
						stack->push(field1);
					}else
						throw std::runtime_error("Orientation and sides do not match");									
					break;
				case 'k':
					stack->push(road1);
					if(this->orientation == 0){
						stack->push(field2);
						stack->push(field1);
					}else if(this->orientation == 270){
						stack->push(field1);
						stack->push(field2);
					}else
						throw std::runtime_error("Orientation and sides do not match");
					break;
				case 'l':
					switch(this->orientation){
						case 0:
							stack->push(road3);
							stack->push(field1);
							stack->push(field3);
							break;
						case 90:
							stack->push(road2);
							stack->push(field3);
							stack->push(field2);
							break;
						case 270:
							stack->push(road1);
							stack->push(field2);
							stack->push(field1);
							break;							
						default:
							throw std::runtime_error("Orientation and sides do not match");
					}
					break;
				case 'o':
				case 'p':
					switch(this->orientation){
						case 90:
							stack->push(road1);
							stack->push(field1);
							stack->push(field2);
							break;
						case 180:
							stack->push(road1);
							stack->push(field2);
							stack->push(field1);	
							break;						
						default:
							throw std::runtime_error("Orientation and sides do not match");
					}
					break;
				case 's':
				case 't':
					stack->push(road1);
					stack->push(field2);
					stack->push(field1);
					break;
				case 'u':
					stack->push(road1);
					if(this->orientation == 90){
						stack->push(field1);
						stack->push(field2);
					}else if(this->orientation == 270){
						stack->push(field2);
						stack->push(field1);
					}else
						throw std::runtime_error("Orientation and sides do not match");
					break;
				case 'v':
					stack->push(road1);
					if(this->orientation == 0){
						stack->push(field1);
						stack->push(field2);
					}else if(this->orientation == 90){
					}else
						throw std::runtime_error("Orientation and sides do not match");
					break;
				case 'w':
					switch(this->orientation){
						case 0:
							stack->push(road3);
							stack->push(field1);
							stack->push(field3);
							break;
						case 90:
							stack->push(road2);
							stack->push(field3);
							stack->push(field2);
							break;
						case 180:
							stack->push(road1);
							stack->push(field2);
							stack->push(field1);
							break;
						default:
							throw std::runtime_error("Orientation and sides do not match");
					}
					break;
				case 'x':
					switch(this->orientation){
						case 0:
							stack->push(road4);
							stack->push(field1);
							stack->push(field4);
							break;
						case 90:
							stack->push(road3);
							stack->push(field4);
							stack->push(field3);
							break;
						case 180:
							stack->push(road2);
							stack->push(field3);
							stack->push(field2);
							break;
						case 270:
							stack->push(road1);
							stack->push(field2);
							stack->push(field1);
							break;
						default:
							throw std::runtime_error("Bad orientation");
					}
					break;
				default:
					throw std::runtime_error("Side and tiletype dont match");
			}
			break;
		default: break;
	}
	return stack;
}
std::stack<TypeIdentifier>* Tile::getRightMapItems()const{
	return new std::stack<TypeIdentifier>;
}
std::stack<TypeIdentifier>* Tile::getUpMapItems()const{
	return new std::stack<TypeIdentifier>;
}
std::stack<TypeIdentifier>* Tile::getDownMapItems()const{
	return new std::stack<TypeIdentifier>;
}
