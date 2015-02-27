#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <iostream>

// gravitational constant
const double G = 6.67e-11;

int Body::_body_count = 0;

// ================================================================= con/destructors
Body::Body(double univ_radius, int window_size) :
		   _radius(univ_radius), _size(window_size)
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	std::cin >> *this;

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);

	_body_count++;
}

Body::~Body()
{
	_body_count--;
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

// ======================================================================== mutators
void Body::set_xvel(double seconds, double accel)
{	
	_xvel = _xvel + (seconds * accel);
}

void Body::set_yvel(double seconds, double accel)
{
	_yvel = _yvel - (seconds * accel);
}

void Body::step(double seconds)
{
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


