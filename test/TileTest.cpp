#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/Tile.hpp"
#include "../src/TileType.hpp"
#include "../src/MapItem.hpp"
#include <stack>

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
	
	TypeIdentifier t1,t2,t3;
	
	SECTION("Tile 'a'"){
		Tile tile('a');
		
		std::stack<TypeIdentifier>* stack = tile.getMapItems(left);
		
		REQUIRE(stack->size() == 1);
		CHECK(stack->top() == field1);
		stack->pop();
		delete stack;
		
		tile.rotate_clockwise();
		stack = tile.getMapItems(left);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1==field1);
		CHECK(t2==field1);
		CHECK(t3==road1);

	}
	SECTION("Tile 'l'"){
	
		Tile tile = Tile('l');
		std::stack<TypeIdentifier>* stack = tile.getMapItems(left);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1==field3);
		CHECK(t2==field1);
		CHECK(t3==road3);
		
		tile.rotate_clockwise();
		stack = tile.getMapItems(left);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1 == field2);
		CHECK(t2 == field3);
		CHECK(t3 == road2);
		
		tile.rotate_clockwise();
		stack = tile.getMapItems(left);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1 == castle1);
	}
	SECTION("Tile 'r'"){
		std::stack<TypeIdentifier>* stack;
		
		Tile tile('r');
		
		stack=tile.getMapItems(left);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);
		stack=tile.getMapItems(up);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);
		stack=tile.getMapItems(right);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);
		stack=tile.getMapItems(down);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == field1);	
		
		tile.rotate_clockwise();
		
		stack=tile.getMapItems(left);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == field1);
		stack=tile.getMapItems(up);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);
		stack=tile.getMapItems(right);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);
		stack=tile.getMapItems(down);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == castle1);			
	}
	
	SECTION("Tile 'w'"){
		std::stack<TypeIdentifier>* stack;
		
		Tile tile('w');
		
		stack = tile.getMapItems(up);
		REQUIRE(stack->size() == 1);
		t1=stack->top(); stack->pop(); delete stack;
		CHECK(t1 == field1);
		
		stack = tile.getMapItems(right);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1 == field1);
		CHECK(t2 == field2);
		CHECK(t3 == road1);		
		
		stack = tile.getMapItems(down);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1 == field2);
		CHECK(t2 == field3);
		CHECK(t3 == road2);	
		
		stack = tile.getMapItems(left);
		REQUIRE(stack->size() == 3);
		t1=stack->top(); stack->pop();
		t2=stack->top(); stack->pop();
		t3=stack->top(); stack->pop();
		delete stack;
		
		CHECK(t1 == field3);
		CHECK(t2 == field1);
		CHECK(t3 == road3);	
	}
}
