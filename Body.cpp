#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <cmath>
#include <iostream>



// ================================================================= con/destructors
Body::Body(double univ_radius, int window_size) :
		   _radius(univ_radius), _size(window_size)
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	std::cin >> *this;

	meters_to_pixels();

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);
	_sprite.setPosition(sf::Vector2f(_xpos, _ypos));

	//_num_bodies++;
}

Body::~Body()
{
	//_num_bodies--;
}

// ======================================================================= accessors
const double Body::get_mass()
{
	return _mass;
}

const double Body::get_xpos()
{
	return _xpos;
}

const double Body::get_ypos()
{
	return _ypos;
}

const double Body::get_xvel()
{
	return _xvel;
}

const double Body::get_yvel()
{
	return _yvel;
}

// ======================================================================== mutators
void Body::set_xpos(double seconds, double veloc)
{
	_xpos = _xpos + (seconds * veloc);
}

void Body::set_ypos(double seconds, double veloc)
{
	_ypos = _ypos + (seconds * veloc);
}

void Body::set_xvel(double seconds, double accel)
{
	_xvel = _xvel + (seconds * accel);
}

void Body::set_yvel(double seconds, double accel)
{
	_yvel = _yvel + (seconds * accel);
}

// ================================================================= calculate force
const sf::Vector2f Body::force(Body& body2)
{
	// gravitational constant
	double G = 6.67e-11;

	// get the masses of the two bodies
	double m1 = _mass;
	double m2 = body2.get_mass();

	// get distance between them
	double delta_x = _xpos - body2.get_xpos();
	double delta_y = _ypos - body2.get_ypos();		
	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

	// calculate the gravitational attraction of x and y components
	double F = (G * m1 * m2) / (distance * distance); 	
	double xF = F * (delta_x / distance);
	double yF = F * (delta_y / distance);
	
	sf::Vector2f force(xF, yF);
	return force;
}

// ============================================================================ step
void Body::step(double seconds, std::vector<Body*> bodies)
{
	std::vector<Body*>::iterator it;
	for (it = bodies.begin(); it != bodies.end(); ++it)
	{
		// determine force between 2 bodies
		sf::Vector2f F = force(**it);
		
		// determine their accelerations
		double body1_accel_x = F.x / _mass;
		double body1_accel_y = F.y / _mass;	
	//	double body2_accel_x = F.x / (**it).get_mass();
	//	double body2_accel_y = F.y / (**it).get_mass();
	
		// update their velocities
		this-> set_xvel(seconds, body1_accel_x);
		this-> set_yvel(seconds, body1_accel_y);
	//	(**it).set_xvel(seconds, body2_accel_x);
	//	(**it).set_xvel(seconds, body2_accel_y);

		// update their positions
		this-> set_xpos(seconds, _xvel);
		this-> set_ypos(seconds, _yvel);
	//	(**it).set_xpos(seconds, (**it).get_xvel());
	//	(**it).set_xpos(seconds, (**it).get_yvel());


	}
}

// ======================================================== scale universe to window
void Body::meters_to_pixels()
{
	// determine meters per pixel
	double univ_size = _radius * 2;
	double meters_per_pixel = univ_size / _size;

	// scale down the x and y positions
	_xpos = _xpos / meters_per_pixel;
	_ypos = _ypos / meters_per_pixel;

	// set an origin in center of window
	double _xorigin = _size / 2;
	double _yorigin = _size / 2;

	// shift from upper left corner to new origin
	_xpos += _xorigin;
	_ypos += _yorigin;

}

// ====================================================================== overridden
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
target.draw(_sprite, states);
	
}

std::istream& operator >>(std::istream& in_stream, Body& body)
{
	in_stream >> body._xpos;
	in_stream >> body._ypos;
	in_stream >> body._xvel;
	in_stream >> body._yvel;
	in_stream >> body._mass;
	in_stream >> body._filename;

	return in_stream;
}

std::ostream& operator <<(std::ostream& out_stream, const Body& body)
{
	out_stream << " " << body._xpos << " ";
	out_stream << " " << body._ypos << " ";
	out_stream << " " << body._xvel << " ";
	out_stream << " " << body._yvel << " ";
	out_stream << " " << body._mass << " ";
	out_stream << " " << body._filename << " ";

	return out_stream;
}

