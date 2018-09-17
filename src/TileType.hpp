#ifndef TILETYPE_HPP
#define TILETYPE_HPP


#include <iostream>
#include <string>
#include <exception>

#define INVALID_TILE 0
#define INCOMPLETE_TILE 1

/*!
 * Definitions of tile types according to the png files
 * 
 * 
 * 
 * */

enum ItemType{

	field,
	road,
	castle, 
	none
};

class TileType{
	
public:

	TileType(ItemType up, ItemType right, ItemType down, ItemType left, bool shield, bool connected);
	
	TileType(ItemType up, ItemType right, ItemType down, ItemType left);
	
	TileType(char tile);
	
	TileType(void);
	
	~TileType();
	
	bool operator==(const TileType& other) const;
	
	bool operator!=(const TileType& other) const;
	
	bool operator<(const TileType& other) const;
	
	friend std::ostream& operator<<( std::ostream& out, const TileType& type );
	
	//void operator=(const TileType& other);
	
	bool operator[](const TileType& other) const;
	
	bool isValid(void) const;
	
	bool isComplete(void) const;
	
	bool hasShield(void) const;
	
	bool isConnected() const;
	
	char getTile(void) const;
	
	std::string const& getDescription(void) const;
	
	int getUp() const;
	
	int getRight() const;
	
	int getLeft() const;
	
	int getDown() const;
	
protected:

	ItemType up;
	ItemType right;
	ItemType down;
	ItemType left;
	char tile;
	bool shield;
	bool connected;
	std::string description;
	
	void attribute(void);
};

/*!
 * \brief Compares the circle abcd to efgh. Works for numbers 0-15
 *  Assigning one of the first 4 parameters -1 means that this slot will be ignored in the comparison
 */ 
bool circle_comparison(int a, int b, int c, int d, int e, int f, int g, int h);

#endif /* TILETYPE */
