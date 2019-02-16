/*!
 * \file main.cpp
 * \brief main source code
 * \author João Gonçalves
 */

#include "configs.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Menu.hpp"
#include "Tile.hpp"
#include "TileType.hpp"
#include "Cell.hpp"
#include "PlayerManager.hpp"
#include "Player.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv){

	po::options_description desc("Allowed options");

	std::string o_path;

	desc.add_options()
    ("help,h", "produce help message")
	("versus,v", "jump to the game in two player mode")
	("instructions,i", "see Carrascone instructions")
	("path,p", po::value<std::string>(&o_path), "path to the src directory, if running from another directory")
	;

	po::variables_map vm;
	try{
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}catch(std::exception& e){
		std::cerr << e.what() << std::endl << "Use --help for more information" << std::endl;
		return -1;
	}

	po::notify(vm);

	if (vm.count("help")) {
    	std::cout << desc << std::endl;
    	return 1;
	}
	if(vm.count("instructions")){
		std::cout << "Google it noob" << std::endl;
		return 1;
	}
	if(vm.count("path")){
		o_path.push_back('/');
	}

	std::cout << "Carrascone is starting!" << std::endl;

	const int screen_width = 1280;
	const int screen_height = 720;

	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Carrascone");
    window.setFramerateLimit(60);
    Map map(window, o_path + std::string("textures/"));

    PlayerManager manager(window, map.getMeeple(), o_path + std::string("fonts/"), map.deck_count());
    bool turn=true;
    Cell clicked;
    TileType surroundings;
    TileType t;
    sf::Event event;
	std::shared_ptr<Tile> current_tile;
	int mode = -1;
	int player_number = -1;

	if (vm.count("versus")){
		std::shared_ptr<Player> pl(new Player("Player 1", sf::Color::Red));
		manager.addPlayer(pl);
		pl = std::shared_ptr<Player>(new Player("Player 2", sf::Color::Blue));
		manager.addPlayer(pl);
	}else{
		// Start menu
		Menu menu(window, o_path + std::string("textures/"), o_path + std::string("fonts/"), screen_width, screen_height);

		std::vector<std::string> opt;
		opt.emplace_back("Local play");
		opt.emplace_back("Network play");
		menu.setOptionType(opt);

		while((window.isOpen()) && (mode<0)){
			while( window.pollEvent(event) ){
				switch (event.type) {
					case sf::Event::Closed:
						window.close();
						return 0;
					case sf::Event::KeyPressed:
						switch (event.key.code) {
							case sf::Keyboard::Up:
							case sf::Keyboard::K:
								menu.cycleUp();
								break;
							case sf::Keyboard::Down:
							case sf::Keyboard::J:
								menu.cycleDown();
								break;
							case sf::Keyboard::Return:
							case sf::Keyboard::Space:
								mode = menu.getSelectedItem();
								break;
							default: break;
						}
						break;
					default: break;
				}
			}
			window.clear();
			menu.render();
			window.display();
		}

		if(mode == 0){
			std::vector<int> opt2;
			opt2.push_back(2);
			opt2.push_back(3);
			opt2.push_back(4);
			opt2.push_back(5);
			menu.setQuerry("Number of players", opt2);

			while((window.isOpen()) && (player_number<0)){
				while( window.pollEvent(event) ){
					switch (event.type) {
						case sf::Event::Closed:
							window.close();
							return 0;
						case sf::Event::KeyPressed:
							switch (event.key.code) {
								case sf::Keyboard::Up:
								case sf::Keyboard::K:
									menu.cycleUp();
									break;
								case sf::Keyboard::Down:
								case sf::Keyboard::J:
									menu.cycleDown();
									break;
								case sf::Keyboard::Return:
								case sf::Keyboard::Space:
									player_number = opt2[(unsigned)menu.getSelectedItem()];
									break;
								default: break;
							}
							break;
						default: break;
					}
				}
				window.clear();
				menu.render();
				window.display();
			}

			std::shared_ptr<Player> pl;
			const sf::Color colors[5] = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color::Black, sf::Color::Green};
			std::string nickname;

			for(int i=1; i<=player_number; i++){
				menu.askPlayer(i);

				pl.reset();
				bool shift_case = false;

				while((window.isOpen()) && (pl==nullptr)){
					while( window.pollEvent(event) ){
						switch (event.type) {
							case sf::Event::Closed:
								window.close();
								return 0;
							case sf::Event::KeyPressed:{
								if((event.key.code == sf::Keyboard::Return)){
									nickname = menu.getEntry();
									if(nickname.size() > 0){
										pl = std::shared_ptr<Player>(new Player(nickname, colors[i-1]));
										manager.addPlayer(pl);
										continue;
									}
								}
								if((event.key.code >= sf::Keyboard::A)&&(event.key.code <= sf::Keyboard::Z)){
									char c = 'a'+(char)(event.key.code - sf::Keyboard::A);
									if(shift_case){
										c += 'A'-'a';
									}
									menu.addLetter(c);
								}
								if(event.key.code == sf::Keyboard::Space){
									menu.addLetter(' ');
								}
								if(event.key.code == sf::Keyboard::BackSpace){
									menu.removeLetter();
								}
								if(event.key.code == sf::Keyboard::LShift){
									shift_case = true;
								}
							}
							break;
							case::sf::Event::KeyReleased:{
								if(event.key.code == sf::Keyboard::LShift){
									shift_case = false;
								}
							}
							break;
							default: break;
						}
					}
					window.clear();
					menu.render();
					window.display();
				}
			}

		}else{
			std::cout << "Network mode will be added in the future!" << std::endl;
			return 0;
		}

