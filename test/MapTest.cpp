#include "catch.hpp"
#include "../src/Map.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <memory>


using namespace std;

/*
TEST_CASE("Map: Randomness"){
	
	sf::RenderWindow window(sf::VideoMode(1280,720), "Carrascone");
    window.setFramerateLimit(60);
	window.close();
	
	const int tests = 500;
	int weights[] = TILE_WEIGHTS;
	int expected[24];
	int results[24]; 
	
	int tilecount=0;
	for(int i=0; i<24; i++){
		
		tilecount+=weights[i];
	}
	
	for(int i=0; i<24; i++){
		
		results[i] = 0;
		expected[i] = tests * weights[i] / tilecount;
	}
	char c;
	
	
	for(int i=0; i<tests; i++){
		
		Map* map = new Map(window, std::string("../src/textures/"));
		c=map->draw().getTile();
		results[c-'a']++;
		delete map;
	}
	
	for(int i=0; i<24; i++){
		
		std::cout << "Tile " << char(i+'a') << ": " << results[i] << "/" << expected[i] << std::endl;
		//CHECK( (double)abs(results[i]-expected[i]) / (double)results[i] < 0.25 );
	}
}
*/

/*
TEST_CASE("Map: draw, count"){
	
	sf::RenderWindow window;
	
	Map map(window, std::string("../src/textures/"));
	int weights[] = TILE_WEIGHTS;
	int tiles = TILE_NUMBER;
	
	int count = 0;
	for(int i=0; i<tiles; i++)
		count+=weights[i];
	
	REQUIRE(count == map.deck_count());
	Tile tile = map.draw();
	REQUIRE(count == map.deck_count());
	
	//play that piece somewhere
	Cell c(7,5);
	int j=0;
	std::shared_ptr<Tile> play(new Tile(tile.getTile()));
	
	while(!map.play(play, c)){
		play->rotate_clockwise();
		j++;
		if(j>4){
			c=Cell(8,4);
			if(j>8)
				c=Cell(6,4);
		}
	}
	REQUIRE(--count == map.deck_count());
}*/


TEST_CASE("Merges"){
	
	sf::RenderWindow window(sf::VideoMode(1280,720), "Carrascone");
    window.setFramerateLimit(60);
	//window.close();	
	
	Map map(window, std::string("../src/textures/"));
	/*
	shared_ptr<Tile> tile(new Tile('u'));
	CHECK(map.play(tile, Cell(6,4))==true);
	
	tile = shared_ptr<Tile>(new Tile('u'));
	CHECK(map.play(tile, Cell(7,5))==true);
	
	tile = shared_ptr<Tile>(new Tile('v'));
	tile->rotate_clockwise();
	CHECK(map.play(tile, Cell(6,5))==true);
	
	
	shared_ptr<Tile> tile(new Tile('a'));
	CHECK(map.play(tile, Cell(7,3))==true);
	*/
	
	shared_ptr<Tile> tile(new Tile('v'));
	map.play(tile, Cell(7,3));
	tile=shared_ptr<Tile>(new Tile('v'));
	tile->rotate_clockwise(); tile->rotate_clockwise();
	map.play(tile, Cell(6,3));
	tile=shared_ptr<Tile>(new Tile('v'));
	map.play(tile, Cell(7,2));
	tile=shared_ptr<Tile>(new Tile('v'));
	tile->rotate_clockwise(); tile->rotate_clockwise();
	map.play(tile, Cell(8,3));
	tile=shared_ptr<Tile>(new Tile('u'));
	tile->rotate_clockwise();
	map.play(tile, Cell(7,2));
	tile=shared_ptr<Tile>(new Tile('v'));
	tile->rotate_counter_clockwise();
	map.play(tile, Cell(6,2));
	
	cout<<map;
	//This fails
	tile=shared_ptr<Tile>(new Tile('v'));
	map.play(tile, Cell(8,2));
	
	
	map.render();
	window.display();
	getchar();
	std::cout << map;
}




