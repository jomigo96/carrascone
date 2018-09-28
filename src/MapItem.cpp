/*!
 * \file MapItem.cpp
 * \brief MapItem class implementation
 * \author João Gonçalves
 */

#include "MapItem.hpp"
#include <exception>


MapItem::MapItem(){}
MapItem::~MapItem(){

	for(auto it=span.begin(); it!=span.end(); it++){
		std::get<0>(*it).reset();
		std::get<2>(*it).reset();
	}
	
}

MapItem::MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key){
	
	span.push_back(
		std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>(tile, key, nullptr));
	
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

