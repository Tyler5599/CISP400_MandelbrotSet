#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	//variables
	float aspect;
	float width, height;
	width = VideoMode::getDesktopMode().width;
	height = VideoMode::getDesktopMode().height;
	aspect = height/width;
	ComplexPlane plane1(aspect);
	VertexArray ourArray;
	ourArray.setPrimitiveType(Points);
	ourArray.resize(height * width);
	enum States
	{
		CALCULATING, DISPLAYING
	};
	States current = CALCULATING;

	//render window
	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot!!!", Style::Default);

	//Vector2f for loading center point on screen
	Vector2f textCoord;
	//Font disabled until font file added!!!!!!!!!
	Font font;
	font.loadFromFile("arial.ttf");
	Text text1;
	text1.setFont(font);
	text1.setColor(sf::Color::Red);
	text1.setCharacterSize(30);
	text1.setStyle(Text::Regular);
	//game loop
	while (window.isOpen())
	{
		//Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			//close is esc key is pressed
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			//handle mouse button clicks
			if (event.type == Event::MouseButtonPressed)
			{
				Vector2f points;
				points = window.mapPixelToCoords(Mouse::getPosition(window), plane1.getView());

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					plane1.zoomIn();
					textCoord = points;
					plane1.setCenter(points);
				}
				if (Mouse::isButtonPressed(Mouse::Right))
				{
					plane1.zoomOut();
					textCoord = points;
					plane1.setCenter(points);
				}
				current = CALCULATING;
			}
			/*Handle Event::MouseMovedUse mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View that corresponds to the screen mouse location
			setMouseLocation on the ComplexPlane object to store this coordinate This will be used later to display the mouse coordinates as it moves*/
			if (event.MouseMoved)
			{
				Vector2f points;
				points = window.mapPixelToCoords(Mouse::getPosition(window), plane1.getView());
				plane1.setMouseLocation(points);
			}
			
		}
		// Test if enum current == States::CALCULATING in order to loop through double for loop to gather iterations of each pixel
		// Assigns Uint8 data type variables r,g,b to color scheme for iterations
		if (current == States::CALCULATING)
		{
			size_t count = 0;

			for (int j = 0; j < static_cast<int>(width); j++)
			{
				for (int i = 0; i < static_cast<int>(height); i++)
				{
					Vector2i points(j, i);
					ourArray[j + i * static_cast<int>(width)].position = { (float)j,(float)i };
					//Created vector2f to push points of complex plane into countIterations function
					Vector2f Coord = window.mapPixelToCoords(points, plane1.getView());
					count = plane1.countIterations(Coord);

					Uint8 r;
					Uint8 g;
					Uint8 b;
					plane1.iterationsToRGB(count, r, g, b);
					ourArray[j + i * width].color = { r,g,b };
					
				}

			}
			current = DISPLAYING;
		}

		// Draw VertexArray & Text
		window.clear();
		window.draw(ourArray);
		plane1.loadText(text1, textCoord);
		window.draw(text1);
		//window.draw(text1);

		// Update the window
		window.display();
	}
	return 0;
};