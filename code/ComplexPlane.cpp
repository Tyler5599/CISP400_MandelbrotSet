#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * aspectRatio);
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

View cgetView()
{
	//code
}
void ComplexPlane::loadText(Text&)
{
	Text;
	stringstream mystream;
	mystream << "Mandelbrot Set" << endl << "Center: (0,0)" << endl << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl 
	<< "Left-click to Zoom in" << endl << "Right-click to Zoom out" << endl;
}
size_t ComplexPlane::countIterations(Vector2f)
{
	//code
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8 r, Uint8 g, Uint8 b)
{
	//code
}
