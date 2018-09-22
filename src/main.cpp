/*!
 * \file main.cpp
 * \brief main source code
 * \author João Gonçalves
 */

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "TileType.hpp"
#include "Cell.hpp"

int main(void){
	
	std::cout << "Carrascone is starting!" << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(1280,720), "Carrascone");
    window.setFramerateLimit(60);
    Map map(window, std::string("textures/"));
     
    std::cout << map;
    bool turn=true;
    Cell clicked;
    TileType surroundings;
    TileType t;
    sf::Event event;
	
	while (window.isOpen()){
		
		
		try{
			t=map.draw();
		}catch(std::length_error){
			std::cout << "Deck empty" << std::endl;
			window.close();
			break;
		}
		std::shared_ptr<Tile> tile(new Tile(t.getTile()));
		map.setPlayable(tile);
		turn=true;
		
		while(turn){
			
			while( window.pollEvent(event) ){
				
				switch (event.type){
					
					case sf::Event::Closed:
					
						window.close();
						turn = false;
						break;
						
					case sf::Event::MouseButtonPressed:
						
						switch (event.key.code){
							case sf::Mouse::Left:
								clicked = Cell(sf::Mouse::getPosition(window).x/CELL_DIM, sf::Mouse::getPosition(window).y/CELL_DIM);
								
								if( !(turn = !map.play(tile, clicked)))
									map.clearPlayable();
								break;

							case sf::Mouse::Right:
								tile->rotate_clockwise();
								break;
							default:
								break;
						}
						break;
						
					default:
						break;
				}
			}			
			if(window.isOpen()){
				map.setPlayablePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				window.clear();
				map.render();
				window.display();
			}
		}
		
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
