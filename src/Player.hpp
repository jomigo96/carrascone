/*!
 * \file Player.hpp
 * \brief Player header file
 * \author João Gonçalves
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

/*!
 * \class Player
 * \brief
 * */
class Player{

public:

	Player();
	~Player();
	Player(const std::string& name, const sf::Color& colour);

	bool hasPieces()const;

	bool takePiece();
	bool givePiece();

private:
	unsigned piece_count;
	sf::Color color;
	std::string nickname;
};
#endif /* PLAYER_HPP */
