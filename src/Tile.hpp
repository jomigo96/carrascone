/*!
 * \file Tile.hpp
 * \brief Tile header file
 * \author João Gonçalves
 */

#ifndef TILE_HPP
#define TILE_HPP

#include "TileType.hpp"
#include "MapItem.hpp"
#include <stack>

class MapItem;

enum Direction : unsigned int{
	
	up,
	right,
	down,
	left
	
};

enum TypeIdentifier : unsigned int;

/*!
 * \class Tile
 * \brief Tile information, with orientation
 * */
class Tile : public TileType{
	
public:
	
	/*!
	 * \brief default constructor
	 * */
	Tile();
	
	/*!
	 * \brief constructor
	 * \param a tile type key
	 * */
	Tile(char a);
	
	/*!
	 * \brief constructor
	 * \param type tile type object
	 * */
	 Tile(const TileType& tile);
	
	/*!
	 * \brief destructor
	 * */
	~Tile();
	
	/*!
	 * \brief rotates the tile clockwise
	 * \return new orientation
	 * */
	int rotate_clockwise(void);

	/*!
	 * \brief rotates the tile counter-clockwise
	 * \return new orientation
	 * */
	int rotate_counter_clockwise(void);
	
	/*!
	 * \brief getter for the orientation
	 * */
	int getOrientation(void) const;
	
	/*!
	 * \brief getter for the actual upwards boundary, takes into account orientation
	 * */
	ItemType getUp()const;
	
	/*!
	 * \brief getter for the actual right boundary, takes into account orientation
	 * */	
	ItemType getRight()const;
	
	/*!
	 * \brief getter for the actual downwards boundary, takes into account orientation
	 * */
	ItemType getDown()const;
	
	/*!
	 * \brief getter for the actual left boundary, takes into account orientation
	 * */	
	ItemType getLeft()const;
	
	ItemType getSide(Direction d)const;

	/*!
	 * 	\brief returns a stack with the mapitems(identified by this Tile
	 *  pointer and the TypeIdentifier) to merge to. This stack should
	 *  then be deleted by the caller.
	 * 
	 * 	For ambiguities where two fields must be connected, the one 
	 *  which appears first in the stack(closer to the top) is the
	 *  one on the right-hand side.
	 *  \throw runtime_error
	 *  \throw logic_error
	 * */	
	std::stack<TypeIdentifier>* getMapItems(Direction d)const;
	
private:
	int orientation;
};

/*!
 * \brief Checks if a tile fits in a space
 * \param tile Tile to be placed
 * \param space TileType that supports it
 * \return boolean with the assertion result
 * \throw runtime_error if a weird bug causes orientation not to be one of 0 90 180 270.
 * \throw invalid_argument if the tile doesnt exist.
 * */
bool fits(const Tile& tile, const TileType& space);


#endif /* TILE_HPP */
