#include <SFML/Graphics.hpp>
#include "Body.hpp"
#include <iostream>

Body::Body(double xpos, double ypos, double xvel, double yvel, 
	       double mass, std::string filename) :
						_xpos(xpos), _ypos(ypos), _xvel(xvel), _yvel(yvel), 
						_mass(mass), _filename(filename)
{}

Body::Body()
{}

Body::~Body()
{}

// =============================================================== getters & setters
void Body::set_texture(std::string texture_name)
{
	_texture.loadFromFile(texture_name);
	_sprite.setTexture(_texture);
}

void Body::set_xpos(double xpos)
{

}

void Body::set_ypos(double ypos)
{

}

double Body::get_xpos()
{
	return _xpos;
}

double Body::get_ypos()
{
	return _ypos;
}

// ====================================================================== overridden
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{


}

std::istream& operator >>(std::istream& in_stream, Body& body)
{	
/*	in_stream >> body._xpos;
	in_stream >> body._ypos;
	in_stream >> body._xvel;
	in_stream >> body._yvel;
	in_stream >> body._mass;
	in_stream >> body._filename;
*/
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


