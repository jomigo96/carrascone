#ifndef MAP_HPP
#define MAP_HPP

#define TILESIZE 78

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <exception>
#include <memory>
#include "TileType.hpp"
#include "Cell.hpp"
#include "Tile.hpp"


class Map{
	
public:
	Map(sf::RenderWindow& window);
	~Map();
	
	TileType const& draw(void);
	
	bool play(std::shared_ptr<Tile> tile, Cell cell);
	
	void render(void) const;
	
private:
	sf::RenderWindow& window;
	
	std::map<TileType, sf::Texture> textures;
	std::map<TileType, int> deck;
	std::map<Cell, std::shared_ptr<Tile>> map;
	
	int deck_count(void) const;
};

#endif /* MAP_HPP */
