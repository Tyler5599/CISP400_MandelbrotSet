#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class ComplexPlane
{
public:
	ComplexPlane(float aspectRatio);
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2f);
	View getView();
	void setMouseLocation(Vector2f);
	void loadText(Text&);
	size_t countIterations(Vector2f);
	void iterationsToRGB(size_t count, Uint8 r, Uint8 g, Uint8 b);

private:
	float m_aspectRatio;
	Vector2f m_mouseLocation;
	View m_view;
	int m_zoomCount;

};


const Uint8 MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

#endif