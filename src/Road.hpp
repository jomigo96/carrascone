/*!
 * \file Road.hpp
 * \brief Road header file
 * \author João Gonçalves
 */

#ifndef ROAD_HPP
#define ROAD_HPP

#include "MapItem.hpp"
#include <ostream>

/*!
 * \class Road
 * \brief 
 * */
class Road : public MapItem{
	
public:
	Road();
	Road(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~Road();

	std::ostream& myprint(std::ostream& os, const Road& R)const;

private:

};
#endif /* ROAD_HPP */
