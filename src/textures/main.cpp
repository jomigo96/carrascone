#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * File src/textures/main.cpp
 * 
 * Tool to count the pixel dimentions of the regular tiles
 * 
 * */

int main(void){
	
	const int count = 'x' - 'a';
	char file[] = "tile-a.png";
	
	for(int i=0; i<=count; i++){
		
		file[5] = 'a' + i;
		
		sf::Texture tex;
		
		if(!tex.loadFromFile(file)){
			std::cout << "Error loading file: "<< file << std::endl;
		}
		
		sf::Vector2u v = tex.getSize();
		
		std::cout << "Tile " << (char)('a'+i) << ": " << v.x << 'x' << v.y << " pixels" << std::endl;
	}
	std::cout << "Done" << std::endl;
	
	return 0;
}
