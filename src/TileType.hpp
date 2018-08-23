#ifndef TILETYPE_HPP
#define TILETYPE_HPP


#include <iostream>
#include <map>

enum MapDirection{

	up,
	right,
	down,
	left
	
};

enum ItemType{

	field,
	road,
	castle
	
};

class TileType{
	
public:

	TileType(ItemType a, ItemType b, ItemType c, ItemType d);
	
	~TileType();
	
	bool operator==(const TileType& other) const;
	
	bool operator!=(const TileType& other) const;
	
	friend std::ostream& operator<<( std::ostream &out, const TileType& D );
	
	void operator=(const TileType& other);
	
	bool isValid(void) const;
	
	bool hasShield(void) const;
	
	const std::map<MapDirection, ItemType>& getType() const;
	
	
private:

	std::map<MapDirection, ItemType> type;
	bool shield;
};

#endif /* TILETYPE */
