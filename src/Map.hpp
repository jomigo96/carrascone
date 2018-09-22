/*!
 * \file Map.hpp
 * \brief Map header file
 * \author João Gonçalves
 */

#ifndef MAP_HPP
#define MAP_HPP

#define TILESIZE 78
#define TILE_NUMBER 24
#define TILE_WEIGHTS {2, 4, 1, 2, 5, 2, 1, 3, 2, 3, 3, 3, 2, 3, 2, 3, 1, 3, 2, 1, 8, 9, 4, 1}

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <exception>
#include <memory>
#include "TileType.hpp"
#include "Cell.hpp"
#include "Tile.hpp"


/*!
 * \class Map
 * \brief Map class, stores and manipulates all tiles played, and displayes them to the SFML window.
 * */
class Map{
	
public:

	/*!
	 * \brief contructor
	 * \param window SFML render window object.
	 * \param path directory with the png files, ending with a '/'
	 * */
	Map(sf::RenderWindow& window, const std::string& path);
	
	/*!
	 * \brief destructor
	 * */
	~Map(); 
	
	/*!
	 * \brief draw one tile from the deck at random
	 * \return TileType reference to that tile 
	 * \throw length_error if the deck is empty
	 * */
	TileType const& draw(void);
	
	/*!
	 * \brief play a Tile in a given position. Checks if is a valid placement. Always succeds on the first placement, and does not decrement that tile on the deck
	 * \param tile Tile to be played
	 * \param cell position where the tile is to be played
	 * \return boolean stating if the play was successful (possible)
	 * */
	bool play(std::shared_ptr<Tile> tile, Cell cell);
	
	/*! 
	 * \brief Renders all tiles to the render window (does not display)
	 * */
	void render(void) const;
	
	/*! 
	 * \brief stream output
	 * For debugging, specifies the tiles on the deck/played
	 * */
	friend std::ostream& operator<<(std::ostream& os, const Map& map);
	
	/*!
	 * \brief adds the Tile currently being played
	 * \param tile tile to be played
	 * */
	void setPlayable(std::shared_ptr<const Tile> tile);
	
	/*! 
	 * \brief setter for the position of the playable tile, in grid coordinates
	 * */
	void setPlayablePos(int x, int y);
	
	/*!
	 * \brief destroys the current playable tile
	 * */
	void clearPlayable(void);
	
	/*!
	 * \brief Asserts the neighbourhood of a map position, in the form of a TileType object
	 * \param c cell position
	 * \return TileType object (can be valid, incomplete, default type...)
	 * */
	TileType getSurroundings(const Cell& c) const;
	
	/*!
	 * \brief checks if a cell is occupied by an already played tile
	 * \param c cell object
	 * \return boolean
	 * */
	bool cellOccupied(const Cell& c)const;
	
	/*!
	 * \brief counts the tiles still present in the deck.
	 */
	int deck_count(void) const;
	
private:
	sf::RenderWindow& window;
	
	std::map<TileType, sf::Texture> textures;
	std::map<TileType, int> deck;
	std::map<Cell, std::shared_ptr<Tile>> map;
	
	std::shared_ptr<const Tile> playable;
	sf::Vector2f playable_pos; 
	

};

#endif /* MAP_HPP */
