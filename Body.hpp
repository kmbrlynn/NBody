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
	double get_mass() const;
	double get_xpos() const;
	double get_ypos() const;

	// for debugging
	std::string get_filename() const;

/*	void set_xaccel(sf::Vector2f);
	void set_yaccel(sf::Vector2f);
	void set_xvel(double);
	void set_yvel(double);
*/	void update_sprite_position();

	// =============================================== force & step calculations
	sf::Vector2f force(const Body&);
	void step(double, sf::Vector2f);

	// ========================================================== overloaded i/o
	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:
	// sfml's abstract sf::Drawable class is private
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double _radius;			
	int _size;				
	double _meters_per_pixel;
	double _xorigin;
	double _yorigin;

	double _xpos;
	double _ypos;	

	double _xaccel;
	double _yaccel;

	double _xvel;
	double _yvel;
	
	double _mass;
	std::string _filename;

	sf::Sprite _sprite;
	sf::Texture _texture;

};








