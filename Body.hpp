#include <SFML/Graphics.hpp>

class CannotLoadBackgroundImage
{};

class Body: public sf::Drawable
{
public:
	
	// ======================================================= con / destructors
	Body(double, int);
	~Body();

	// ==================================================== accessors / mutators
	const double get_mass();
	const double get_xpos();
	const double get_ypos();

	// for debugging
	const std::string get_filename();

	void set_xvel(double, Body*);
	void set_yvel(double, Body*);

	// =============================================== force & step calculations
	const sf::Vector2f force(Body*);
	void step(double, std::vector<Body*>);

	// ========================================================== overloaded i/o
	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:

	// scale the universe to the window size. occurs in constructor
	void meters_to_pixels();

	// sfml's abstract sf::Drawable class is private
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double _radius;	// millions of meters in the universe
	int _size;		// hundreds of pixels in the window

	double _xpos;
	double _ypos;	

	double _xvel;
	double _yvel;
	
	double _mass;
	std::string _filename;

	sf::Sprite _sprite;
	sf::Texture _texture;

};








