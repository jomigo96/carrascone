#include "Map.hpp"



Map::Map(sf::Window& window): window(window){
	
	//textures.reserve(24);
	std::cout << "Map constructor" << std::endl;
}

Map::~Map(){}


void Map::load(){
	
	const int count = 'x' - 'a';
	char file[] = "textures/tile-a.png";
	sf::Texture tex;
	
	for(int i=0; i<=count; i++){
		
		file[14] = 'a' + i;
		
		if(!tex.loadFromFile(file)){
			std::cout << "Error loading file: "<< file << std::endl; 
			throw "File not found";
		}
		//textures[i] = tex;
		
	}
	std::cout << "Tiles loaded" << std::endl;
	
}
