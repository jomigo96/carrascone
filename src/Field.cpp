/*!
 * \file Field.cpp
 * \brief Field class implementation
 * \author João Gonçalves
 */

#include "Field.hpp"

Field::Field(){}

Field::Field(std::shared_ptr<Tile> tile, TypeIdentifier key): MapItem(tile, key){}

Field::~Field(){}

std::ostream& Field::myprint(std::ostream& os, const MapItem& item)const{

	os << "Field on tiles : ";

	std::string s;
	auto span = item.getSpan();

	for(auto it=span.cbegin(); it!=span.cend(); it++){

		switch(std::get<1>(*it)){
			case field1:
				s=std::string("field1");
				break;
			case field2:
				s=std::string("field2");
				break;
			case field3:
				s=std::string("field3");
				break;
			case field4:
				s=std::string("field4");
				break;
			default: break;
		}
		os << "tiletype " << std::get<0>(*it)->getTile() << " item " << s << " | ";
	}
	os << std::endl;
	return os;

}

void Field::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map){

}
