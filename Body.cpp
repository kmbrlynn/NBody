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
	_num_bodies++;
}

Body::~Body()
{}

// ======================================================================= accessors
const double Body::get_xpos()
{
	return _xpos;
}

const double Body::get_ypos()
{
	return _ypos;
}

const double Body::get_mass()
{
	return _mass;
}

// ======================================================================== mutators
void Body::set_xvel()
{
	// calculate this at time t given the current net force
}

void Body::set_yvel()
{


}

void Body::step(double seconds, std::vector<Body*> bodies)	//call this in main, on Sun probably
{
	// F = force of gravitational attraction between two bodies
	// xF = force of attraction for their x
	// yF = force of attraction for their y component
	// G = gravitational constant, 6.67e-11

	// F = (G * mass1 * mass2) / (square of their distance) 
	// xF = (G * mass1 * mass2) / (square of their distance) * (
	

	// gravitational constant
	double G = 6.67e-11;


	std::vector<Body*>::iterator it;
	for (it = bodies.begin(); it != bodies.end(); ++it)
	{
		// get the masses of the two bodies
		double m1 = _mass;
		double m2 = (**it).get_mass();

		// get distance between them
		double delta_x = _xpos - (**it).get_xpos();
		double delta_y = _ypos - (**it).get_ypos();		
		double r = sqrt( (delta_x*delta_x) +(delta_y*delta_y) );

		double F = (G * m1 * m2) / (r*r); 	

	}



	/* for each item in vector<Body>, 

	 get net force between this body and current body, update both accordingly
	 Force units = Newtons = (kilograms * meters) / seconds^2
	double
	

	 	get acceleration of this body and current body, update both accordingly



	*/

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

