#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/Tile.hpp"
#include "../src/TileType.hpp"

TEST_CASE("Tile: test piece fits"){
	
	Tile t1('a');
	TileType tt1(field, road, field, none);
	
	REQUIRE(t1[tt1] == false);
	t1.rotate_counter_clockwise();
	REQUIRE(t1[tt1] == true);
	
	tt1=TileType(road, field, road, field);
	
	REQUIRE_THROWS_AS(t1[tt1], std::logic_error);
	
	tt1=TileType(road, field, castle, none);
	
	REQUIRE(t1[tt1] == false);
	
	t1=Tile('s');
	tt1=TileType(none, castle, road, none);
	
	REQUIRE(t1[tt1] == true);
	t1.rotate_clockwise();
	REQUIRE(t1[tt1] == false);
	
}
