#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/Tile.hpp"
#include "../src/TileType.hpp"

TEST_CASE("Tile: fits"){
	
	Tile tile('a');
	TileType type(field, field, road, field);
	
	REQUIRE(fits(tile, type) == true);
	tile.rotate_clockwise();
	REQUIRE(fits(tile, type) == false);
	tile.rotate_clockwise();
	REQUIRE(fits(tile, type) == false);
	tile.rotate_clockwise();
	REQUIRE(fits(tile, type) == false);
	tile.rotate_clockwise();
	REQUIRE(fits(tile, type) == true);
	
	tile=Tile('k');
	type=TileType(none, none, none, none);
	REQUIRE( fits(tile,type) == false );
	
	type=TileType(none, none, none, field);
	REQUIRE( fits(tile,type) == false );
	
	type=TileType(none, none, none, road);
	REQUIRE(fits(tile, type) == true);
}

TEST_CASE("Tile: getters"){
	
	Tile tile('v');
	REQUIRE(tile.getUp() == field);
	REQUIRE(tile.getRight() == field);
	REQUIRE(tile.getDown() == road);
	REQUIRE(tile.getLeft() == road);
	
	tile.rotate_clockwise();
	REQUIRE(tile.getUp() == road);
	REQUIRE(tile.getRight() == field);
	REQUIRE(tile.getDown() == field);
	REQUIRE(tile.getLeft() == road);	
	
	TileType t('v');
	tile=Tile(t);
	
	std::cout << tile.getUp() << std::endl << tile.getDown() << 
	 tile.getTile() <<std::endl;
	
	REQUIRE(tile.getUp() == field);
	REQUIRE(tile.getRight() == field);
	REQUIRE(tile.getDown() == road);
	REQUIRE(tile.getLeft() == road);
	
	tile.rotate_clockwise();
	REQUIRE(tile.getUp() == road);
	REQUIRE(tile.getRight() == field);
	REQUIRE(tile.getDown() == field);
	REQUIRE(tile.getLeft() == road);
}
