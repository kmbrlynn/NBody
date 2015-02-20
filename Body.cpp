#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <iostream>

// ================================================================= con/destructors
Body::Body(double univ_radius, int window_size) :
		   _radius(univ_radius), _size(window_size)
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	std::cin >> *this;

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);

	_sprite.setPosition(sf::Vector2f(_xpos, _ypos));
}

Body::~Body()
{}

// ============================================================ accessors / mutators
sf::Sprite Body::get_sprite()
{
	return _sprite;
}

// ======================================================= convert universe / window
void Body::polar_to_cartesian()
{
	// create a cartesian origin in center of window
//	double cartesian_origin_x = _size / 2;
//	double cartesian_origin_y = _size / 2;

	// s

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

