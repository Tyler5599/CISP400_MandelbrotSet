#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	//variables
	float aspect, width, height;
	width = VideoMode::getDesktopMode().width;
	height = VideoMode::getDesktopMode().height;
	aspect = height * width;
	ComplexPlane plane1(aspect);
	VertexArray ourArray;
	ourArray.setPrimitiveType(Points);
	ourArray.resize(height * width);
	enum States
	{
		CALCULATING, DISPLAYING
	};
	States current = CALCULATING;

	//calculating aspect ratio by dividing or values that were rturned from get width and height functions
	
	/*width =	VideoMode::getDesktopMode().width;
	height = VideoMode::getDesktopMode().height;
	aspect = height / width;*/

	//render window
	VideoMode vm(height, width);
	RenderWindow window(vm, "Mandelbrot!!!", Style::Default);
	
	//Font disabled until font file added!!!!!!!!!
	
	/*Font font;
	font.loadFromFile("arial.ttf");
	Text text1;
	text1.setFont(font);
	text1.setCharacterSize(30);
	text1.setStyle(Text::Regular);*/


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
				points = window.mapPixelToCoords(Mouse::getPosition());
				plane1.setCenter(points);

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Vector2f points(Mouse::getPosition().x, Mouse::getPosition().y);
					plane1.zoomIn();
				}
				if (Mouse::isButtonPressed(Mouse::Right))
				{
					Vector2f points(Mouse::getPosition().x, Mouse::getPosition().y);
					plane1.zoomOut();
				}
				States::CALCULATING;
			}
			/*Handle Event::MouseMovedUse mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View that corresponds to the screen mouse location
			setMouseLocation on the ComplexPlane object to store this coordinate This will be used later to display the mouse coordinates as it moves*/
			if (event.MouseMoved)
			{
				Vector2f points;
				points = window.mapPixelToCoords(Mouse::getPosition());
				plane1.setMouseLocation(points);
			}
		}

		// Test if enum current == States::CALCULATING in order to loop through double for loop to gather iterations of each pixel
		// Assigns Uint8 data type variables r,g,b to color scheme for iterations
		if (current == States::CALCULATING)
		{
			size_t count = 0;
			Vector2f points;
			for(float j = 0.0; j < height; j++)
			{
				for (float i = 0.0; i < width; i++)
				{
					ourArray[j + i * width].position = { (float)j,(float)i };

					//points = window.mapPixelToCoords(Vector2i{ j,i }, plane1.getView()); currently gives compiler error:  "Error C2398 Element '1': conversion from 'float' to 'T' requires a narrowing conversion"
					points = window.mapPixelToCoords(Vector2i{ j,i }, plane1.getView());


					count = plane1.countIterations(points);
					Uint8 r, g, b;
					plane1.iterationsToRGB(count, r, g, b);
					ourArray[j + i * width].color = { r,g,b };

				}

				States::DISPLAYING;
			}
		}
		// Clear screen
		window.clear();
		
		// Draw VertexArray & Text
		window.draw(ourArray);
		//window.draw(text1);

		// Update the window
		window.display();
	}
	return 0;
};