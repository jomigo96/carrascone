#ifndef MAP_HPP
#define MAP_HPP

#define TILESIZE 78
#define TILE_WEIGHTS {2, 4, 1, 2, 5, 2, 1, 3, 2, 3, 3, 3, 2, 3, 2, 3, 1, 3, 2, 1, 8, 9, 4, 1}

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
	
	friend std::ostream& operator<<(std::ostream& os, const Map& map);
	
	void setPlayable(std::shared_ptr<const Tile> tile);
	
	void setPlayablePos(int x, int y);
	
	void clearPlayable(void);
	
	TileType getSurroundings(const Cell& l) const;
	
	bool cellOccupied(const Cell& c)const;
	
private:
	sf::RenderWindow& window;
	
	std::map<TileType, sf::Texture> textures;
	std::map<TileType, int> deck;
	std::map<Cell, std::shared_ptr<Tile>> map;
	
	std::shared_ptr<const Tile> playable;
	sf::Vector2f playable_pos; 
	
	int deck_count(void) const;
};

#endif /* MAP_HPP */
