#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
//#include <sstream>
#include "Body.hpp"

const int TIME_ARG = 1;
const int DELTA_TIME_ARG = 2;

int main(int argc, char* argv[])
{
	int n_bodies;				 
	double universe_radius;	
	std::vector<Body> solar_system;
	double xpos, ypos, xvel, yvel, mass;
	std::string filename;

	std::cin >> n_bodies;
	std::cout << std::endl << "Number of bodies: " << n_bodies << std::endl;
	std::cin >> universe_radius;
	std::cout << "Universe radius: " << universe_radius << std::endl;
	std::cout << std::endl;
	std::cout << " ...xpos... ...ypos... ...xvel... ...yvel... ...mass... filename";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < n_bodies; ++i)
	{
		std::cin >> xpos >>	ypos >> xvel >> yvel >> mass;
		std::cin >> filename;
		
		solar_system.push_back(Body(xpos, ypos, xvel, yvel, mass, filename));
		
		std::cout.precision(4);
		std::cout << std::scientific << solar_system[i] << std::endl;
	}

	// ======================================================================== SFML

	sf::RenderWindow window(sf::VideoMode(800, 800), "N-Body Simulation");
	window.setPosition(sf::Vector2i(200, 50));

	while (window.isOpen())
	{
		sf::Event event;

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


