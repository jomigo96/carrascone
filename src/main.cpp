#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "TileType.hpp"
#include "Cell.hpp"

int main(void){
	
	std::cout << "Carrascone is starting!" << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(480, 360), "Carrascone");
    window.setFramerateLimit(60);
    Map map(window);
    
    std::shared_ptr<Tile> tile (new Tile('i'));
    
    map.play(tile, Cell(1,1));	
    tile= std::shared_ptr<Tile>(new Tile('d'));
    tile->rotate_clockwise();tile->rotate_clockwise();
    map.play(tile, Cell(2,1));
    
    tile= std::shared_ptr<Tile>(new Tile('k'));
    tile->rotate_counter_clockwise();
    map.play(tile, Cell(1,2));
    
    tile= std::shared_ptr<Tile>(new Tile('d'));
    tile->rotate_clockwise();
    map.play(tile, Cell(0,2));
    
	
	while (window.isOpen()){
		
		sf::Event event;
		
		while( window.pollEvent(event) ){
			
			switch (event.type){
				
				case sf::Event::Closed:
				
					window.close();
					break;
					
					
				default:
					break;
			}
		}
		
		window.clear();
		
		map.render();
		
		window.display();
	}
	
	
	std::cout << "Carrascone is exiting, bye!" << std::endl; 
	
	return 0;
}
