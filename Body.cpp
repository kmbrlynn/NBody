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

	_texture.loadFromFile(_filename);
	_sprite.setTexture(_texture);

	// scale universe down to window
	_meters_per_pixel = (_radius * 2) / _size;
	_xorigin = _size / 2;
	_yorigin = _size / 2;
	
//	_sprite.setPosition(sf::Vector2f(xpos, ypos));

//	update_sprite_position();
}

Body::~Body()
{}

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

std::string Body::get_filename() const
{
	return _filename;
}

// ======================================================================== mutators
void Body::set_xvel(double seconds, double acceleration)
{	
	_xvel = _xvel + (seconds * acceleration);
}

void Body::set_yvel(double seconds, double acceleration)
{
	_yvel = _yvel - (seconds * acceleration);
}

void Body::update_sprite_position()
{
	// scale down the x and y positions
	double xpos = _xpos / _meters_per_pixel;
	double ypos = _ypos / _meters_per_pixel;

	// shift from upper left corner to center
	xpos += _xorigin;
	ypos += _yorigin;

	_sprite.setPosition(sf::Vector2f(xpos, ypos));
	// may want to set a local center origin here
}

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

// ============================================================================ step
void Body::step(double seconds)
{
//	if (_filename == body2.get_filename())
//		return;	

	// calculate net force exerted on it from other body
//	sf::Vector2f F = force(body2);

	// calculate acceleration in each component
//	double accel_x = F.x / _mass;
//	double accel_y = F.y / _mass;

	// calculate velocities
//	set_xvel(seconds, accel_x);
//	set_yvel(seconds, accel_y);
//	_xvel = _xvel + (seconds * accel_x);
//	_yvel = _yvel - (seconds * accel_y);
	
	// set new position
	_xpos = _xpos + (seconds * _xvel);
	_ypos = _ypos - (seconds * _yvel);

	// assign new position to sprite
	// may want to put origin in center of image
//	update_sprite_position();
}

// ====================================================================== overridden
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// scale down the x and y positions
	double xpos = _xpos / _meters_per_pixel;
	double ypos = _ypos / _meters_per_pixel;

	// shift from upper left corner to center
	xpos += _xorigin;
	ypos += _yorigin;

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


