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

	TileType(ItemType up, ItemType right, ItemType down, ItemType left, bool shield, bool connected=true);
	
	TileType(char tile);
	
	~TileType();
	
	bool operator==(const TileType& other) const;
	
	bool operator!=(const TileType& other) const;
	
	friend std::ostream& operator<<( std::ostream& out, const TileType& type );
	
	//void operator=(const TileType& other);
	
	bool operator[](const TileType& other) const;
	
	bool isValid(void) const;
	
	bool hasShield(void) const;
	
	char getTile(void) const;
	
	std::string const& getDescription(void) const;
	
	int getUp() const;
	
	int getRight() const;
	
	int getLeft() const;
	
	int getDown() const;
	
private:

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
 */ 
bool circle_comparison(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h);

#endif /* TILETYPE */
