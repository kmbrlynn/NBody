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

	update_sprite_position();
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

const std::string Body::get_filename()
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
	_yvel = _yvel + (seconds * acceleration);
}

void Body::update_sprite_position()
{
	// determine meters per pixel
	double univ_size = _radius * 2;
	double meters_per_pixel = univ_size / _size;
	double xpos = _xpos;
	double ypos = _ypos;
	
	// set an origin in center of window
	double x_origin = _size / 2;
	double y_origin = _size / 2;

	// scale down the x and y positions
	xpos = xpos / meters_per_pixel;
	ypos = ypos / meters_per_pixel;

	// shift from upper left corner to new origin
	xpos += x_origin;
	ypos += y_origin;

	_sprite.setPosition(sf::Vector2f(xpos, ypos));
	// may want to set a local center origin here
}

// ================================================================= calculate force
const sf::Vector2f Body::force(Body& body2)
{
	// get the masses of the two bodies
	double m1 = _mass;
	double m2 = body2.get_mass();

	// calculate distance between them
	double delta_x = abs(body2.get_xpos() - _xpos);
	double delta_y = abs(body2.get_ypos() - _ypos);		
	double distance = sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
/*
std::cout << std::endl;
std::cout << "Distance between " << _filename << " and " << body2.get_filename();
std::cout << " = " << distance << std::endl;
*/
	// calculate the gravitational attraction of x and y components
	double net_force = (G * m1 * m2) / (distance * distance); 	
	double x_force = net_force * (delta_x / distance);
	double y_force = net_force * (delta_y / distance);
	
	sf::Vector2f force(x_force, y_force);
	return force;
}

// ============================================================================ step
void Body::step(double seconds, Body& body2)
{
	if (_filename == body2.get_filename())
		return;	

	// calculate net force exerted on it from other body
	sf::Vector2f F = force(body2);

	// calculate acceleration in each component
	double accel_x = F.x / _mass;
	double accel_y = F.y / _mass;

	// calculate velocities
	set_xvel(seconds, accel_x);
	set_yvel(seconds, accel_y);
	
	// set new position
	_xpos = _xpos + (seconds * _xvel);
	_ypos = _ypos + (seconds * _yvel);
/*
std::cout << "new xpos of " << _filename << " = " << _xpos << std::endl;
std::cout << "new ypos of " << _filename << " = " << _ypos << std::endl;
*/
	// assign new position to sprite
	// may want to put origin in center of image
	update_sprite_position();

/*
std::cout << "x-force between " << _filename << " and " << body2.get_filename();
std::cout << " = " << F.x << std::endl;
std::cout << "y-force between " << _filename << " and " << body2.get_filename();
std::cout << " = " << F.y << std::endl;
*/

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


/*
std::cout << "delta_x = " << delta_x << std::endl;
std::cout << "delta_y = " << delta_y << std::endl;		
std::cout << "distance from " << _filename << " to ";
std::cout << body2-> get_filename() << " = " << distance << std::endl;


std::cout << "x force on " << _filename << " from " << body2-> get_filename();
std::cout << " = " << x_force << std::endl;
std::cout << "y force on " << _filename << " from " << body2-> get_filename();
std::cout << " = " << y_force << std::endl << std::endl;








*/
