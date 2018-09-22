/*!
 * \file Road.cpp
 * \brief Road class implementation
 * \author João Gonçalves
 */

#include "Road.hpp"

Road::Road() : MapItem(){}

Road::Road(std::shared_ptr<Tile> tile, TypeIdentifier key) : MapItem(tile, key){}

Road::~Road(){}

std::ostream& Road::myprint(std::ostream& os, const Road& R)const{
	
	os << "road on tiles : ";
	
	std::string s;
	
	for(auto it=R.span.cbegin(); it!=R.span.cend(); it++){
		
		switch(it->second){
			case road1:
				s=std::string("road1");
				break;
			case road2:
				s=std::string("road2");
				break;
			case road3:
				s=std::string("road3");
				break;				
			case road4:
				s=std::string("road4");
				break;				
			default: break;
		}
		os << "tiletype " << it->first->getTile() << " item " << s << " | ";
	}
	return os;
}
