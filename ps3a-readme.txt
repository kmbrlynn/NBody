/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt
 **********************************************************************/

Name: Kim Douglas
OS: Ubuntu 14.1 (native)
Machine (e.g., Dell Latitude, MacBook Pro): Clevo/System76
Text editor: Vim
Hours to complete assignment (optional): not sure

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.

My Body class has a single constructor, which takes two parameters - 
the universe radius, and the window size, each determined in the 
initialization line. 

Then, it calls the overloaded std::cin, which reads the xpos, ypos, 
xvel, yvel, mass, and filename from the planets file - then 
initializes its Sprite and Texture member variables with this data. 

It also calls a function that scales the universe down to the 
window size. 

Here is my constructor:

 	Body::Body(double univ_radius, int window_size) : _radius(univ_radius), _size(window_size)
	{
		// _xpos, _ypos, _xvel, _yvel, _mass, _filename
		std::cin >> *this;

		meters_to_pixels();

		_texture.loadFromFile(_filename);
		_sprite.setTexture(_texture);
		_sprite.setPosition(sf::Vector2f(_xpos, _ypos));
	}

In my NBody.cpp file, I created a vector of pointers to Body
objects, and pushed new Bodies to this vector in a loop, like so:

	int n_bodies;				 
	std::vector<Body*> bodies;
	std::cin >> n_bodies;
	std::cin >> universe_radius;

	for (int i = 0; i < n_bodies; ++i)
	{	
		bodies.push_back(new Body(universe_radius, window_size));

		std::cout.precision(4);
		std::cout << std::scientific << *bodies[i] << std::endl;
	}

I overrode the draw function like so:

	void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

And in NBody.cpp, I called this:

	std::vector<Body*>::iterator it;
	for(it = bodies.begin(); it != bodies.end(); ++it)
	{
		window.draw(**it);
	}

 **********************************************************************/


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/

Originally, I created a vector of Bodies instead of a vector of pointers
to Bodies. I could not figure out why my draw loop had no problem 
drawing a standalone Body, but if it iterated through a vector of 
bodies, nothing showed up on screen. It compiled either way.

After much wrestling with it, I remembered Fred's advice that we should
make a vector of pointers as opposed to a vector of objects themselves... 
sure enough, that fixed everything. 

However, before that happened, Kyle and I talked for a while about my
problem, and he thought it might've been and issue with how I set up my 
constructor. In the end, that wasn't the issue at all, but it was good 
to talk to him becuase it made me think more critically about why I 
chose to set up my constructor the way I did. 

So talking things out with him made me have a better understanding of
my decisions, I guess.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

See above.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

I added some exception handling that loads the starfield.jpg background
image if it's available, and just draws a black background if it's not.

