/*!
 * \file Road.cpp
 * \brief Road class implementation
 * \author João Gonçalves
 */

#include "Road.hpp"

Road::Road() : MapItem(){}

Road::Road(std::shared_ptr<Tile> tile, TypeIdentifier key) : MapItem(tile, key){}

Road::~Road(){}

std::ostream& Road::myprint(std::ostream& os, const MapItem& item)const{

	os << "Road on tiles : ";

	std::string s;
	auto span = item.getSpan();

	for(auto it=span.cbegin(); it!=span.cend(); it++){

		switch(std::get<1>(*it)){
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
		os << "tiletype " << std::get<0>(*it)->getTile() << " item " << s << " | ";
	}
	os << std::endl;
	return os;
}


int Road::countPoints(void)const{

	int points = 0;
	std::set<std::shared_ptr<Tile>> instances;
	for(auto it=span.cbegin(); it!=span.cend(); it++){
		if(instances.find(std::get<0>(*it)) == instances.end()){
			instances.insert(std::get<0>(*it));
			points ++;
		}
	}

	return points;
}
