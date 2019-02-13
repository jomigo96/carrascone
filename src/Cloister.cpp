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

	Cell c;
	int count=0;

	//Get cloister's cell
	for(auto it=map.cbegin(); it!=map.cend(); it++)
		if((*it).second == std::get<0>(this->span[0]))
			c = (*it).first;
	for(int i=-1; i<2; i++)
		for(int j=-1; j<2; j++)
			count += map.count(c + Cell(i,j));


	if(count == 9){
#ifdef DEBUG_CLOISTER
		std::cout << "Cloister closed" << std::endl;
#endif
		this->closed = true;

		if(this->occupant){
			this->occupant = false;

			std::get<2>(this->span[0])->givePoints(9);
			std::get<2>(this->span[0])->givePiece();
			std::get<2>(this->span[0]).reset();
		}

	}

}
