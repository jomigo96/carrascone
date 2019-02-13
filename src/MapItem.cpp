/*!
 * \file MapItem.cpp
 * \brief MapItem class implementation
 * \author João Gonçalves
 */

#include "MapItem.hpp"
#include <exception>


MapItem::MapItem(){

	occupant=false;
	closed=false;
}

MapItem::~MapItem(){

	for(auto it=span.begin(); it!=span.end(); it++){
		std::get<0>(*it).reset();
		std::get<2>(*it).reset();
	}

}

MapItem::MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key){

	span.push_back(
		std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>(tile, key, nullptr));

	occupant=false;
	closed=false;
}

std::ostream& operator<<(std::ostream& os, const MapItem& item){
	item.myprint(os, item);
	return os;
}

std::ostream& MapItem::myprint(std::ostream& os, const MapItem& item)const{

	os << &item << std::endl;
	return os;
}

std::vector<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>> const& MapItem::getSpan(void)const{
	return span;
}


void MapItem::mergeWith(std::shared_ptr<MapItem> other){

	if(this == other.get())
		return;

	auto span = other->getSpan();

	this->span.reserve(span.size());

	for(auto it = span.cbegin(); it!=span.cend(); it++){
		this->span.push_back(*it);
	}

	this->occupant |= other->occupant;
}

TypeIdentifier MapItem::getFirst()const{

	if(this->span.size()>0)
		return std::get<1>(*this->span.begin());
	throw std::length_error("Empty mapitem");

}

bool MapItem::hasItem(std::shared_ptr<const Tile> tileptr, TypeIdentifier type)const{

	for(auto it=this->span.cbegin(); it!=this->span.cend(); it++){
		if((std::get<0>(*it) == tileptr)&&(std::get<1>(*it) == type))
			return true;
	}
	return false;

}

bool MapItem::hasTile(std::shared_ptr<Tile> tileptr)const{

	for(auto it=this->span.cbegin(); it!=this->span.cend(); it++){
		if((std::get<0>(*it) == tileptr))
			return true;
	}
	return false;

}


bool MapItem::hasOccupant()const{

	return occupant;
}


void MapItem::freeRealEstate(std::shared_ptr<Tile> tile, std::list<TypeIdentifier>& target)const{

	if(occupant)
		return;

	for(auto it=span.cbegin(); it!=span.cend(); it++){
		if(std::get<0>(*it) == tile){
			target.push_back(std::get<1>(*it));
		}
	}

}

bool MapItem::isClosed()const{

	return closed;
}

bool MapItem::claim(std::shared_ptr<const Tile> tile, TypeIdentifier type, std::shared_ptr<Player> player){

	if(occupant)
		return false;

	if(player == nullptr)
		throw std::invalid_argument("called with nullptr");

	for(auto it=span.begin(); it!= span.end(); it++){

		if((std::get<0>(*it) == tile)&&(std::get<1>(*it) == type)){
			std::get<2>(*it) = player;
			occupant = true;
			return true;
		}
	}

	return false;

}

void MapItem::getOccupiedPosition(std::list<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>>& list){

	for(auto it = span.cbegin(); it != span.cend(); it++){
		if(std::get<2>(*it) != nullptr){
			list.push_back(*it);
		}
	}
}

std::string print_TypeIdentifier(TypeIdentifier t){


	switch(t){
		case road1:
			return std::string("road1");

		case road2:
			return std::string("road2");
		case road3:
			return std::string("road3");
		case road4:
			return std::string("road4");

		//Castles
		case castle1:
			return std::string("castle1");
		case castle2:
			return std::string("castle2");

		//Fields
		case field1:
			return std::string("field1");
		case field2:
			return std::string("field2");
		case field3:
			return std::string("field3");
		case field4:
			return std::string("field4");

		case cloister:
			return std::string("cloister");

		//none
		default:
			return std::string("invalid");
	}
	return std::string("invalid");
}


void MapItem::checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map){

	TypeIdentifier t1;
	std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> r;
	Cell c;

	for(auto it=span.cbegin(); it!=span.cend(); it++){

		for(auto iit=map.cbegin(); iit!=map.cend(); iit++)
			if((*iit).second == std::get<0>(*it))
				c = (*iit).first;

		r = std::get<0>(*it)->getMapItems(up);
		t1 = std::get<1>(*it);
		if((t1 == std::get<0>(r))||(t1 == std::get<2>(r))){
			if(map.find(c+Cell(0,-1)) == map.end())
				return;
		}
		r = std::get<0>(*it)->getMapItems(right);
		t1 = std::get<1>(*it);
		if((t1 == std::get<0>(r))||(t1 == std::get<2>(r))){
			if(map.find(c+Cell(1,0)) == map.end())
				return;
		}
		r = std::get<0>(*it)->getMapItems(down);
		t1 = std::get<1>(*it);
		if((t1 == std::get<0>(r))||(t1 == std::get<2>(r))){
			if(map.find(c+Cell(0,1)) == map.end())
				return;
		}
		r = std::get<0>(*it)->getMapItems(left);
		t1 = std::get<1>(*it);
		if((t1 == std::get<0>(r))||(t1 == std::get<2>(r))){
			if(map.find(c+Cell(-1,0)) == map.end())
				return;
		}
	}

#ifdef DEBUG_MAP
		std::cout << "Road/Castle is closed" << std::endl;
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

			//Count unique tiles, take into account shields
			int points = this->countPoints();


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

int MapItem::countPoints(void)const{
	return -1;
}
