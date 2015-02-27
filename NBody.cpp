#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Body.hpp"

const int DEFAULT_WINDOW_SIZE = 512;
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
		background_image.loadFromFile("nbody/starfield.jpg");
		background.setTexture(background_image);
		
		background_file_exists = true;
		background_size = background_image.getSize();
		window_size = (int)background_size.x;

		if (!background_image.loadFromFile("nbody/starfield.jpg"))
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
	std::cout << std::endl << std::endl <<  "INITIAL STATE OF UNIVERSE:" << std::endl;
	std::cin >> n_bodies;
	std::cout << "Number of bodies: " << n_bodies << std::endl;
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

	sf::SoundBuffer buffer;
	buffer.loadFromFile("nbody/2001.ogg");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	sf::Font font;
	font.loadFromFile("Ubuntu-Light.ttf");
	int sec = 0;
	int min = 0;
	int days = 0;
	int weeks = 0;
	int years = 0;

	sf::Text title_time_seconds("Seconds: ", font);
	title_time_seconds.setPosition(10, 0);
	title_time_seconds.setCharacterSize(18);
	sf::Text time_seconds;
	time_seconds.setFont(font);
	time_seconds.setPosition(window_size*0.25, 0);
	time_seconds.setCharacterSize(18);

	sf::Text title_time_minutes("Minutes: ", font);
	title_time_minutes.setPosition(10, 20);
	title_time_minutes.setCharacterSize(18);
	sf::Text time_minutes;
	time_minutes.setFont(font);
	time_minutes.setPosition(window_size*0.25, 20);
	time_minutes.setCharacterSize(18);

	sf::Text title_time_days("Days: ", font);
	title_time_days.setPosition(10, 40);
	title_time_days.setCharacterSize(18);
	sf::Text time_days;
	time_days.setFont(font);
	time_days.setPosition(window_size*0.25, 40);
	time_days.setCharacterSize(18);
	
	sf::Text title_time_weeks("Weeks: ", font);
	title_time_weeks.setPosition(10, 60);
	title_time_weeks.setCharacterSize(18);
	sf::Text time_weeks;
	time_weeks.setFont(font);
	time_weeks.setPosition(window_size*0.25, 60);
	time_weeks.setCharacterSize(18);

	sf::Text title_time_years("Years: ", font);
	title_time_years.setPosition(10, 80);
	title_time_years.setCharacterSize(18);
	sf::Text time_years;
	time_years.setFont(font);
	time_years.setPosition(window_size*0.25, 80);
	time_years.setCharacterSize(18);
	
	for (sec = 0; sec < total_time; sec += seconds_per_step)
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

		// elapsed time
		std::ostringstream string_stream_sec;
		string_stream_sec << sec;
		std::string time_string_sec = string_stream_sec.str();
		time_seconds.setString(time_string_sec);

		min = sec / 60;
		std::ostringstream string_stream_minutes;
		string_stream_minutes << min;
		std::string time_string_minutes = string_stream_minutes.str();
		time_minutes.setString(time_string_minutes);
	
		days = min / 60 / 24;
		std::ostringstream string_stream_days;
		string_stream_days << days;
		std::string time_string_days = string_stream_days.str();
		time_days.setString(time_string_days);
	
		weeks = days / 7;
		std::ostringstream string_stream_weeks;
		string_stream_weeks << weeks;
		std::string time_string_weeks = string_stream_weeks.str();
		time_weeks.setString(time_string_weeks);
	
		years = weeks / 52;
		std::ostringstream string_stream_years;
		string_stream_years << years;
		std::string time_string_years = string_stream_years.str();
		time_years.setString(time_string_years);
			
		// This body
		std::vector<Body*>::iterator it_i;
		for (it_i = bodies.begin(); it_i != bodies.end(); ++it_i)
		{
			// maintain these values for all of the Thats
			double m1 = (**it_i).get_mass();	
			double x_force = 0;
			double y_force = 0;
			double x_accel;
			double y_accel;

			// That body
			std::vector<Body*>::iterator it_j;
			for (it_j = bodies.begin(); it_j != bodies.end(); ++it_j)
			{	
				if (*it_i != *it_j)
				{
					// calculate distance between This and That
					double delta_x = (**it_j).get_xpos() - (**it_i).get_xpos();
					double delta_y = (**it_j).get_ypos() - (**it_i).get_ypos();
					double distance = sqrt((delta_x * delta_x) + (delta_y * delta_y));

					// calculate gravitational force between This and That
					double m2 = (**it_j).get_mass();
					double net_force = (G * m1 * m2) / (distance * distance);
					x_force += net_force * (delta_x / distance);
					y_force += net_force * (delta_y / distance);

					// calculate acceleration of This
					x_accel = x_force / m1;
					y_accel = y_force / m1;
				}
			}	
			
			// update velocity of This
			(**it_i).set_xvel(seconds_per_step, x_accel);
			(**it_i).set_yvel(seconds_per_step, y_accel);	

			// update position of This, and display
			(**it_i).step(seconds_per_step);
			window.draw(**it_i);
			window.draw(title_time_seconds);
			window.draw(time_seconds);
			window.draw(title_time_minutes);
			window.draw(time_minutes);
			window.draw(title_time_days);
			window.draw(time_days);
			window.draw(title_time_weeks);
			window.draw(time_weeks);
			window.draw(title_time_years);
			window.draw(time_years);
		}

		window.display();
	}

	std::cout << std::endl << std::endl << "FINAL STATE OF UNIVERSE:" << std::endl;
	std::cout << "Number of bodies: " << n_bodies << std::endl;
	std::cout << "Universe radius: " << universe_radius << std::endl;
	std::cout << std::endl;
	std::cout << " ...xpos...  ...ypos...  ...xvel...  ...yvel...  ...mass...  filename";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < n_bodies; ++i)
	{	
		std::cout.precision(4);
		std::cout << std::scientific << *bodies[i] << std::endl;		
	}

	return 0;
}



