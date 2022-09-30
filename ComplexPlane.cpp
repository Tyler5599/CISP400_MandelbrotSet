#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ccomplex>

using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::loadText(Text& text)
{
	//Doesn't work needs to pass in stream to text box after its passed but it acts like I am passing another object
	
	stringstream mystream;
	Vector2f center = m_view.getCenter();
	mystream << "Mandelbrot Set" << endl << "Center: (" << center.x  << "," << center.y << ")" << endl << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
		<< "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
	string input = mystream.str();
	text.setString(input);
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	//works now
	float x = coord.x;
	float y = coord.y;

	size_t count = 0;
	complex<float> c(x, y);
	complex<float> z(0, 0);

	while (abs(z) < 2.0 && count < MAX_ITER)
	{
		z = z * z + c;
		count++;
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count > 0 && count <= 16)
	{
		//code for 1-16 iterations
		r = 300 - (count * 4);
		g = 350 - (count * 4);
		b = 0 - (count * 4);
	}
	else if (count > 16 && count <= 32)
	{
		//code for 17-32 iterations
		r =  300 - (count * 4);
		g = 300 - (count * 4);
		b = 200 - (count * 4);
	}
	else if (count > 32 && count <= 48)
	{
		//code for 33-48 iterations
		r = 400 - (count * 4);
		g =  250- (count * 4);
		b = 100 - (count * 4);
	}
	else if (count > 48 && count < 64)
	{
		//code for 49-64 iterations
		r = 75 - (count * 2);
		g = 0 - (count * 2);
		b = 500 - (count * 2);
	}
	else
	{
		r = 0;
		g = 0;
		b = 0;
	}
}
