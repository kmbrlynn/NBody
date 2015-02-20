#include <SFML/Graphics.hpp>

class Usage
{};

class Body: public sf::Drawable
{
public:

	// ==================================================== con / destructors
	Body(double, int);
	~Body();

	// ================================================= accessors / mutators
	sf::Sprite get_sprite();

	// ====================================================== overloaded i/o
	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:
	
	void polar_to_cartesian();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double _radius;
	int _size;

	double _xpos;
	double _ypos;	

	double _xvel;
	double _yvel;
	
	double _mass;
	std::string _filename;

	sf::Sprite _sprite;
	sf::Texture _texture;

};








