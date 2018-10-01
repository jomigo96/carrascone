/*!
 * \file Tile.hpp
 * \brief Tile header file
 * \author João Gonçalves
 */

#ifndef TILE_HPP
#define TILE_HPP

#include "TileType.hpp"
#include "SFML/Graphics.hpp"
#include "MapItem.hpp"
#include <tuple>

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
	 * \brief Determines the mapitems(identified by this Tile
	 * pointer and the TypeIdentifier) that can be merge to.
	 *
	 * In the case that the border is a field or a castle, it will be
	 * present in the first element of the tuple, and the other ones
	 * will hold invalid. In the case it is a road, the convention is
	 * the first element has the field to the right-hand side when
	 * looking at the tile border, the second element the one to the
	 * left-hand side, and the third one the road.
	 *
	 * \return A tuple with 3 elements, of which at least the first one
	 * has a useful value.
	 *
	 * \throw runtime_error if it encounters a weird mis-match in
	 * orientation. (should never happen)
	 * \throw logic_error if the tile is not a known type, from a-x.
	 * */
	std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> getMapItems(Direction d)const;

	sf::Vector2f getItemPosition(TypeIdentifier t)const;

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
