/*!
 * \file Field.cpp
 * \brief Field class implementation
 * \author João Gonçalves
 */

#include "Field.hpp"

Field::Field(){}

Field::Field(std::shared_ptr<Tile> tile, TypeIdentifier key): MapItem(tile, key){}

Field::~Field(){}

std::ostream& Field::myprint(std::ostream& os, const Field& f)const{

	os << "Field on tiles : ";
	
	std::string s;
	
	for(auto it=f.span.cbegin(); it!=f.span.cend(); it++){
		
		switch(it->second){
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
		os << "tiletype " << it->first->getTile() << " item " << s << " | ";
	}
	return os;

}
