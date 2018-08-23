#ifndef MAP_HPP
#define MAP_HPP

#define TILESIZE 78

#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include <exception>
#include "TileType.hpp"

class Map{
	
public:
	Map(sf::Window& window);
	~Map();
	
	void load(void);
	
private:
	sf::Window& window;
	
	std::set<TileType, sf::Texture> textures;
};

#endif /* MAP_HPP */
