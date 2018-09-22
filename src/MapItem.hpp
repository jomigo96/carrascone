/*!
 * \file MapItem.hpp
 * \brief MapItem header file
 * \author João Gonçalves
 */

#ifndef MAPITEM_HPP
#define MAPITEM_HPP

#include "Cell.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include <memory>
#include <vector>

/*!
 * \class MapItem
 * \brief Base class for map elements such as castles, fields, roads
 * */
class MapItem{
	
public:
	MapItem();
	//MapItem(const Tile& tile, int a);
	~MapItem();
	
	// merge - join two mapitems
	// score - attribute points to players uppon closure
	
private:
	std::vector<std::pair<Cell, std::shared_ptr<Tile>>> span;
	std::vector<std::shared_ptr<Player>> owners;
	// connects;
};
#endif /* MAPITEM_HPP */
