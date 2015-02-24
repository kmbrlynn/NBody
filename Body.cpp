#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <cmath>
#include <iostream>

// gravitational constant
const double G = 6.67e-11;

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
}

Body::~Body()
{}

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

// ======================================================================== mutators
void Body::set_xvel(double seconds, Body body2)
{
	sf::Vector2f F = force(body2);
	double accel = F.x / _mass;
	
	_xvel = _xvel + (seconds * accel);
}

void Body::set_yvel(double seconds, Body body2)
{
	sf::Vector2f F = force(body2);
	double accel = F.y / _mass;

	_yvel = _yvel + (seconds * accel);
}

// ================================================================= calculate force
const sf::Vector2f Body::force(Body body2)
{
	// get the masses of the two bodies
	double m1 = _mass;
	double m2 = body2.get_mass();

	// calculate distance between them
	double delta_x = _xpos - body2.get_xpos();
	double delta_y = _ypos - body2.get_ypos();		
	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

	// calculate the gravitational attraction of x and y components
	double net_force = (G * m1 * m2) / (distance * distance); 	
	double x_force = net_force * (delta_x / distance);
	double y_force = net_force * (delta_y / distance);
	
	sf::Vector2f force(x_force, y_force);
	return force;
}

// ============================================================================ step
void Body::step(double seconds, std::vector<Body*> bodies)
{
	std::vector<Body*>::iterator it;
	for (it = bodies.begin(); it != bodies.end(); ++it)
	{
		// update velocities and positions
		set_xvel(seconds, (**it));
		set_yvel(seconds, (**it));
		_xpos = _xpos + (seconds * _xvel);
		_ypos = _ypos + (seconds * _yvel);

		// assign new position to sprite
		_sprite.setPosition(sf::Vector2f(_xpos, _ypos));
	}
}

// ======================================================== scale universe to window
void Body::meters_to_pixels()
{
	// determine meters per pixel
	double univ_size = _radius * 2;
	double meters_per_pixel = univ_size / _size;

	// set an origin in center of window
	double x_origin = _size / 2;
	double y_origin = _size / 2;

	// scale down the x and y positions
	_xpos = _xpos / meters_per_pixel;
	_ypos = _ypos / meters_per_pixel;

	// shift from upper left corner to new origin
	_xpos += x_origin;
	_ypos += y_origin;
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
	// reverse meters-to-pixels
	double univ_size = body._radius * 2;
	double meters_per_pixel = univ_size / body._size;
	double xpos = body._xpos - (body._size / 2);
	double ypos = body._ypos - (body._size / 2);

	// scale x and y positions back up for printing
	xpos = xpos * meters_per_pixel;
	ypos = ypos * meters_per_pixel;

	out_stream << " " << xpos << " ";
	out_stream << " " << ypos << " ";
	out_stream << " " << body._xvel << " ";
	out_stream << " " << body._yvel << " ";
	out_stream << " " << body._mass << " ";
	out_stream << " " << body._filename << " ";

	return out_stream;
}

