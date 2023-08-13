#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <dwmapi.h>
#include <functional>


namespace OVERLAY {
	extern const char* WINDOW_NAME;
	extern const unsigned int FRAMERATE_LIMIT;
	extern const char* TARGET_WINDOW_NAME;

    struct _POS {
        LONG R; // right
        LONG L; // left
        LONG T; // top
        LONG B; // bottom
    };

	typedef _POS POS;
	
	void EVENTLOOP(sf::RenderWindow& window) noexcept;

    void GetWindowPosition(POS* dms, HWND hProcess) noexcept;
	sf::RenderWindow InitWindow(void) noexcept;
	void ConfigWindow(sf::RenderWindow& window);
}