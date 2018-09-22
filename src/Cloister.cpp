/*!
 * \file Cloister.hpp
 * \brief Cloister class implementation
 * \author João Gonçalves
 */

#include "Cloister.hpp"

Cloister::Cloister() : MapItem(){}

Cloister::Cloister(std::shared_ptr<Tile> tile, TypeIdentifier key) : MapItem(tile, key){}

Cloister::~Cloister(){}

std::ostream& Cloister::myprint(std::ostream& os, const Cloister& c)const{
	os << "Cloister on tile : ";
	
	std::string s;
	
	for(auto it=c.span.cbegin(); it!=c.span.cend(); it++){
		os << it->first->getTile(); 
	}
	
	os<<std::endl;
	
	return os;
	
}
