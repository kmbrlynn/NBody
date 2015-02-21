#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Body.hpp"

int main(int argc, char* argv[])
{
	sf::Texture starfield;
	starfield.loadFromFile("starfield.jpg");
	
	if (!starfield.loadFromFile("starfield.jpg"))
	{
		std::cout << std::endl << "Cannot find solar system background image.";
		std::cout << std::endl << "Aborting program." << std::endl << std::endl;
		return -1;
	}
	
	sf::Vector2u size_starfield = starfield.getSize();

	int window_size = (int)size_starfield.x;
	double universe_radius;

	int n_bodies;				 
	std::vector<Body*> bodies;

	std::cin >> n_bodies;
	std::cout << std::endl << "Number of bodies: " << n_bodies << std::endl;
	std::cin >> universe_radius;
	std::cout << "Universe radius: " << universe_radius << std::endl;
	std::cout << std::endl;
	std::cout << " ...xpos...  ...ypos...  ...xvel...  ...yvel...  ...mass...  filename";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < n_bodies; ++i)
	{	
		bodies.push_back(new Body(universe_radius, window_size));

		std::cout.precision(4);
		std::cout << std::scientific << *bodies[i] << std::endl;
	}

	// ======================================================================== SFML

	sf::RenderWindow window(sf::VideoMode(window_size, window_size), "N-Body Simulation");
	window.setPosition(sf::Vector2i(200, 50));

	sf::Sprite background;
	background.setTexture(starfield);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);

		std::vector<Body*>::iterator it;
		for(it = bodies.begin(); it != bodies.end(); ++it)
		{
			window.draw(**it);
		}
	
		window.display();
	}

	return 0;
}



