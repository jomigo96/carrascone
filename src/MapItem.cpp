/*!
 * \file MapItem.cpp
 * \brief MapItem class implementation
 * \author João Gonçalves
 */

#include "MapItem.hpp"


MapItem::MapItem(){}
MapItem::~MapItem(){}

MapItem::MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key){
	
	span.push_back(
		std::pair<std::shared_ptr<Tile>, TypeIdentifier>(tile, key));
	
}

std::ostream& operator<<(std::ostream& os, const MapItem& item){
	item.myprint(os, item);
	return os;
}

std::ostream& MapItem::myprint(std::ostream& os, const MapItem& item)const{
	
	os << "Base type" << std::endl;
	return os;
}

std::vector<std::pair<std::shared_ptr<Tile>, TypeIdentifier>> const& MapItem::getSpan(void)const{
	return span;
}
