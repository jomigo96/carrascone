/*!
 * \file MapItem.hpp
 * \brief MapItem header file
 * \author João Gonçalves
 */

#ifndef MAPITEM_HPP
#define MAPITEM_HPP

//#include "Cell.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include <memory>
#include <vector>
#include <ostream>
//#include <tuple>

class Tile;

/*!
 * \enum TypeIdentifier
 * \brief Information to identify a MapItem for each Tile
 * 
 * The used convention is with respect to the png files. Respecting the
 * order [up right down left], the first item is respective to the first
 * one appearing in this clockwise circling. For example, for TileType 
 * 'd', the field1 will be the big field to the left, then there is 
 * road1, then field2 will be the smaller field, then castle1. For
 * TileType 'l', field1 on the top left, field2 the larger one, field3
 * on the bottom left, road1 on top, road2 on bottom, road3 on the left,
 * and castle1 on the right.
 * */
enum TypeIdentifier: unsigned int{
	
	//Roads
	road1,
	road2,
	road3,
	road4,
	
	//Castles
	castle1,
	castle2,
	
	//Fields
	field1,
	field2,
	field3,
	field4,
	
	cloister
	
};

//forward declarations
class Tile;

/*!
 * \class MapItem
 * \brief Base class for map elements such as castles, fields, roads
 * */
class MapItem{
	
public:
	MapItem();
	MapItem(std::shared_ptr<Tile> tile, TypeIdentifier key);
	~MapItem();
	
	friend std::ostream& operator<<(std::ostream& os, const MapItem& item);
	
	// merge - join two mapitems(not for type cloister)
	// virtual score - attribute points to players uppon closure
	
	std::vector<std::pair<std::shared_ptr<Tile>, TypeIdentifier>> const& getSpan(void)const;
	std::vector<std::shared_ptr<Player>> const& getOwners()const;
	
	TypeIdentifier getFirst()const;
	
	void mergeWith(const MapItem& other);
	
	bool hasItem(std::shared_ptr<const Tile> tileptr, TypeIdentifier type)const;
	
protected:
	std::vector<std::pair<std::shared_ptr<Tile>, TypeIdentifier>> span;
	std::vector<std::shared_ptr<Player>> owners;
	// connects;
	
private:
	virtual std::ostream& myprint(std::ostream& os, const MapItem& item)const;
	
};
#endif /* MAPITEM_HPP */
