#include <SFML/Graphics.hpp>

class CannotLoadBackgroundImage
{};

class Body: public sf::Drawable
{
public:
	
	// ======================================================= con / destructors
	Body(double, int);
	~Body();

	// =============================================================== accessors
	double get_mass() const;
	double get_xpos() const;
	double get_ypos() const;

	// ================================================================ mutators
	void set_xvel(double, double);
	void set_yvel(double, double);
	void step(double);

	// ========================================================== overloaded i/o
	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:
	
	// sfml's abstract sf::Drawable class is private
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static int _body_count;
	double _radius;			
	int _size;				

	double _mass;
	double _xpos;
	double _ypos;	

	double _xvel;
	double _yvel;
	
	std::string _filename;
	sf::Sprite _sprite;
	sf::Texture _texture;

};








