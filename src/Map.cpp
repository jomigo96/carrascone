/*!
 * \file Map.cpp
 * \brief Map class implementation
 * \author João Gonçalves
 */

#include "Map.hpp"
#include <cstdlib>
#include <sys/time.h>


Map::Map(sf::RenderWindow& window, const std::string& path): window(window){
	
	//Load tile textures
	const int count = 'x' - 'a';
	char file[] = "tile-a.png";
	sf::Texture tex;
	
	//Build deck
	const int weights[] = TILE_WEIGHTS;
	
	for(int i=0; i<=count; i++){
		
		file[5] = 'a' + i;
		
		if( !tex.loadFromFile( path + std::string(file) ) ){
			std::cout << "Error loading file: "<< file << std::endl; 
			throw std::runtime_error("png file error");
		}
		TileType tipe = TileType('a' + i);
		textures.emplace(tipe, tex);
		deck.emplace(tipe, weights[i]);
		
	}
	struct timeval tp;
	gettimeofday(&tp, NULL);
	srand(tp.tv_usec);
	
	std::shared_ptr<Tile> first(new Tile('d'));
	this->play(first, Cell(7,4));
	
	
	playable = std::shared_ptr<const Tile>(nullptr);
}

Map::~Map(){
	
	
	
	
}

TileType const& Map::draw(void){
	
	const int count = this->deck_count();
	if(count == 0)
		throw std::length_error("Deck seems to be empty");
		
	
	// To extract one random tile, must be fair with regard to the total number of tiles.
	int v = rand() % count;
	
	for (auto i = deck.begin(); i != deck.end(); i++){
		
		if(i->second==0) //This type is all out
			continue;
			
		if((v-i->second) > 0){ //Not going to land here
			
			v-=i->second;
		}else{ //Lands here
			
			return i->first;
		}	
	}
	// By default returns the first I guess
	std::cout << "Warning: Random tile pull failed, returning first" << std::endl;
	return deck.begin()->first;
}

int Map::deck_count(void) const{
	
	int count = 0;

	for (std::map<TileType, int>::const_iterator i = deck.cbegin(); i != deck.cend();  i++){
		count += i->second;
	}
	
	return count;
}

bool Map::play(std::shared_ptr<Tile> tile, Cell cell){
	
	// TODO Checks if piece can be added there
	map.insert( std::pair<Cell, std::shared_ptr<Tile>>(cell, tile) );
	std::map<TileType, int>::iterator it = deck.find(*tile);
	if (it!=deck.end()){
		if (it->second >0){
			it->second--;
		}else
			return false;
	}else
		return false;
	return true;
}

void Map::render(void) const{
	
	sf::Sprite sprite;
	
	for(auto i = map.begin(); i!= map.end(); i++){
		
		Cell cell = i->first;
		Tile tile = *(i->second); 	
			
		std::map<TileType, sf::Texture>::const_iterator it = textures.find(tile);
		if(it == textures.end()){
			//std::cout << "Error looking up texture" << std::cout;
			continue;
		}	
			
		sprite.setTexture(it->second);
		sprite.setRotation(tile.getOrientation());
		int mod_x=(tile.getOrientation()==90 || tile.getOrientation()==180) ? 1 : 0;
		int mod_y=(tile.getOrientation()>90) ? 1 : 0;
		sprite.setPosition(sf::Vector2f(CELL_DIM*(cell.getX()+mod_x), CELL_DIM*(cell.getY()+mod_y)));
		window.draw(sprite);
	}
	if(playable){
		std::map<TileType, sf::Texture>::const_iterator it = textures.find(*playable);
		if(it == textures.cend())
			return; //Maybe exception
		sprite.setTexture(it->second);
		sprite.setRotation(playable->getOrientation());
		int mod_x=(playable->getOrientation()==90 || playable->getOrientation()==180) ? CELL_DIM/2 : -CELL_DIM/2;
		int mod_y=(playable->getOrientation()>90) ? CELL_DIM/2 : -CELL_DIM/2;
		sprite.setPosition(playable_pos+sf::Vector2f(mod_x, mod_y));
		window.draw(sprite);
	}
}


std::ostream& operator<<(std::ostream& os, const Map& map){
	
	os << std::endl << "showing deck" << std::endl;
	const int weights[] = TILE_WEIGHTS;
	for(auto it = map.deck.cbegin(); it != map.deck.cend(); it++){
	
		os << it->first.getDescription() << " -- count: " 
		   << it->second << '/' << weights[(int)it->first.getTile()-'a'] 
		   << std::endl;
	
	}
	
	return os;
}

void Map::setPlayable(std::shared_ptr<const Tile> tile){
	
	playable = tile;
	
}
void Map::setPlayablePos(int x, int y){
	
	playable_pos.x=x;
	playable_pos.y=y;
}

void Map::clearPlayable(void){
	
	playable.reset();
	
}

TileType Map::getSurroundings(const Cell& c) const{
	
	Cell aux = c + Cell(1,0); // cell to the right
	
	ItemType up, right, down, left;
	
	try{
		right = map.at(aux)->getLeft();
	}catch(std::out_of_range){
		right = none;		
	}
	
	aux = c + Cell(0,1); // Cell to the bottom
	
	try{
		down = map.at(aux)->getUp();
	}catch(std::out_of_range){
		down = none;		
	}
	
	aux = c + Cell(-1, 0); // Cell to the left
	
	try{
		left = map.at(aux)->getRight();
	}catch(std::out_of_range){
		left = none;		
	}
	
	aux = c + Cell(0, -1); // Cell to the top
	
	try{
		up = map.at(aux)->getDown();
	}catch(std::out_of_range){
		up = none;		
	}
	
	return TileType(up, right, down, left);
}

bool Map::cellOccupied(const Cell& c)const{
	
	return (bool)map.count(c);
	
}
