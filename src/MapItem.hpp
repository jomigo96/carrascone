/*!
 * \file MapItem.hpp
 * \brief MapItem header file
 * \author João Gonçalves
 */

#ifndef MAPITEM_HPP
#define MAPITEM_HPP

//#include "Cell.hpp"
#include "configs.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Cell.hpp"
#include <memory>
#include <vector>
#include <ostream>
#include <list>
#include <set>
#include <exception>
#include <string>

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

	cloister,

	//none
	invalid
};

//forward declarations
class Tile;
class Player;

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

	std::vector<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>>const& getSpan(void)const;

	TypeIdentifier getFirst()const;

	void mergeWith(std::shared_ptr<MapItem> other);

	bool hasItem(std::shared_ptr<const Tile> tileptr, TypeIdentifier type)const;

	bool hasTile(std::shared_ptr<Tile> tileptr)const;

	bool hasOccupant()const;

	bool isClosed()const;

	void freeRealEstate(std::shared_ptr<Tile> tile, std::list<TypeIdentifier>& target)const;

	bool claim(std::shared_ptr<const Tile> tile, TypeIdentifier type, std::shared_ptr<Player> player);

	void getOccupiedPosition(std::list<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>>& list);

	//Checks if it was closed with this play, gives points and followers back
	//Overriden for field and cloister types
	virtual void checkCloseAndProcess(std::map<Cell, std::shared_ptr<Tile>> const& map);

	virtual int countPoints(void)const;

	virtual void giveRemainingPoints(std::map<Cell, std::shared_ptr<Tile>> const& );

protected:
	std::vector<std::tuple<std::shared_ptr<Tile>, TypeIdentifier, std::shared_ptr<Player>>> span;
	bool occupant;
	bool closed;
	// connects;

private:
	virtual std::ostream& myprint(std::ostream& os, const MapItem& item)const;

};

// Non Member functions for debugging

std::string print_TypeIdentifier(TypeIdentifier t);

#endif /* MAPITEM_HPP */
