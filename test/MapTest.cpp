#include "catch.hpp"
#include "../src/Map.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>

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
