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

void Field::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const&){
	//Do nothing
}

void Field::giveRemainingPoints(std::map<Cell, std::shared_ptr<Tile>> const& ){
	//Do nothing
}

void Field::giveRemainingPoints(int castles){
	if(occupant){
		occupant=false;

		std::map<std::shared_ptr<Player>, int> players;

		for(auto it=span.begin(); it!= span.end(); it++){
			if(std::get<2>(*it)!=nullptr){

				if(players.find(std::get<2>(*it)) == players.end()){
					players[std::get<2>(*it)]=1;
				}else{
					players.at(std::get<2>(*it))++;
				}

				//remove from span
				std::get<2>(*it).reset();
			}
		}

		//Determine winner(s)
		int max=0;
		for(auto it=players.begin(); it!=players.end(); it++){
			max = ((*it).second > max) ? (*it).second : max;
		}
		//Give back followers and points
		for(auto it=players.begin(); it!=players.end(); it++){
			for(int i=0; i<(*it).second; i++)
				(*it).first->givePiece();
			if(max == (*it).second)
				(*it).first->givePoints(castles*3);
		}
	}
}
