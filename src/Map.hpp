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
#define START_POSITION Cell(7,4)
#define CIRCLE_RADIUS 8

#include "configs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <exception>
#include <memory>
#include <list>
#include <cmath>
#include "TileType.hpp"
#include "Cell.hpp"
#include "Tile.hpp"
#include "MapItem.hpp"
#include "Field.hpp"
#include "Road.hpp"
#include "Castle.hpp"
#include "Cloister.hpp"

/*!
 * \class Map
 * \brief Map class, game interface class. Stores and manipulates all tiles played, and displayes them to the SFML window.
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

	//Go private after testing
	void getFreeRealEstate(std::shared_ptr<Tile> tile, std::list<TypeIdentifier>& target)const;

	bool setPiece(TypeIdentifier t, std::shared_ptr<Player> player);

	bool selectItemAt(sf::Vector2f pos, std::shared_ptr<Player> player);

	int getBoundaries(const Direction dir)const;

	void skipPlayable(void);


private:
	//Variables

	//Render Window
	sf::RenderWindow& window;

	//Textures for tiles
	std::map<TileType, sf::Texture> textures;

	//Deck (unplayed tiles)
	std::map<TileType, int> deck;

	//Map (played tiles)
	std::map<Cell, std::shared_ptr<Tile>> map;

	//Map Items (castles, fields, etc)
	std::list<std::shared_ptr<MapItem>> items;

	//Tile being played
	std::shared_ptr<const Tile> playable;

	//Position of the tile being played
	sf::Vector2f playable_pos;

	//Position clicked laying a follower
	sf::Vector2f follower_pos;

	//Tile just played
	std::shared_ptr<Tile> last_played;


	//Methods
	std::shared_ptr<const Tile> getTileAt(Cell c)const;
	inline bool mergeItems(Cell c, std::list<std::shared_ptr<MapItem>>& newitems);
	bool mapItemExists(std::shared_ptr<MapItem> item)const;

};

std::shared_ptr<MapItem> getItem(std::list<std::shared_ptr<MapItem>>& origin, std::shared_ptr<Tile> tile, TypeIdentifier type);

#endif /* MAP_HPP */
