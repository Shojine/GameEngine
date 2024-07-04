#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "E_Timer.h"
#include <SDL.h>
#include<vector>
#include <iostream>


int main(int argc, char* argv[])
{



	//create system
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 1020, 800);

	Input input;
	input.Initialize();

	Time time;



	//std::vector<Vector2> points;
	std::vector<Particle> particles;
	/*for(int i = 0; i < 0; i++)
	{
		particles.push_back(Particle{ {rand() % 800,rand() % 800},{randomf(100.0f,300.0f), 0.0f}});
	}*/
	

	/*for(int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}*/
	
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		std::cout << time.GetTime() << std::endl;
	
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

		if (input.GetMouseButtonDown(0))
		{
			
			particles.push_back(Particle{ mousePosition,{randomf(-100.0f,100.0f), randomf(-100,100)},randomf(1,5)});
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;

		}




			renderer.SetColor(0, 0, 0, 0);
			renderer.BeginFrame();


		  //  renderer.SetColor(255, 255, 255, 0);
			
			
			for (Particle particle : particles)
			{
				particle.Draw(renderer);
			}








		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;


		/*if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0))
		{
			std::cout << "Mouse Pressed\n";
			points.push_back(mousePosition);
		}
		if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			
			if (distance > 5) points.push_back(mousePosition);
		}*/

		/*for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.SetColor(255, 255, 255, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}*/




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

