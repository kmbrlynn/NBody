#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Body.hpp"

const int DEFAULT_WINDOW_SIZE = 912;
const double G = 6.76e-11;

int main(int argc, char* argv[])
{	
	double total_time = (double)std::atoi(argv[1]);
	double seconds_per_step = (double)std::atoi(argv[2]);
	
	int window_size;
	double universe_radius;
	int n_bodies;				 
	std::vector<Body*> bodies;

	sf::Texture background_image;
	sf::Sprite background;
	sf::Vector2u background_size;
	
	bool background_file_exists;

	// ============================================ if background image exists, load it
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
	
	// ========================================================== create bodies from file
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
	
	// ============================================================================= SFML
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

		for (int t = 0; t < total_time; t += seconds_per_step);
		{
			std::vector<Body*>::iterator it_i;
			for (it_i = bodies.begin(); it_i != bodies.end(); ++it_i)
			{
				std::vector<Body*>::iterator it_j;
				for (it_j = bodies.begin(); it_j != bodies.end(); ++it_j)
				{	
					double m1 = (**it_i).get_mass();
					double xvel = (**it_i).get_xvel();
					double yvel = (**it_i).get_yvel();
					
					if (*it_i != *it_j)
					{
						// calculate distance between This body and That body
						double delta_x = (**it_j).get_xpos() - (**it_i).get_xpos();
						double delta_y = (**it_j).get_ypos() - (**it_i).get_ypos();
						double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

						// calculate gravitational force between This and That
						double m2 = (**it_j).get_mass();
						double net_force = (G * m1 * m2) / (distance * distance);
						double x_force = net_force * (delta_x / distance);
						double y_force = net_force * (delta_y / distance);

						// calculate acceleration of This
						double x_accel = x_force / m1;
						double y_accel = y_force / m2;

						// calculate new velocity of This
						xvel = xvel + seconds_per_step * (x_force / delta_x);
						yvel = yvel + seconds_per_step * (y_force / delta_y);

						// add This's new velocity to current velocity
						(**it_i).set_xvel(seconds_per_step, xvel, x_accel);
						(**it_i).set_yvel(seconds_per_step, yvel, y_accel);	

						// print updated info for debugging
						std::cout << (**it_i).get_filename() << " - ";
						std::cout << (**it_j).get_filename() << " accel =\t";
						std::cout << x_accel << " | " << y_accel << std::endl;

						std::cout << (**it_i).get_filename() << " - ";
						std::cout << (**it_j).get_filename() << " force =\t";
						std::cout << x_force << " | " << y_force << std::endl;

						std::cout << (**it_i).get_filename() << " - ";
						std::cout << (**it_j).get_filename() << " delta =\t" ;
						std::cout << delta_x << " | " << delta_y << std::endl;
						std::cout << std::endl;
					}	

					// update position
					(**it_i).step(seconds_per_step);
					window.draw(**it_i);
				}
			}
		}

		window.display();
	}

	return 0;
}



