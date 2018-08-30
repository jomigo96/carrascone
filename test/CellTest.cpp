#include "catch.hpp"

#include <iostream>
#include <string>
#include "../src/Cell.hpp"

TEST_CASE("Cell: Constructors, rule of 3"){
	
	Cell c1 = Cell();
	Cell c2;
	REQUIRE(c2 == c1);
	
	Cell c3(1,3);
	REQUIRE(c3 == Cell(1,3));
	
	Cell c4 = c3;
	REQUIRE(c4 == c3);
	
	Cell c5(c3);
	REQUIRE(c3 == c5);
	
}

TEST_CASE("Cell: Basic operators"){
	
	Cell c1(1,2);
	Cell c2(1,1);
	
	REQUIRE((c1+c2).getX() == 2);
	REQUIRE((c1+c2).getY() == 3);
	REQUIRE((c1+c2) == Cell(2,3));
}

TEST_CASE("Cell: difference, greatest coordinate"){
	
	Cell c1(423, 223);
	Cell c2(2,3);
	
	REQUIRE((c1-c2)==Cell(421, 220));
	REQUIRE(c1.greatest() == 423);
}
