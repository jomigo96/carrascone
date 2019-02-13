#include "PlayerManager.hpp"

PlayerManager::PlayerManager(){

    state=start;
}

PlayerManager::~PlayerManager(){}


void PlayerManager::beginGame(){
    state=lay;
    current_player=players.begin();
}

State PlayerManager::getState()const{

    return state;
}

void PlayerManager::endDeck(){

    state = deck_finished;
}

void PlayerManager::closeWindow(){

    state=close;
}

void PlayerManager::nextState(){

    switch (state) {
        case start:
            if(players.size()>1){
                current_player = players.begin();
                state=lay;
            }
            break;
        case lay:
            state=follower;
            break;
        case follower:
            state=accept;
            break;
        case accept:
            if(++current_player == players.end())
                current_player = players.begin();
            state=end_turn;
            break;
        case end_turn:
            state=lay;
            break;
        case deck_finished:
            state = end_game;
            break;
        default:
            break;
    }
}

bool PlayerManager::addPlayer(std::shared_ptr<Player> player){

    if(players.size() < 5){
        for(auto it=players.cbegin(); it!=players.cend(); it++){
            if(*player == **it)
                return false;
        }
        players.push_back(player);
        return true;
    }
    return false;
}

std::shared_ptr<Player> PlayerManager::getCurrentPlayer(){
    if(current_player!=players.end())
        return *current_player;
    else
        return nullptr;
}

std::ostream& operator<<(std::ostream& os, const PlayerManager& manager){

    switch (manager.state) {
        case lay:
            if(manager.players.size() > 0)
                os << "Player " << (*(manager.current_player))->getNickname() << " to play a tile." << std::endl;
            else
                os << "No players" << std::endl;
            break;
        case follower:
            if(manager.players.size() > 0)
                os << "Player " << (*(manager.current_player))->getNickname() << " to invest a follower." << std::endl;
            else
                os << "No players" << std::endl;
            break;
        case end_game:
            for(auto it=manager.players.cbegin(); it!=manager.players.cend(); it++){
                os << "Player " << (*it)->getNickname() << " finished with " << (*it)->getPoints() << " points" << std::endl;
            }
            break;
        default: break;
    }


    return os;
}
