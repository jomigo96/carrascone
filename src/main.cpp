#include <iostream>
#include <SFML/Graphics.hpp>

int main(void){
	
	std::cout << "Carrascone is starting!" << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(480, 360), "Sim city 2");
    window.setFramerateLimit(60);
	
	
	while (window.isOpen()){
		
		
		window.display();
	}
	
	
	std::cout << "Carrascone is exiting, bye!" << std::endl; 
	
	return 0;
}
