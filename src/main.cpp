/*!
 * \file main.cpp
 * \brief main source code
 * \author João Gonçalves
 */

#include "configs.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "TileType.hpp"
#include "Cell.hpp"
#include "PlayerManager.hpp"
#include "Player.hpp"

int main(void){

	std::cout << "Carrascone is starting!" << std::endl;

	sf::RenderWindow window(sf::VideoMode(1280,720), "Carrascone");
    window.setFramerateLimit(60);
    Map map(window, std::string("textures/"));

    PlayerManager manager;
    bool turn=true;
    Cell clicked;
    TileType surroundings;
    TileType t;
    sf::Event event;
	//std::shared_ptr<Player> current_player;
	std::shared_ptr<Tile> current_tile;

	//debug;


	// Game loop
	while (window.isOpen()){

		switch (manager.getState()) {
			case start:{
				// Initial definition of player number and customizations
				std::shared_ptr<Player> pl(new Player("Ganso", sf::Color::Red));
				manager.addPlayer(pl);
				pl = std::shared_ptr<Player>(new Player("Scrub", sf::Color::Blue));
				manager.addPlayer(pl);
				manager.beginGame();
				break;
			}
			/////////////////////////////// Tile set ///////////////////////////
			case lay:

#ifdef DEBUG_MAIN
				std::cout << manager;
#endif
				try{
					t = map.draw();
				}catch(std::length_error){
					manager.endDeck();
					break;
				}

				current_tile = std::shared_ptr<Tile>(new Tile(t));
				map.setPlayable(current_tile);

				while(manager.getState() == lay){
					while( window.pollEvent(event) ){
						switch(event.type){
							case sf::Event::Closed:
								window.close();
								manager.closeWindow();
								break;

							case sf::Event::MouseButtonPressed:
								switch (event.key.code) {
									case sf::Mouse::Left:
										clicked = Cell(sf::Mouse::getPosition(window).x/CELL_DIM, sf::Mouse::getPosition(window).y/CELL_DIM);

										turn = map.play(current_tile, clicked);
										if(turn){
											map.clearPlayable();
											manager.nextState();
										}
										break;
									case sf::Mouse::Right:
										current_tile->rotate_clockwise();
										break;
									default: break;
								}
								break;

#ifdef DEBUG_ALL
							case sf::Event::KeyPressed:

								switch (event.key.code) {
									case sf::Keyboard::P:
										std::cout << map;
										break;
									case sf::Keyboard::O:
										current_tile=std::shared_ptr<Tile>(new Tile(map.draw().getTile()));
										map.setPlayable(current_tile);
										break;
									default: break;
								}

								break;
#endif
							default: break;
						}
					}
					if(window.isOpen()){
						map.setPlayablePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
						window.clear();
						map.render();
						window.display();
					}
				}


				break;

			/////////////////////////////// Follower set ///////////////////////

			case follower:

				if(!(manager.getCurrentPlayer()->hasPieces())){
					manager.nextState();
					break;
				}
				// Also check here if Tile has any remaining items to claim, skip if so

#ifdef DEBUG_MAIN
				std::cout << manager;
#endif

				while(manager.getState() == follower){
					while( window.pollEvent(event) ){
						switch(event.type){
							case sf::Event::Closed:
								window.close();
								manager.closeWindow();
								break;

							case sf::Event::MouseButtonPressed:
								switch (event.key.code) {
									case sf::Mouse::Left:
										turn=map.selectItemAt(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y), manager.getCurrentPlayer());
										if(turn)
											manager.nextState();
										break;
									default: break;
								}
								break;

							case sf::Event::KeyPressed:

								switch (event.key.code) {
									case sf::Keyboard::S:
										manager.nextState();
										map.skipPlayable();
										break;
									default: break;
								}

									break;

							default: break;
						}
					}
					if(window.isOpen()){
						window.clear();
						map.render();
						window.display();
					}
				}

				break;
			case accept:
#ifdef DEBUG_MAIN
				std::cout << "Map boundaries: " << std::endl << "Up: " << map.getBoundaries(up) << std::endl <<
							"Right: " << map.getBoundaries(right) << std::endl <<
							"Down: " << map.getBoundaries(down) << std::endl <<
							"Left: " << map.getBoundaries(left) << std::endl;
#endif
				manager.nextState();
				break;
			case end:
				//Count points etc
				break;
			case error:
				window.close();
				break;
			default:
				break;




		}
		if(window.isOpen()){
			window.clear();
			map.render();
			window.display();
		}

	}


	std::cout << "Carrascone is exiting, bye!" << std::endl;

	return 0;
}
