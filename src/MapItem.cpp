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
		it->first.reset();
	}
	
	for(auto it=owners.begin(); it!=owners.end(); it++){
		it->reset();
	}
	
}

MapItem::MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key){
	
	span.push_back(
		std::pair<std::shared_ptr<Tile>, TypeIdentifier>(tile, key));
	
}

std::ostream& operator<<(std::ostream& os, const MapItem& item){
	item.myprint(os, item);
	return os;
}

std::ostream& MapItem::myprint(std::ostream& os, const MapItem& item)const{
	
	os << &item << std::endl;
	return os;
}

std::vector<std::pair<std::shared_ptr<Tile>, TypeIdentifier>> const& MapItem::getSpan(void)const{
	return span;
}

std::vector<std::shared_ptr<Player>> const& MapItem::getOwners()const{
	return owners;
}

void MapItem::mergeWith(std::shared_ptr<MapItem> other){
	
	if(this == other.get())
		return;
	
	auto owners = other->getOwners();
	auto span = other->getSpan();
	
	this->span.reserve(span.size());
	
	for(auto it = span.cbegin(); it!=span.cend(); it++){
		this->span.push_back(*it);
	}
	for(auto it = owners.cbegin(); it!=owners.cend(); it++){
		this->owners.push_back(*it);
	}
}

TypeIdentifier MapItem::getFirst()const{
	
	if(this->span.size()>0)
		return this->span.begin()->second;
	throw std::length_error("Empty mapitem");
	
}

bool MapItem::hasItem(std::shared_ptr<const Tile> tileptr, TypeIdentifier type)const{
	
	for(auto it=this->span.cbegin(); it!=this->span.cend(); it++){
		if((it->first == tileptr)&&(it->second == type))
			return true;
	}
	return false;
	
}

