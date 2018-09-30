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
#include "Player.hpp"


enum State : unsigned{

	start,
	lay,
	follower,
	accept,
	end,
	close,
	error,
};


class PlayerManager{

public:
	PlayerManager();
	~PlayerManager();

	void beginGame();
	void endDeck();
	void closeWindow();
	void nextState();

	bool addPlayer(std::shared_ptr<Player> player);

	State getState()const;

	std::shared_ptr<Player> getCurrentPlayer();

	friend std::ostream& operator<<(std::ostream& os, const PlayerManager& manager);

private:

	State state;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Player>>::iterator current_player;
};



#endif /*PLAYERMANAGER_HPP*/
