#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include "Body.hpp"

int main(int argc, char* argv[]) // read time and delta_time
{
	std::string data;
	
	int n_bodies;				// N 
	double universe_radius;		// R
	double time;				// T - argv[1]
	double delta_time;			// t - argv[2]
	
	std::getline(std::cin, data);
	std::istringstream(data) >> n_bodies;	
	std::getline(std::cin, data);
	std::istringstream(data) >> universe_radius;
	std::istringstream(argv[1]) >> time;
	std::istringstream(argv[2]) >> delta_time;

	std::cout << "Number of bodies: " << n_bodies << std::endl;
	std::cout << "Universe radius: " << universe_radius << std::endl;


	// ======================================================================== SFML

	sf::RenderWindow window(sf::VideoMode(800, 800), "N-Body Simulation");
	window.setPosition(sf::Vector2i(200, 50));

	while (window.isOpen())
	{
		sf::Event event;

		// Create instances of Body for each planet
	//	Body sun;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
	//	window.draw(sun);
		window.display();
	}

	return 0;
}


