#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Body.hpp"

const int DEFAULT_WINDOW_SIZE = 512;

int main(int argc, char* argv[])
{	
	int window_size;
	double universe_radius;
	int n_bodies;				 
	std::vector<Body*> bodies;

	sf::Texture background_image;
	sf::Sprite background;
	sf::Vector2u background_size;
	
	bool background_file_exists;

	// =============================================== if background image exists, load it
	try
	{
		background_image.loadFromFile("starfield.jpg");
		background.setTexture(background_image);
		
		background_file_exists = true;
		background_size = background_image.getSize();
		window_size = (int)background_size.x;

		if (!background_image.loadFromFile("starfield.jpg"))
			throw CannotLoadBackgroundImage();		
	}
	catch (CannotLoadBackgroundImage e)
	{
		std::cout << std::endl << "Cannot find solar system background image.";
		std::cout << std::endl << "Background will default to black.";
		std::cout << std::endl;
			
		background_file_exists = false;
		window_size = DEFAULT_WINDOW_SIZE;
	}
	
	// =========================================================== create bodies from file
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

	// ============================================================================== SFML
	sf::RenderWindow window(sf::VideoMode(window_size, window_size), "N-Body Simulation");
	window.setPosition(sf::Vector2i(200, 50));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (background_file_exists)
			window.draw(background);
		else
			window.clear(sf::Color::Black);

		std::vector<Body*>::iterator it;
		for(it = bodies.begin(); it != bodies.end(); ++it)
		{
			window.draw(**it);
		}
	
		window.display();
	}

	return 0;
}



