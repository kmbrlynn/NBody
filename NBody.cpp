#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Body.hpp"

const int SIZE = 800;

int main(int argc, char* argv[])
{
	double universe_radius;
	int window_size = SIZE;

	int n_bodies;				 
	std::vector<Body> bodies;

	std::cin >> n_bodies;
	std::cout << std::endl << "Number of bodies: " << n_bodies << std::endl;
	std::cin >> universe_radius;
	std::cout << "Universe radius: " << universe_radius << std::endl;
	std::cout << std::endl;
	std::cout << " ...xpos...  ...ypos...  ...xvel...  ...yvel...  ...mass...  filename";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < n_bodies-3; ++i)
	{	
		Body body(universe_radius, window_size);
		bodies.push_back(body);

		std::cout.precision(4);
		std::cout << std::scientific << bodies[i] << std::endl;
	}

//	std::cout << std::endl << bodies[2] << std::endl;

	// ======================================================================== SFML

	sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "N-Body Simulation");
	window.setPosition(sf::Vector2i(200, 50));

	Body testBody(universe_radius, window_size);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

/*		std::vector<Body>::iterator it;
		for(it = bodies.begin(); it != bodies.end(); ++it)
		{
			window.draw(*it);
		}
*/	

		window.draw(testBody);

/*		for(unsigned int i = 0; i < bodies.size(); i++)
		{
			window.draw(bodies.at(i));
		}
*/
		window.display();
	}

	return 0;
}













