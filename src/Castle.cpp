/*!
 * \file Castle.cpp
 * \brief Castle class implementation
 * \author João Gonçalves
 */

#include "Castle.hpp"
#include <string>

Castle::Castle() : MapItem(){}

Castle::Castle(std::shared_ptr<Tile> tile, TypeIdentifier key) : MapItem(tile, key){}

Castle::~Castle(){}

std::ostream& Castle::myprint(std::ostream& os, const MapItem& item)const{

	os << "Castle on tiles : ";

	auto span = item.getSpan();

	std::string s;

	for(auto it=span.cbegin(); it!=span.cend(); it++){

		switch(std::get<1>(*it)){
			case castle1:
				s=std::string("castle1");
				break;
			case castle2:
				s=std::string("castle2");
				break;
			default: break;
		}
		os << "tiletype " << std::get<0>(*it)->getTile() << " item " << s << " | ";
	}
	os << std::endl;
	return os;
}

void Castle::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map){

}
