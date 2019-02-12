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

void Road::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const&){

	int endpoint_count=0;
	const char endpoints[] = {'a', 'l', 's', 't', 'w', 'x'};
	const std::set<char> endpoints_set = std::set<char>(endpoints, endpoints+6);

	for(auto it=span.cbegin(); it!=span.cend(); it++){
		if(endpoints_set.find(std::get<0>(*it)->getTile()) != endpoints_set.end())
			endpoint_count++;
	}

	if(endpoint_count == 2){
#ifdef DEBUG_ROAD
		std::cout << "Road is closed" << std::endl;
#endif

		this->closed = true;
		if(this->occupant){
			this->occupant=false;

			std::map<std::shared_ptr<Player>, int> players;

			//Get players and inversor count
			for(auto it=span.begin(); it!= span.end(); it++){
				if(std::get<2>(*it)!=nullptr){

					try{
						players.at(std::get<2>(*it))++;
					}catch(std::out_of_range){
						players[std::get<2>(*it)]=1;
					}

					//remove from span
					std::get<2>(*it).reset();
				}
			}

			//TODO: Count unique tiles
			int points = this->span.size()*2;

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
					(*it).first->givePoints(points);
			}
		}
	}

}
