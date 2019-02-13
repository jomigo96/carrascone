/*!
 * \file Player.cpp
 * \brief Player class implementation
 * \author João Gonçalves
 */

#include "Player.hpp"

Player::Player(){

    piece_count=7;
    color = sf::Color::Red;
    nickname = std::string("Player");
    points=0;
}

Player::Player(const std::string& name, const sf::Color& colour){

    color=colour;
    piece_count=7;
    nickname=name;
    points=0;
}

Player::~Player(){}

bool Player::hasPieces()const{

    return piece_count > 0;
}

bool Player::takePiece(){

    if(piece_count > 0)
        return (piece_count--);
    else
        return false;
}

bool Player::givePiece(){

    if(piece_count < 7)
        return (piece_count++);
    else
        return false;
}


bool Player::operator==(const Player& other)const{

    return ((color == other.getColor())||(nickname == other.getNickname()));
}
bool Player::operator!=(const Player& other)const{

    return !(*this == other);
}

sf::Color const& Player::getColor()const{
    return color;
}

std::string const& Player::getNickname()const{
    return nickname;
}

void Player::givePoints(int p){
    if(p>0){
        points += p;
#ifdef DEBUG_PLAYER
        std::cout << nickname << " gets " << p << " points" << std::endl;
#endif
    }
}

int Player::getPoints()const{
    return points;
}
