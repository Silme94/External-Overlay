#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <dwmapi.h>
#include <functional>
#include "overlay.hpp"


namespace OVERLAY {

	extern const char* WINDOW_NAME = "Easy Overlay";
	extern const unsigned int FRAMERATE_LIMIT = 60;
	extern const char* TARGET_WINDOW_NAME = "AssaultCube";

	void GetWindowPosition(POS* dms, HWND hProcess) noexcept {
		RECT rect;

		GetWindowRect(hProcess, &rect);

		dms->R = rect.right;
		dms->L = rect.left;
		dms->T = rect.top;
		dms->B = rect.bottom;
	}


	sf::RenderWindow InitWindow(void) noexcept {
		return sf::RenderWindow(sf::VideoMode(200, 200), WINDOW_NAME, sf::Style::None);
	}

	void EVENTLOOP(sf::RenderWindow& window) noexcept {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	};


	void ConfigWindow(sf::RenderWindow& window) {
		window.setFramerateLimit(FRAMERATE_LIMIT);
		HWND target = FindWindowA(NULL, TARGET_WINDOW_NAME);
		if (target == NULL) {
			std::cout << "Window not found. Exiting.\n";
			exit(EXIT_FAILURE);
		}

		HWND syshandle = window.getSystemHandle();
		MARGINS margins;
		margins.cxLeftWidth = -1;

		DwmExtendFrameIntoClientArea(syshandle, &margins);
		SetWindowPos(syshandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
		SetWindowLong(syshandle, GWL_EXSTYLE, GetWindowLong(syshandle, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetLayeredWindowAttributes(syshandle, 0, 255, LWA_ALPHA);

		/*------------------MAIN LOOP------------------*/

		while (window.isOpen()) {
			
			EVENTLOOP(window);

			POS screen_pos;
			GetWindowPosition(&screen_pos, target);

			int width = screen_pos.R - screen_pos.L;
			int height = screen_pos.B - screen_pos.T;

			sf::Vector2i newPos;
			newPos.x = screen_pos.L;
			newPos.y = screen_pos.T;

			window.setPosition(newPos);
			window.setSize(sf::Vector2u(width, height));

			window.clear(sf::Color::Transparent);

			sf::RectangleShape rectangle(sf::Vector2f(100.0f, 50.0f));
			rectangle.setFillColor(sf::Color::Red);
			window.draw(rectangle);
			
			window.display();

			Sleep(100);

			// . . .
		}
	}
}
