#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <cmath>
#include <iostream>

// gravitational constant
const double G = 6.67e-11;

int Body::_body_id = 0;

// ================================================================= con/destructors
Body::Body(double univ_radius, int window_size) :
		   _radius(univ_radius), _size(window_size)
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	std::cin >> *this;

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);

	_body_id++;
}

Body::~Body()
{
	_body_id--;
}

// ======================================================================= accessors
double Body::get_mass() const
{
	return _mass;
}

double Body::get_xpos() const
{
	return _xpos;
}

double Body::get_ypos() const
{
	return _ypos;
}

double Body::get_xvel() const
{
	return _xvel;
}

double Body::get_yvel() const
{
	return _yvel;
}

std::string Body::get_filename() const
{
	return _filename;
}

// ======================================================================== mutators
/*void Body::set_xaccel(sf::Vector2f force)
{
	_xaccel = force.x / _mass;
}

void Body::set_yaccel(sf::Vector2f force)
{
	_yaccel = force.y / _mass;
}
*/
void Body::set_xvel(double seconds, double xvel, double accel)
{	
	_xvel = xvel + (seconds * accel);
}

void Body::set_yvel(double seconds, double yvel, double accel)
{
	_yvel = yvel - (seconds * accel);
}

/*
// ================================================================= calculate force
sf::Vector2f Body::force(const Body& body2)
{
	// get the masses of the two bodies
	double m1 = _mass;
	double m2 = body2.get_mass();

	// calculate distance between them
	double delta_x = (body2.get_xpos() - _xpos);
	double delta_y = (body2.get_ypos() - _ypos);		
	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );

	// calculate the gravitational attraction of x and y components
	double net_force = (G * m1 * m2) / (distance * distance); 	
	double x_force = net_force * (delta_x / distance);
	double y_force = net_force * (delta_y / distance);
	
	sf::Vector2f force(x_force, y_force);
	return force;
}
*/

// ============================================================================ step
void Body::step(double seconds)
{
/*	// calculate acceleration in each component
	_xaccel = F.x / _mass;
	_yaccel = F.y / _mass;

	// calculate velocities
	_xvel = _xvel + (seconds * _xaccel);
	_yvel = _yvel - (seconds * _yaccel);
*/
	// set new position
	_xpos = _xpos + (seconds * _xvel);
	_ypos = _ypos - (seconds * _yvel);
}

// ====================================================================== overridden
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// scale universe down to window
	double meters_per_pixel = (_radius * 2) / _size;
	double xorigin = _size / 2;
	double yorigin = _size / 2;

	// scale down the x and y positions
	double xpos = _xpos / meters_per_pixel;
	double ypos = _ypos / meters_per_pixel;

	// shift from upper left corner to center
	xpos += xorigin;
	ypos += yorigin;

	sf::Sprite sprite = _sprite;
	sprite.setPosition(sf::Vector2f(xpos, ypos));
	target.draw(sprite);	
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


