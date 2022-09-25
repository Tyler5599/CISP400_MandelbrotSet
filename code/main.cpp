#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	//variables
	float aspect, width, height;
	//calculating aspect ratio by dividing or values that were rturned from get width and height functions
	width =	VideoMode::getDesktopMode().width;
	height = VideoMode::getDesktopMode().height;
	aspect = height / width;

	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Mandelbrot!!!", Style::Default);
	ComplexPlane plane1(aspect);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	sf::Text text1;
	text1.setFont(font);
	text1.setCharacterSize(30);
	text1.setStyle(sf::Text::Regular);
	VertexArray ourArray(Points,width*height);
	enum class States
	{
		CALCULATING, DISPLAYING
	};
	States::CALCULATING;
	while (window.isOpen())
	{
		//Process events
			sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//close is esc key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//close is esc key is pressed
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f points(Mouse::getPosition().x, Mouse::getPosition().y);
			plane1.setCenter(points);
			plane1.zoomIn();
			States::CALCULATING;
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			Vector2f points(Mouse::getPosition().x, Mouse::getPosition().y);
			plane1.setCenter(points);
			plane1.zoomOut();
			States::CALCULATING;
		}
		/*Handle Event::MouseMovedUse mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View that corresponds to the screen mouse location
		setMouseLocation on the ComplexPlane object to store this coordinate This will be used later to display the mouse coordinates as it moves*/
		if(event.MouseMoved)
		{
			Vector2f points(Mouse::getPosition().x, Mouse::getPosition().y);
			plane1.setMouseLocation(points);
		}
		if (States::CALCULATING == States::CALCULATING)
		{
			for(int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					ourArray[j + i * width].position = { (float)j,(float)i };
				}
			}
		}
		// Clear screen
		window.clear();
		// Update the window
		window.display();
	}
	return 0;
};