#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"



int main(void){
	
	std::cout << "Carrascone is starting!" << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(480, 360), "Carrascone");
    window.setFramerateLimit(60);
    Map map(window);
    map.load();
	
	sf::Texture tex_chappel;
	
	if(!tex_chappel.loadFromFile("textures/tile-a.png")){
		std::cout << "Error loading tile texture, exiting!" << std::endl;
		return -1;
	}
	
	sf::Sprite sprite(tex_chappel);
	
	
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
		
		window.draw(sprite);
		
		window.display();
	}
	
	
	std::cout << "Carrascone is exiting, bye!" << std::endl; 
	
	return 0;
}
