#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ccomplex>

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

View ComplexPlane::getView()
{
	return m_view;
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
	//not done yet dont understand instructions
	
	int count = 0;
	
	for (int i = 0; i < MAX_ITER; i++)
	{
		complex<double> c(Vector2f().x, Vector2f().y);
		complex<double> z(0, 0);
		if (c != 2.0)
		{
			z = z * z + c;
			count++;
		}		
	}
	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 r, Uint8 g, Uint8 b)
{
	if (count == 1)
	{
		//code for 1 iteration
	}
	else if (count > 1 && count <= 16)
	{
		//code for 2-16 iterations
	}
	else if (count > 16 && count <= 32)
	{
		//code for 17-32 iterations
	}
	else if (count > 32 && count <= 48)
	{
		//code for 33-48 iterations
	}
	else if(count > 48 && count < 64)
	{
		//code for 49-64 iterations
	}
	else
	{
		//code for excess iterations
	}
}
