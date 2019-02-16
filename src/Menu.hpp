#ifndef MENU_HPP
#define MENU_HPP

#include "configs.hpp"
#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <deque>
#include <SFML/Graphics.hpp>

enum MenuType : int{
    option_selection,
    number_selection,
    player_nickname,
};

class Menu{

public:
    Menu(sf::RenderWindow& window, std::string const& path_textures, std::string const& path_fonts, int screen_width, int screen_height);
    virtual ~Menu();

    void render()const;

    void setOptionType(std::vector<std::string> const& option_list);

    void setQuerry(std::string const& querry, std::vector<int> const& option_list);

    void cycleUp();

    void cycleDown();

    int getSelectedItem()const;

    void askPlayer(int player_no);

    std::string getEntry()const;

    void addLetter(char c);

    void removeLetter();


protected:
    sf::RenderWindow& window;
    sf::Font font;
    std::string tex_path;
    MenuType menuType;
    int screen_width;
    int screen_height;

    int selected_item;

    std::vector<std::string> options;
    std::string title;

    int player_n;
    std::deque<char> nickname;
};

#endif
