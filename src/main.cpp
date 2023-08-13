#include <Windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "overlay.hpp"


int main(void) {

    sf::RenderWindow window = OVERLAY::InitWindow();
    
    OVERLAY::ConfigWindow(window);
    
    return 0;
}
