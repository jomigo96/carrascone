#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/TileType.hpp"

	
TEST_CASE("Circular comparison"){
		int a,b,c,d,e,f,g,h;
	
		a=1; b=2; c=3; d=4; e=2; f=3; g=4; h=1;		
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == true);
		
		a=1; b=1; c=1; d=1; e=2; f=3; g=4; h=1;
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == false);
		
		a=1; b=2; c=3; d=4; e=1; f=2; g=3; h=4;
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == true);
		
		a=1; b=2; c=3; d=4; e=1; f=3; g=4; h=1;
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == false);
		
		a=4; b=2; c=3; d=4; e=3; f=4; g=4; h=2;
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == true);
		
		a=1; b=1; c=1; d=1; e=1; f=1; g=1; h=1;
		REQUIRE(circle_comparison(a,b,c,d,e,f,g,h) == true);
		
		//Testing joker sides
		
		REQUIRE(circle_comparison(-1, 1, 2, 3, 1, 1, 2, 3) == true);
		
		REQUIRE(circle_comparison(-1, 1, -1, 3, 1, 1, 3, 2) == true);
		
		REQUIRE(circle_comparison(1, -1, 2, 3, 3, 1, 2, 2) == true);
		
		REQUIRE(circle_comparison(1, -1, 2, 3, 3, 2, 2, 2) == false);
}

TEST_CASE("Testing constructors"){
	
	TileType* tile;
	TileType t = TileType('e');
	
	tile = new TileType(castle, field, field, field, false, false);
	REQUIRE(tile->getTile() == 'e');
	REQUIRE(tile->getUp() == castle);
	REQUIRE(tile->getRight() == field);
	REQUIRE(tile->getDown() == field);
	REQUIRE(tile->getLeft() == field);
	REQUIRE(t == *tile);
	t=TileType('b');
	REQUIRE(t != *tile);
	
	t=TileType('e');
	tile = new TileType(field, field, castle, field, false, false);
	REQUIRE(tile->getTile() == 'e');
	REQUIRE(tile->getUp() == field);
	REQUIRE(tile->getRight() == field);
	REQUIRE(tile->getDown() == castle);
	REQUIRE(tile->getLeft() == field);
	REQUIRE(t == *tile);
	t=TileType('b');
	REQUIRE(t != *tile);
	
	t=TileType(road, none, road, field);
	REQUIRE(t.getTile() == INCOMPLETE_TILE);
	
	//Rule of 3
	t=TileType(*tile);
	REQUIRE(t == *tile);
	t= *tile;
	REQUIRE(t == *tile);
	TileType tiile;
	REQUIRE(tiile.isValid() == false);
	
	
	//Undefined tiles
	delete tile;
	
	tile = new TileType(none, field, road, field);
	REQUIRE(*tile != t);
	REQUIRE(tile->isComplete() == false);
	*tile = TileType(castle, field, castle, field);
	REQUIRE(tile->isComplete() == true);

	delete tile;
}

TEST_CASE("Test []operator"){
	
	TileType tile1=TileType('l');
	TileType tile2=TileType(road, castle, none, road);
	
	
	REQUIRE(tile2[tile1] == true);
	
	tile1=TileType('d');
	
	REQUIRE(tile2[tile1] == false);
	
	tile2=TileType(none, none, castle, road);
	
	REQUIRE(tile2[tile1] == true);
	
	REQUIRE_THROWS_AS(tile1[tile2], std::invalid_argument);
	
	tile2=tile1;
	
	REQUIRE(tile2[tile1]);
}


	


