#include "PlayerManager.hpp"

PlayerManager::PlayerManager(sf::RenderWindow& window, sf::Texture tex,
    std::string const& path, int deck_count) : window(window), meeple_tex(tex), deck_count(deck_count){

    state=start;
    deck_size = deck_count;

    if(!font.loadFromFile(path + std::string("Lato-Medium.ttf"))){
        std::cerr << "Error opening font" << std::endl;
        throw std::runtime_error("ttf file error");
    }
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

    state=close_state;
}

void PlayerManager::tilePlayed(){
    deck_count--;
}

sf::Font const& PlayerManager::getFont()const{
    return font;
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

void PlayerManager::renderMenu()const{

    const sf::Vector2f origin(1120,50);
    sf::Sprite sprite(meeple_tex);
    sf::Text text(std::string(), font, (int)text_height);
    std::stringstream stream;

    text.setFillColor(sf::Color::White);


    auto size = meeple_tex.getSize();
    sprite.setScale(text_height/size.x, text_height/size.y);
    //sprite.setOrigin(size.x/2, size.y/2);

    int dev=0;
    for(auto it=players.cbegin(); it!=players.cend(); it++, dev += text_height*3){
        sprite.setColor((*it)->getColor());
        sprite.setPosition(origin + sf::Vector2f(0, dev + text_height*1.2));
        window.draw(sprite);

        text.setPosition(origin + sf::Vector2f(0, dev));
        text.setString((*it)->getNickname());
        window.draw(text);

        text.setPosition(origin + sf::Vector2f(text_height+10, dev + text_height*1.2));
        stream = std::stringstream();
        stream << "x" << (*it)->getPieces() << "    " << (*it)->getPoints();
        text.setString( stream.str() );
        window.draw(text);
    }

    stream = std::stringstream();
    stream << "Tiles: " << deck_count << "/" << deck_size;
    text.setString( stream.str() );
    text.setPosition(origin + sf::Vector2f(0, dev + text_height*1.2));

    window.draw(text);

}
