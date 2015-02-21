#include <SFML/Graphics.hpp>

class Body: public sf::Drawable
{
public:

	// ==================================================== con / destructors
	Body(double, int);
	~Body();

	// ================================================= accessors / mutators


	// ====================================================== overloaded i/o
	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:

	// meters to pixels conversion occurs in constructor
	void universe_to_window();

	// sfml's abstract sf::Drawable class is private
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double _radius;	// millions of meters
	int _size;		// hundreds of pixels

	double _xpos;
	double _ypos;	

	double _xvel;
	double _yvel;
	
	double _mass;
	std::string _filename;

	sf::Sprite _sprite;
	sf::Texture _texture;

};








