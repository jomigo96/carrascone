#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window, std::string const& path_textures, std::string const& path_fonts, int screen_width, int screen_height):
    window(window), tex_path(path_textures), screen_width(screen_width), screen_height(screen_height){

        if(!font.loadFromFile(path_fonts + std::string("Lato-Medium.ttf"))){
            std::cerr << "Error opening font" << std::endl;
            throw std::runtime_error("ttf file error");
        }
        menuType = option_selection;
}

Menu::~Menu(){}

void Menu::render()const{

    sf::Text text(std::string("Carrascone"), font, 50);
    text.setFillColor(sf::Color::White);

    auto bounds = text.getLocalBounds();
    const int x = screen_width/2.0-bounds.width/2.0;
    text.setPosition(sf::Vector2f(x, 50));
    window.draw(text);

    text.setCharacterSize(30);

    switch(menuType){
        case option_selection:{
            int dev=0;
            const sf::Vector2f origin(x, 200);
            for(auto it=options.cbegin(); it!=options.cend(); it++, dev+=40){
                text.setString((*it));
                text.setPosition(origin + sf::Vector2f(0, dev));
                window.draw(text);
            }
            sf::CircleShape circle(10);
            circle.setFillColor(sf::Color::White);
            circle.setPosition(origin + sf::Vector2f(-30, 8+selected_item*40));
            window.draw(circle);

        }
        break;
        case number_selection:{
            int dev=0;
            sf::Vector2f origin(x, 200);
            text.setString(title);
            text.setPosition(origin);
            text.setCharacterSize(35);
            window.draw(text);
            text.setCharacterSize(30);
            origin += sf::Vector2f(60,40);
            for(auto it=options.cbegin(); it!=options.cend(); it++, dev+=40){
                text.setString((*it));
                text.setPosition(origin + sf::Vector2f(0, dev));
                window.draw(text);
            }
            sf::CircleShape circle(10);
            circle.setFillColor(sf::Color::White);
            circle.setPosition(origin + sf::Vector2f(-30, 8+selected_item*40));
            window.draw(circle);
        }
        break;
        case player_nickname:{

            sf::Vector2f origin(x, 200);

            std::string out;
            for(auto it=nickname.cbegin(); it!=nickname.cend(); it++){
                out.push_back(*it);
            }

            text.setPosition(origin);
            text.setString(std::string("Player ") + std::to_string(player_n) + std::string(" nickname:"));
            window.draw(text);

            origin+=sf::Vector2f(60, 40);
            text.setPosition(origin);
            text.setString(out);
            window.draw(text);
        }
        break;
        default: break;
    }


}

void Menu::setQuerry(std::string const& querry, std::vector<int> const& option_list){
    menuType = number_selection;
    selected_item = 0;
    options.resize(option_list.size());
    for(unsigned i=0; i<option_list.size(); i++){
        options[i] = std::to_string(option_list[i]);
    }
    title = querry;
}

void Menu::setOptionType(std::vector<std::string> const& option_list){
    menuType = option_selection;
    options = option_list;
    selected_item = 0;
}

void Menu::cycleUp(){
    selected_item--;
    if(selected_item<0)
        selected_item=0;
}

void Menu::cycleDown(){
    selected_item++;
    if(selected_item >= (int)options.size())
        selected_item--;

}

int Menu::getSelectedItem()const{
    return selected_item;
}

void Menu::askPlayer(int player_no){
    menuType = player_nickname;
    player_n = player_no;
    nickname = std::deque<char>();
}

std::string Menu::getEntry()const{

    std::string out;

    for(auto it=nickname.cbegin(); it!=nickname.cend(); it++){
        out.push_back(*it);
    }

    return out;
}

void Menu::addLetter(char c){
    nickname.push_back(c);
    //std::cout << "Letter "<< c << std::endl;
}

void Menu::removeLetter(){
    if(!nickname.empty())
        nickname.pop_back();
}
