#include "TileType.hpp"


TileType::TileType(ItemType a, ItemType b, ItemType c, ItemType d){

	type.insert( std::pair<MapDirection, ItemType>(up, a) );
	type.insert( std::pair<MapDirection, ItemType>(right, b) );
	type.insert( std::pair<MapDirection, ItemType>(down, c) );
	type.insert( std::pair<MapDirection, ItemType>(left, d) );
	shield = false;
}
	
TileType::~TileType(){}
	
bool TileType::operator==(const TileType& other) const{
	
	return true;
}

bool TileType::operator!=(const TileType& other) const{

	return false;
}

std::ostream& operator<<( std::ostream &out, const TileType& D ){
	
	std::map<MapDirection, ItemType> type = D.getType();
	
	out << "Tile type:\t" << "Up: " << type[up] << " Right: "<< type[right]<< " Down: " << type[down] << " Left: " << type[left];
	
	if(D.hasShield())	
		out << " with shield";
	
	out << std::endl;
	
	return out;
	
}
	
void TileType::operator=(const TileType& other){

	std::map<MapDirection, ItemType> otherm = other.getType(); 

	type[up]=otherm[up];
	type[right]=otherm[right];
	type[down]=otherm[down];
	type[left]=otherm[left];
	shield=other.hasShield();
}

bool TileType::isValid(void) const{
	return true;
}

bool TileType::hasShield(void) const{
	return shield;
}
	
const std::map<MapDirection, ItemType>& TileType::getType() const{

	return type;
}
