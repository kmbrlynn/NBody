#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
//#include <sstream>
#include "Body.hpp"

int main(int argc, char* argv[])
{
	int n_bodies;				 
	double universe_radius;	
	
	double xpos, ypos, xvel, yvel, mass;
	std::string filename;

	std::vector<Body> bodies;

	std::cin >> n_bodies;
	std::cout << std::endl << "Number of bodies: " << n_bodies << std::endl;
	std::cin >> universe_radius;
	std::cout << "Universe radius: " << universe_radius << std::endl;
	std::cout << std::endl;
	std::cout << " ...xpos...  ...ypos...  ...xvel...  ...yvel...  ...mass...  filename";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < n_bodies; ++i)
	{	
		// CHANGE THIS LATER
		// overload istream for whole line instead of doing it value by value
		std::cin >> xpos >>	ypos >> xvel >> yvel >> mass >> filename;
		
		// construct a body
		bodies.push_back(Body(xpos, ypos, xvel, yvel, mass, filename));
		
		// give its sprite a texture
		bodies.back().set_texture(filename);

		// set its initial position
		bodies.back().get_sprite().setPosition(xpos, ypos);
		
		// print info to console
		std::cout.precision(4);
		std::cout << std::scientific << bodies[i] << std::endl;
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

		for (int i = 0; i < n_bodies; ++i)
		{
		//	window.draw(i
			
		}

		window.display();
	}

	return 0;
}


