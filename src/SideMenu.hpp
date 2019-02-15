#ifndef SIDEMENU_HPP
#define SIDEMENU_HPP

#include "configs.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <set>
#include <exception>
#include <memory>
#include <list>
#include "Player.hpp"

class SideMenu{

public:
    SideMenu(sf::RenderWindow& window, const std::string& path);
    ~SideMenu();

protected:

    sf::RenderWindow& window;

};

#endif
