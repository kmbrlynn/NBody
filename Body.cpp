#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <iostream>

// ================================================================= con/destructors
Body::Body(double univ_radius, int window_size) :
		   _radius(univ_radius), _size(window_size)
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	// ERROR CHECK THIS
	std::cin >> *this;

	universe_to_window();

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);
	_sprite.setPosition(sf::Vector2f(_xpos, _ypos));
}

Body::~Body()
{}

// ============================================================ accessors / mutators
void Body::universe_to_window()
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

