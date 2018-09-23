/*!
 * \file Cloister.hpp
 * \brief Cloister class implementation
 * \author João Gonçalves
 */

#include "Cloister.hpp"

Cloister::Cloister() : MapItem(){}

Cloister::Cloister(std::shared_ptr<Tile> tile, TypeIdentifier key) : MapItem(tile, key){}

Cloister::~Cloister(){}

std::ostream& Cloister::myprint(std::ostream& os, const MapItem& item)const{
	
	auto span = item.getSpan();
	
	os << "Cloister with tiletype " << span.cbegin()->first->getTile() << std::endl;
	
	return os;
	
}
