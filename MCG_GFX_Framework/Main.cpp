#include <cmath>
#include <iostream>
#include "MCG_GFX_Lib.h"
#include "Shapes.h"
#include <glm/gtx/transform.hpp>

int main(int argc, char* argv[])
{
	
	glm::ivec2 windowSize(640, 480); //this variable stores window dimensions

	if (!MCG::Init(windowSize)) //MCG init initialises and creates windows of dimensions windowSize
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGB, numbers are from 0 to 1
	MCG::SetBackground(glm::vec3(0, 0, 0));

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 1
	glm::vec3 pixelColour(1, 0, 0);

	//Drawing of the shapes

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();





	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:
	

	// Variable to keep track of time
	float timer = 0.0f;
	// This is our game loop
	// It will run until the user presses 'escape' or closes the window

	while( MCG::ProcessFrame() )
	{
	//	 Set every pixel to the same colour
		MCG::SetBackground( glm::vec3(0,0,0) );
	//	 Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
	//	 Update our time variable
		timer += 1.0f / 60.0f;
	//	 Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour);

	
				createCircle(525, 100, 70); //draws circle
		
				createTriangle(70, 320, 2, 0, 0); //draws equilateral triangle
				createTriangle(500, 400, 2, -286, -79); //translation of equilateral triangle
			
				createTriangle(200, 130, 3, 0, 0); //draws iscosoles triangle
				createTriangle(312, 130, 3, 20, 0); //translates iscosoles triangle
			
				createTriangle(70, 250, 1, 0, 0); //draws right angle triangle
				createTriangle(350, 330, 1, -137, -80); //translates right angle triangle
			

				createTriangle(350, 350, 4, 0, 0); //draws scalene triangle
				createTriangle(350, 250, 4, 0, 0); //translates scalene triangle
		
				createSquare(50, 100, 50, 100);
	}
	return 0;
	

}

void createLine(float pos_xA, float pos_yA, float pos_xB, float pos_yB)
{
	//initilising the vectors needed
	glm::ivec2 pixelPosition = glm::ivec2(0, 0); //integer 2D vector that has 2 positions
	glm::vec3 pixelColour(0, 255, 0);

	const bool gradient = (fabs(pos_yB - pos_yA) > fabs(pos_xB - pos_xA)); //fabs is a function in C++ which returns the absolute value of the argument (distance on number line from 0 ignoring direction so always positive)
	if (gradient)
	{
		std::swap(pos_xB, pos_yB); //swap exchanges the values of the parameters
		std::swap(pos_xA, pos_yA); 
	}

	if (pos_xA > pos_xB)
	{
		std::swap(pos_xA, pos_xB); //ensures that A is greater than B 
		std::swap(pos_yA, pos_yB);
	}

	const float change_X = pos_xB - pos_xA;
	const float change_Y = fabs(pos_yB - pos_yA); //fabs ensures positive value

	float error = change_X / 2.0f;
	const int ystep = (pos_yA < pos_yB) ? 1 : -1;
	int y = (int)pos_yA;

	const int max_X = (int)pos_xB;

	for (int x = (int)pos_xA; x <= max_X; x++)
	{
		if (gradient)
		{
			pixelPosition = glm::ivec2(y, x);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}
		else
		{
			pixelPosition = glm::ivec2(x, y);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}

		error -= change_Y;
		if (error < 0)
		{
			y += ystep;
			error += change_X;
		}
	}
}

void createSquare(float pos_x1, float pos_x2, float pos_y1, float pos_y2)
{
	glm::ivec2 pixelPosition = glm::ivec2(0, 0);
	glm::vec3 pixelColour(255, 255, 0);

	float x1, x2, y1, y2;

	x1 = pos_x1;
	x2 = pos_x2;
	y1 = pos_y1;
	y2 = pos_y2;

	//below draws lines between all the points
	createLine(x1, y1, x1, y2); 
	createLine(x2, y2, x1, y2);
	createLine(y2, x1, y1, x1);
	createLine(y2, x1, y2, x2);
}

void createCircle(int x_centre, int y_centre, int radius)
{
	glm::ivec2 pixelPosition = glm::ivec2(0, 0);
	glm::vec3 pixelColour(0, 255, 0);

	int x = radius, y = 0;

	if (radius > 0) //only creates circle if radius is more than zero 
	{
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
	}

	int perimiter = 1 - radius;
	while (x > y)
	{
		y++;

		if (perimiter <= 0) //midpoint is in/on perimiter
		{
			perimiter = perimiter + 2 * y + 1;
		}
		
		else //midpoint is outside perimiter
		{
			x--;
			perimiter = perimiter + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed
		if (x < y)
			break;

		//below prints the generated points and reflects them into the other octants. This works because a circles point of symmetry is the center
		pixelPosition = glm::ivec2(x + x_centre, y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, -y + y_centre);
		MCG::DrawPixel(pixelPosition, pixelColour);

		if (x != y) //if x != y then perimeter points havent been printed 
		{
			pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(y + x_centre, -x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, -x + y_centre);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}

void createTriangle(float pos_X, float pos_Y, int type, float transform_X, float transform_Y)
{
	float x1, y2, x2, y1;
	glm::vec3 pixelColour(255, 255, 0);

	switch (type)
	{
	case 1: //right angle
		x1 = pos_X + 70;
		y2 = pos_Y;
		x2 = pos_X;
		y1 = pos_Y - 70;
		break;
	case 2: //equilateral
		x1 = pos_X + 70;
		y2 = pos_Y;
		x2 = pos_X + 45;
		y1 = pos_Y - 45;
		break;
	case 3: //iscosoles
		x1 = pos_X + 50;
		y2 = pos_Y;
		x2 = pos_X + 25;
		y1 = pos_Y - 50;
		break;
	case 4: //scalene
		x1 = pos_X + 15;
		y2 = pos_Y + 35;
		x2 = pos_X + 55;
		y1 = pos_Y - 40;
		break;
	}

	//below a translation matrix is used to show a matrix transformation
	if (transform_X != 0 || transform_Y != 0)
	{
		glm::mat4 Matrix = glm::translate(glm::mat4(), glm::vec3(transform_X, transform_Y, 0.0f));
		glm::vec4 Vector(pos_X, pos_Y, 0.0f, 1.0f);
		glm::vec4 transformed_vector = Matrix * Vector;
		pos_X = transformed_vector.x;
		pos_Y = transformed_vector.y;
		Vector = glm::vec4(x1, y2, 0.0f, 1.0f);
		transformed_vector = Matrix * Vector;
		x1 = transformed_vector.x;
		y2 = transformed_vector.y;
		Vector = glm::vec4(x2, y1, 0.0f, 1.0f);
		transformed_vector = Matrix * Vector;
		x2 = transformed_vector.x;
		y1 = transformed_vector.y;
	};

	//below draws lines between the 3 points
	createLine(pos_X, pos_Y, x1, y2);
	createLine(x1, y2, x2, y1);
	createLine(x2, y1, pos_X, pos_Y);
}