/*
		std::shared_ptr<Player> pl(new Player("Player 1", sf::Color::Red));
		manager.addPlayer(pl);
		pl = std::shared_ptr<Player>(new Player("Player 2", sf::Color::Blue));
		manager.addPlayer(pl);*/
	}


	// Game loop
	while (window.isOpen()){

		switch (manager.getState()) {
			case start:{
				// Initial definition of player number and customizations
				manager.beginGame();
				break;
			}
			/////////////////////////////// Tile set ///////////////////////////
			case lay:

#ifdef DEBUG_MAIN3
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
				map.setPlayerColor(manager.getCurrentPlayer()->getColor());

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
											manager.tilePlayed();
											manager.nextState();
										}
										break;
									case sf::Mouse::Right:
										current_tile->rotate_clockwise();
										break;
									default: break;
								}
								break;

#ifdef DEBUG_MAIN
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
						manager.renderMenu();
						window.display();
					}
				}


				break;

			/////////////////////////////// Follower set ///////////////////////

			case follower:

				if(!(manager.getCurrentPlayer()->hasPieces())){
					manager.nextState();
					map.skipPlayable();
					break;
				}
				if(!(map.hasFreeRealEstate())){
					manager.nextState();
					map.skipPlayable();
					break;
				}


#ifdef DEBUG_MAIN3
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
										if(turn){
											manager.nextState();
										}
										break;
									case sf::Mouse::Right:
										manager.nextState();
										map.skipPlayable();
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
						manager.renderMenu();
						window.display();
					}
				}

				break;

			case accept:
#ifdef DEBUG_MAIN1
				std::cout << "Map boundaries: " << std::endl << "Up: " << map.getBoundaries(up) << std::endl <<
							"Right: " << map.getBoundaries(right) << std::endl <<
							"Down: " << map.getBoundaries(down) << std::endl <<
							"Left: " << map.getBoundaries(left) << std::endl;
#endif
				manager.nextState();
				break;
			case end_turn:
				//Count points etc
				map.closeItems(clicked);
				manager.nextState();
				break;
			case deck_finished:
				map.countRemainingPoints();
				manager.nextState();
				std::cout << manager;
				break;
			case end_game:
				while(window.pollEvent(event)){
					if(event.type == sf::Event::Closed){
						window.close();
						manager.closeWindow();
						break;
					}
				}
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
			manager.renderMenu();
			window.display();
		}

	}


	std::cout << "Carrascone is exiting, bye!" << std::endl;

	return 0;
}
