// BALLS.cpp : Defines the entry point for the application.
//

#include "BALLS.h"
#include "graphics/graphics.h"

int main()
{

	Graphics graphics;
	graphics.init();

	while (true) {
		graphics.draw();
	}

	return 0;
}
