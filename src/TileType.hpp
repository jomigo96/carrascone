/*!
 * \file TileType.hpp
 * \brief TileType header file
 * \author João Gonçalves
 */

#ifndef TILETYPE_HPP
#define TILETYPE_HPP

#include <iostream>
#include <string>
#include <exception>
#include "configs.hpp"

#define EMPTY_TILE 0
#define INVALID_TILE 1
#define INCOMPLETE_TILE 2

/*!
 * \enum ItemType
 * \brief Definitions the border types
 * */
enum ItemType{

	field,
	road,
	castle,
	none
};

/*!
 * \class TileType
 * \brief Identifies the type of tile piece, including partialy complete ones, in accordance to the png files, ie, does not specify orientation or position.
 */
class TileType{

public:

	/*!
     * \brief Constructor
     * Accepts all variables explicitly.
     * \param up boundary of the tile upwards.
     * \param right boundary of the tile to the right.
     * \param down boundary of the tile downwards.
     * \param left boundary of the tile to the left.
     * \param shield boolean that states weather a castle is shielded (ambiguities between tiles 'f' and 'g' for example).
     * \param connected boolean that states weather castles are connected (ambiguities between tiles 'i' and 'n' for example).
     */
	TileType(ItemType up, ItemType right, ItemType down, ItemType left, bool shield, bool connected);

     /*!
     * \brief Constructor
     * Accepts all boundary values, the other nuances are set to default values of no shield and not connected castles.
     * \param up boundary of the tile upwards.
     * \param right boundary of the tile to the right.
     * \param down boundary of the tile downwards.
     * \param left boundary of the tile to the left.
     */
	TileType(ItemType up, ItemType right, ItemType down, ItemType left);

	/*!
	 * \brief constructor, accepts the type of tile as used with the png files
	 * \param tile a letter (a-x) that specifies the type of tile.
	 * \throw invalid_argument if called with 0.
	 * */
	TileType(char tile);

	/*!
	 * \brief default constructor
	 * */
	TileType(void);

	/*!
	 * \brief class destructor
	 * */
	~TileType();

	/*!
	 * \brief equality operator
	 * returns true if and only if the tiles are the same existing type. Always false if one of them is incomplete or invalid
	 * */
	bool operator==(const TileType& other) const;

	/*!
	 * \brief innequality operator
	 * The output of this function is simply the opposite of the == operator
	 * */
	bool operator!=(const TileType& other) const;

	/*!
	 * \brief operator<
	 * To be used by containers that require sorting.
	 * The comparison is made based on the tile key, ie its letter according to the png files.
	 * */
	bool operator<(const TileType& other) const;

	/*!
	 * \brief stream output
	 * Used for debugging
	 * */
	friend std::ostream& operator<<( std::ostream& out, const TileType& type );

	/*!
	 * \brief operator[], information weather a tile fits somewhere, with some possible rotation.
	 * \param other other tile to be analysed, must be a valid kind.
	 * \throw invalid_argument if the calling tile is not incomplete (has all sides defined) or if the second is not valid.
	 * \return bool result of the assertion.
	 * */
	bool operator[](const TileType& other) const;

	/*!
	 * \brief validity check
	 * valid tiles are those that correspond to a possible tile as in the png files.
	 * */
	bool isValid(void) const;

	/*!
	 * \brief completeness check
	 * complete tiles are those that have all sides defined.
	 * */
	bool isComplete(void) const;

	/*!
	 * \brief Shield check
	 * */
	bool hasShield(void) const;

	/*!
	 * \brief castle connection check
	 *  */
	bool isConnected() const;

	/*!
	 * \brief getter for the tile type key
	 * */
	char getTile(void) const;

	/*!
	 * \brief getter for the description (for debugging)
	 */
	std::string const& getDescription(void) const;

	/*!
	 * \brief getter for the upwards boundary
	 * */
	ItemType getUp() const;

	/*!
	 * \brief getter for the right boundary
	 * */
	ItemType getRight() const;

	/*!
	 * \brief getter for the left boundary
	 * */
	ItemType getLeft() const;

	/*!
	 * \brief getter for the downwards boundary
	 * */
	ItemType getDown() const;


protected:

	ItemType up;
	ItemType right;
	ItemType down;
	ItemType left;
	char tile;
	bool shield;
	bool connected;
	std::string description;



private:

	void attribute(void);
};

/*!
 * \brief Compares the circle abcd to efgh. Works for numbers 0-15
 *  Assigning one of the first 4 parameters -1 means that this slot will be ignored in the comparison
 */
bool circle_comparison(int a, int b, int c, int d, int e, int f, int g, int h);

#endif /* TILETYPE */
