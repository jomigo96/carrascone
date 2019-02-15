/*!
   \file PlayerManager.hpp
   \brief
   \author João Gonçalves
*/

#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include "Player.hpp"
#include "Map.hpp"
#include "configs.hpp"


enum State : unsigned{

	start,
	lay,
	follower,
	accept,
	end_turn,
	end_game,
	deck_finished,
	close_state, //close already taken by boost
	error,
};


class PlayerManager{

public:
	PlayerManager(sf::RenderWindow& window, sf::Texture tex, std::string const& path, int deck_count);
	~PlayerManager();

	void beginGame();
	void endDeck();
	void closeWindow();
	void nextState();

	bool addPlayer(std::shared_ptr<Player> player);

	State getState()const;

	std::shared_ptr<Player> getCurrentPlayer();

	void renderMenu()const;

	void tilePlayed();

	sf::Font const& getFont()const;

	friend std::ostream& operator<<(std::ostream& os, const PlayerManager& manager);

private:

	State state;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Player>>::iterator current_player;

	sf::RenderWindow& window;
    sf::Texture meeple_tex;

	int deck_count;
	int deck_size;

	sf::Font font;
	static constexpr float text_height = 18.0;
};



#endif /*PLAYERMANAGER_HPP*/
