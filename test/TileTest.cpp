#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/Tile.hpp"
#include "../src/TileType.hpp"
#include "../src/MapItem.hpp"
#include <tuple>
#include <exception>

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

TEST_CASE("Tile: MapItem getters"){
	
	std::tuple<TypeIdentifier, TypeIdentifier, TypeIdentifier> out, exp;
	TypeIdentifier& first = std::get<0>(exp);
	TypeIdentifier& second = std::get<1>(exp);
	TypeIdentifier& third = std::get<2>(exp);
	
	//For these sections the tile is rotated
	SECTION("Tile 'a'"){
		Tile tile('a');
		
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		
		out = tile.getMapItems(down);
		first=field1; second=field1; third=road1;
		CHECK(out == exp);
		
		tile.rotate_clockwise();
		
		out = tile.getMapItems(left);
		first=field1; second=field1; third=road1;
		CHECK(out == exp);
		
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
	}
	SECTION("Tile 'b'"){
		Tile tile('b');
		
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		
	}
	SECTION("Tile 'l'"){
	
		Tile tile = Tile('l');
		
		out = tile.getMapItems(left);
		first=field3; second=field1; third=road3;
		CHECK(out == exp);
		
		out = tile.getMapItems(down);
		first=field2; second=field3; third=road2;
		CHECK(out == exp);
		
		tile.rotate_clockwise();
		
		out = tile.getMapItems(down);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		
		out = tile.getMapItems(right);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);

	}
	
	//On all other sections we dont rotate the tile
	SECTION("Tile 'c'"){
		
		Tile tile('c');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);			
		out = tile.getMapItems(right);
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		CHECK(out == exp);	
				
	}
	SECTION("Tile 'd'"){
		
		Tile tile('d');
		out = tile.getMapItems(up);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);			
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);			
		
	}
	SECTION("Tile 'e'"){
		
		Tile tile('e');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);			
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		CHECK(out == exp);	
		
	}
	SECTION("Tile 'f'"){
		
		Tile tile('f');
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);		
		
	}
	SECTION("Tile 'g'"){
		
		Tile tile('g');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field2; second=invalid; third=invalid;
		CHECK(out == exp);	
		
	}
	SECTION("Tile 'h'"){
		
		Tile tile('h');
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle2; second=invalid; third=invalid;
		CHECK(out == exp);	
		
	}
	SECTION("Tile 'i'"){
		
		Tile tile('i');
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=castle2; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);			
		
	}
	SECTION("Tile 'j'"){
		
		Tile tile('j');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);		
		
	}
	SECTION("Tile 'k'"){
		
		Tile tile('k');
		out = tile.getMapItems(up);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);			
		
	}
	SECTION("Tiles 'm' and 'n'"){
		
		Tile tile('m');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		
		tile = Tile('n');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);				
		
	}
	SECTION("Tiles 'o' and 'p'"){
		
		Tile tile('o');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		
		tile=Tile('p');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);			
		
	}
	SECTION("Tiles 'q' and 'r'"){

		Tile tile('q');
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);		
		out = tile.getMapItems(left);
		CHECK(out == exp);
		out = tile.getMapItems(up);
		CHECK(out == exp);		
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		
		tile=Tile('r');
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);		
		out = tile.getMapItems(left);
		CHECK(out == exp);
		out = tile.getMapItems(up);
		CHECK(out == exp);		
		out = tile.getMapItems(down);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);			
			
	}
	SECTION("Tiles 's' and 't'"){
		
		Tile tile('s');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		
		tile=Tile('s');
		out = tile.getMapItems(up);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=castle1; second=invalid; third=invalid;
		CHECK(out == exp);				
		
	}
	SECTION("Tile 'u'"){
		
		Tile tile('u');
		out = tile.getMapItems(up);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);			
		out = tile.getMapItems(right);
		first=field2; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);					
	}	
	SECTION("Tile 'v'"){
		
		Tile tile('v');
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field2; second=field1; third=road1;
		CHECK(out == exp);		
		
	}
	SECTION("Tile 'w'"){
		
		Tile tile('w');
		out = tile.getMapItems(up);
		first=field1; second=invalid; third=invalid;
		CHECK(out == exp);			
		out = tile.getMapItems(right);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field2; second=field3; third=road2;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field3; second=field1; third=road3;
		CHECK(out == exp);					
	}
	SECTION("Tile 'x'"){
		
		Tile tile('x');
		out = tile.getMapItems(up);
		first=field1; second=field2; third=road1;
		CHECK(out == exp);
		out = tile.getMapItems(right);
		first=field2; second=field3; third=road2;
		CHECK(out == exp);	
		out = tile.getMapItems(down);
		first=field3; second=field4; third=road3;
		CHECK(out == exp);	
		out = tile.getMapItems(left);
		first=field4; second=field1; third=road4;
		CHECK(out == exp);			
		
	}
}
