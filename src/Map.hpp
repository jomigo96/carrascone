#ifndef MAP_HPP
#define MAP_HPP

#define TILESIZE 78

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <exception>

class Map{
	
public:
	Map(sf::Window& window);
	~Map();
	
	void load(void);
	
private:
	sf::Window& window;
	
	std::vector<sf::Texture> textures;
};

#endif /* MAP_HPP */
