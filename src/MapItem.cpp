/*!
 * \file MapItem.cpp
 * \brief MapItem class implementation
 * \author João Gonçalves
 */

#include "MapItem.hpp"
#include <exception>


MapItem::MapItem(){

	occupant=false;
	closed=false;
}

MapItem::~MapItem(){

	for(auto it=span.begin(); it!=span.end(); it++){
		std::get<0>(*it).reset();
		std::get<2>(*it).reset();
	}

}

MapItem::MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key){

	span.push_back(
		std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>(tile, key, nullptr));

	occupant=false;
	closed=false;
}

std::ostream& operator<<(std::ostream& os, const MapItem& item){
	item.myprint(os, item);
	return os;
}

std::ostream& MapItem::myprint(std::ostream& os, const MapItem& item)const{

	os << &item << std::endl;
	return os;
}

std::vector<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>> const& MapItem::getSpan(void)const{
	return span;
}


void MapItem::mergeWith(std::shared_ptr<MapItem> other){

	if(this == other.get())
		return;

	auto span = other->getSpan();

	this->span.reserve(span.size());

	for(auto it = span.cbegin(); it!=span.cend(); it++){
		this->span.push_back(*it);
	}

	this->occupant |= other->occupant;
}

TypeIdentifier MapItem::getFirst()const{

	if(this->span.size()>0)
		return std::get<1>(*this->span.begin());
	throw std::length_error("Empty mapitem");

}

bool MapItem::hasItem(std::shared_ptr<const Tile> tileptr, TypeIdentifier type)const{

	for(auto it=this->span.cbegin(); it!=this->span.cend(); it++){
		if((std::get<0>(*it) == tileptr)&&(std::get<1>(*it) == type))
			return true;
	}
	return false;

}

bool MapItem::hasTile(std::shared_ptr<Tile> tileptr)const{

	for(auto it=this->span.cbegin(); it!=this->span.cend(); it++){
		if((std::get<0>(*it) == tileptr))
			return true;
	}
	return false;

}


bool MapItem::hasOccupant()const{

	return occupant;
}


void MapItem::freeRealEstate(std::shared_ptr<Tile> tile, std::list<TypeIdentifier>& target)const{

	if(occupant)
		return;

	for(auto it=span.cbegin(); it!=span.cend(); it++){
		if(std::get<0>(*it) == tile){
			target.push_back(std::get<1>(*it));
		}
	}

}

bool MapItem::isClosed()const{

	return closed;
}

bool MapItem::claim(std::shared_ptr<const Tile> tile, TypeIdentifier type, std::shared_ptr<Player> player){

	if(occupant)
		return false;

	if(player == nullptr)
		throw std::invalid_argument("called with nullptr");

	for(auto it=span.begin(); it!= span.end(); it++){

		if((std::get<0>(*it) == tile)&&(std::get<1>(*it) == type)){
			std::get<2>(*it) = player;
			occupant = true;
			return true;
		}
	}

	return false;

}

void MapItem::getOccupiedPosition(std::list<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>>& list){

	for(auto it = span.cbegin(); it != span.cend(); it++){
		if(std::get<2>(*it) != nullptr){
			list.push_back(*it);
		}
	}
}

std::string print_TypeIdentifier(TypeIdentifier t){


	switch(t){
		case road1:
			return std::string("road1");

		case road2:
			return std::string("road2");
		case road3:
			return std::string("road3");
		case road4:
			return std::string("road4");

		//Castles
		case castle1:
			return std::string("castle1");
		case castle2:
			return std::string("castle2");

		//Fields
		case field1:
			return std::string("field1");
		case field2:
			return std::string("field2");
		case field3:
			return std::string("field3");
		case field4:
			return std::string("field4");

		case cloister:
			return std::string("cloister");

		//none
		default:
			return std::string("invalid");
	}
	return std::string("invalid");
}
