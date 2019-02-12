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

	os << "Cloister with tiletype " << std::get<0>(*span.cbegin())->getTile() << std::endl;

	return os;

}

void Cloister::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map){

}
