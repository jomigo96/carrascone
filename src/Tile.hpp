/*!
 * \file Tile.hpp
 * \brief Tile header file
 * \author João Gonçalves
 */

#ifndef TILE_HPP
#define TILE_HPP

#include "TileType.hpp"

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
	 * \brief checks if the calling tile fits somewhere
	 * \param other incomplete tiletype where the calling tile should go.
	 * \throw invalid_argument if the TileType is not incomplete, ie, at least one side mustn't be defined.
	 * */
	bool operator[](const TileType& other) const;
	
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
	int get_orientation(void) const;
	
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
	
private:
	int orientation;
};


#endif /* TILE_HPP */
