/*!
 * \file Road.hpp
 * \brief Road header file
 * \author João Gonçalves
 */

#ifndef ROAD_HPP
#define ROAD_HPP

#include "configs.hpp"
#include "MapItem.hpp"
#include <ostream>
#include <set>


/*!
 * \class Road
 * \brief
 * */
class Road : public MapItem{

public:
	Road();
	Road(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~Road();

	std::ostream& myprint(std::ostream& os, const MapItem& item)const;

	void checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const&);

private:

};
#endif /* ROAD_HPP */
