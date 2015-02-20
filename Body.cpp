#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <iostream>

// ================================================================= con/destructors
Body::Body()
{
	// _xpos, _ypos, _xvel, _yvel, _mass, _filename
	std::cin >> *this;
	// _texture, _sprite
	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);
}

Body::~Body()
{}

// ======================================================== position, velocity, mass
void Body::set_xvel(double xvel)
{
	// need a translation function
}

void Body::set_yvel(double yvel)
{
	// need a translation function
}

// ====================================================================== overridden
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{


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


