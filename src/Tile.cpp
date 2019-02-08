/*!
 * \file Tile.cpp
 * \brief Tile class implementation
 * \author João Gonçalves
 */

#include "Tile.hpp"
#include "Cell.hpp"

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
			// fall through
		case Direction::right:
			angle=rotate_right(angle);
			// fall through
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

sf::Vector2f Tile::getItemPosition(TypeIdentifier t)const{
	sf::Vector2f offset;

	switch(t){
		case field1:
			switch (TileType::tile) {
				case 'a':
				case 'b':
				case 'd':
				case 'i':
				case 'k':
				case 'l':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
					offset.x=CELL_DIM*0.2;
					offset.y=CELL_DIM*0.2;
					break;
				case 'e':
				case 'h':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.5;
					break;
				case 'f':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.08;
					break;
				case 'g':
					offset.x=CELL_DIM*0.95;
					offset.y=CELL_DIM*0.5;
					break;
				case 'j':
					offset.x=CELL_DIM*0.15;
					offset.y=CELL_DIM*0.5;
					break;
				case 'q':
				case 'r':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.9;
					break;
				case 's':
				case 't':
					offset.x=CELL_DIM*0.85;
					offset.y=CELL_DIM*0.95;
					break;
				default: break;
			}
			break;
		case field2:
			switch (TileType::tile) {
				case 'd':
				case 'l':
					offset.x=CELL_DIM*0.7;
					offset.y=CELL_DIM*0.1;
					break;
				case 'f':
				case 'k':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.92;
					break;
				case 'g':
					offset.x=CELL_DIM*0.08;
					offset.y=CELL_DIM*0.5;
					break;
				case 'j':
				case 'o':
				case 'p':
				case 'w':
				case 'u':
					offset.x=CELL_DIM*0.8;
					offset.y=CELL_DIM*0.8;
					break;
				case 'x':
					offset.x=CELL_DIM*0.8;
					offset.y=CELL_DIM*0.2;
					break;
				case 's':
				case 't':
					offset.x=CELL_DIM*0.15;
					offset.y=CELL_DIM*0.95;
					break;
				case 'v':
					offset.x=CELL_DIM*0.2;
					offset.y=CELL_DIM*0.8;
					break;
				default: break;
			}
			break;
		case field3:
			switch (TileType::tile) {
				case 'l':
				case 'w':
					offset.x=CELL_DIM*0.15;
					offset.y=CELL_DIM*0.85;
					break;
				case 'x':
					offset.x=CELL_DIM*0.75;
					offset.y=CELL_DIM*0.75;
					break;
				default: break;
			}
			break;
		case field4:
			if(TileType::tile == 'x'){
				offset.x=CELL_DIM*0.25;
				offset.y=CELL_DIM*0.75;
			}
			break;
		case road1:
		 	switch (TileType::tile) {
		 		case 'a':
					offset.x=CELL_DIM*0.45;
					offset.y=CELL_DIM*0.85;
					break;
				case 's':
				case 't':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.75;
					break;
				case 'd':
				case 'u':
				case 'v':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.5;
					break;
				case 'x':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.25;
					break;
				case 'l':
					offset.x=CELL_DIM*0.45;
					offset.y=CELL_DIM*0.2;
					break;
				case 'j':
					offset.x=CELL_DIM*0.55;
					offset.y=CELL_DIM*0.55;
					break;
				case 'o':
				case 'p':
					offset.x=CELL_DIM*0.9;
					offset.y=CELL_DIM*0.5;
					break;
				case 'k':
					offset.x=CELL_DIM*0.37;
					offset.y=CELL_DIM*0.37;
					break;
				case 'w':
					offset.x=CELL_DIM*0.85;
					offset.y=CELL_DIM*0.5;
					break;
				default: break;
		 	}
			break;
		case road2:
		 	switch (TileType::tile) {
		 		case 'l':
					offset.x=CELL_DIM*0.4;
					offset.y=CELL_DIM*0.8;
					break;
				case 'w':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.75;
					break;
				case 'x':
					offset.x=CELL_DIM*0.75;
					offset.y=CELL_DIM*0.5;
					break;
				default: break;
		 	}
			break;
		case road3:
			switch (TileType::tile) {
				case 'l':
				case 'w':
					offset.x=CELL_DIM*0.15;
					offset.y=CELL_DIM*0.45;
					break;
				case 'x':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.75;
					break;
				default: break;
			}
			break;
		case road4:
			if(TileType::tile == 'x'){
				offset.x=CELL_DIM*0.25;
				offset.y=CELL_DIM*0.5;
			}
			break;
		case castle1:
			switch (TileType::tile) {
				case 'c':
				case 'f':
				case 'g':
				case 'q':
				case 'r':
				case 's':
				case 't':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.5;
					break;
				case 'e':
				case 'j':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.1;
					break;
				case 'm':
				case 'n':
				case 'o':
				case 'p':
					offset.x=CELL_DIM*0.3;
					offset.y=CELL_DIM*0.3;
					break;
				case 'h':
				case 'i':
				case 'k':
				case 'l':
				case 'd':
					offset.x=CELL_DIM*0.9;
					offset.y=CELL_DIM*0.5;
					break;
				default: break;
			}
			break;
		case castle2:
			switch (TileType::tile) {
				case 'h':
					offset.x=CELL_DIM*0.1;
					offset.y=CELL_DIM*0.5;
					break;
				case 'i':
					offset.x=CELL_DIM*0.5;
					offset.y=CELL_DIM*0.9;
					break;
				default: break;
			}
			break;
		case cloister:
			offset.x=CELL_DIM*0.5;
			offset.y=CELL_DIM*0.5;
			break;
		default: break;

	}

	int aux;
	switch(orientation){
		case 90:
			aux = offset.x;
			offset.x = CELL_DIM-offset.y;
			offset.y = aux;
			break;
		case 180:
			offset.x = CELL_DIM-offset.x;
			offset.y = CELL_DIM-offset.y;
			break;
		case 270:
			aux = offset.y;
			offset.y = CELL_DIM - offset.x;
			offset.x = aux;
			break;
		default: break;
	}

	return offset;
}
