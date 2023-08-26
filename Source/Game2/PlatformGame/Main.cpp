#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <thread>
#include <map>
#include <functional>

#include "Platformer.h"

#include "Renderer\Renderer.h"

#include "Input\InputSystem.h"

#include "Audio\AudioSystem.h"

#include "Framework/FrameWork.h"

#include "Core\Core.h"

#include "Physics/PhysicsSystem.h"


using namespace std;
int main(int argc, char* argv[])
{

	INFO_LOG("INITIALLIZE ENGINE.........");

	Twili::MemoryTracker::Initialize();
	Twili::seedRandom((unsigned)time(nullptr));
	Twili::setFilePath("assets");

	Twili::g_rend.Init(); Twili::g_rend.CreateWindow("CSC196", 800, 600);

	Twili::g_inputSys.Initialize();
	Twili::g_noise.Initialize();
	Twili::PhysicsSystem::Instance().Init();

	unique_ptr<Twili::Platformer> game = make_unique<Twili::Platformer>();
	game->Init();

	//main game code
	bool quit = false;
	while (!quit)
	{
		Twili::g_time.Tick();

		Twili::g_inputSys.Update();
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		Twili::g_ParticleSystem.Update(Twili::g_time.getDeltaTime());
		Twili::PhysicsSystem::Instance().Update(Twili::g_time.getDeltaTime());


		game->Update(Twili::g_time.getDeltaTime());

		Twili::g_rend.setColor(0, 0, 0, 0);
		Twili::g_rend.beginFrame();
		Twili::g_noise.PlayOneShot("MakeItPop", true);
		game->Draw(Twili::g_rend);

		Twili::g_ParticleSystem.Draw(Twili::g_rend);
		Twili::g_rend.EndFrame();
	};


	return 0;
	/*Twili::g_memoryTracker.Display();
	int* p = new int;
	Twili::g_memoryTracker.Display();
		   delete p;
	Twili::g_memoryTracker.Display();

	Twili::Time timer;
	for(int i = 0; i < 100000000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;*/

	/*


	   cout << Twili::getFilePath() << std::endl;
	   Twili::setFilePath("Assets");
	   cout << Twili::getFilePath() << std::endl;
	   size_t size;
	   Twili::getFileSize("game.txt", size);
	   cout << size << endl;

	   std::string s;
	   Twili::readFile("game.txt",s);
	   cout << s << endl;

	   Twili::seedRandom((unsigned int)time(nullptr));
	   for (int i = 0; i < 10; i++) {
		   std::cout << Twili::random(5, 10) << std::endl;
	   }*/

};