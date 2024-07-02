#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include <SDL.h>
#include<vector>
#include <iostream>


int main(int argc, char* argv[])
{



	//create system
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();



	Vector2 v1{ 400,300 };
	Vector2 v2{ 600,200 };

	std::vector<Vector2> points;

	

	/*for(int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}*/
	
	bool quit = false;
	while (!quit)
	{
		//input
		//update
		//draw


		//INPUT 
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}


		//Update
		Vector2 mousePosition = input.GetMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;


		if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		{
			std::cout << "Mouse Pressed\n";
			points.push_back(mousePosition);
		}
		if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			
			if (distance > 5) points.push_back(mousePosition);
		}

		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.SetColor(255, 255, 255, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}




		/*Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.002f;
		}*/


	/*	renderer.SetColor(0, 0, 0, 0);

		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);
		renderer.DrawLine(600,300,150,300);
		renderer.DrawLine(600, 300, 350, 400);
		renderer.DrawLine(150, 300, 350, 400);  

		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}*/

		renderer.EndFrame();
	}

	return 0;
}

