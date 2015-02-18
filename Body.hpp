#include <SFML/Graphics.hpp>

class Usage
{};

class Body: public sf::Drawable
{
public:

	Body(double, double, double, double, double, std::string);
	Body();
	~Body();

	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double _xpos;
	double _ypos;
	
	double _xvel;
	double _yvel;
	
	double _mass;
	std::string _filename;

	sf::Sprite _sprite;
	sf::Texture _texture;


};








