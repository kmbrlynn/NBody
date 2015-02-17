#include <SFML/Graphics.hpp>

class Usage
{};

class Body : public sf::Drawable
{
public:

	friend std::ostream& operator <<(std::ostream&, const Body&);
	friend std::istream& operator >>(std::istream&, Body&);

private:

	void draw(sf::RenderTarget&, sf::RenderStates) const;

	double _xpos;
	double _ypos;
	
	double _xveloc;
	double _yveloc;
	
	double _mass;
	std::string _filename;



};









































