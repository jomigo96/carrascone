#include "Map.hpp"
#include <cstdlib>
#include <sys/time.h>


Map::Map(sf::RenderWindow& window): window(window){
	
	std::cout << "Map constructor" << std::endl;
	
	//Load tile textures
	const int count = 'x' - 'a';
	char file[] = "textures/tile-a.png";
	sf::Texture tex;
	
	//Build deck
	const int weights[] = TILE_WEIGHTS;
	
	for(int i=0; i<=count; i++){
		
		file[14] = 'a' + i;
		
		if(!tex.loadFromFile(file)){
			std::cout << "Error loading file: "<< file << std::endl; 
			throw std::runtime_error("png file error");
		}
		TileType tipe = TileType('a' + i);
		textures.emplace(tipe, tex);
		deck.emplace(tipe, weights[i]);
		
	}
	std::cout << "Tiles loaded, deck assembled" << std::endl;
	struct timeval tp;
	gettimeofday(&tp, NULL);
	srand(tp.tv_sec);
}

Map::~Map(){}

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
		sprite.setRotation(tile.get_orientation());
		int mod_x=(tile.get_orientation()==90 || tile.get_orientation()==180) ? 1 : 0;
		int mod_y=(tile.get_orientation()>90) ? 1 : 0;
		sprite.setPosition(sf::Vector2f(CELL_DIM*(cell.getX()+mod_x), CELL_DIM*(cell.getY()+mod_y)));
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
