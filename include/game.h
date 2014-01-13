/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * game.h
 *
 */

#ifndef GAME
#define GAME

#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include "timer.h"
#include "window.h"
#include "shader.h"
#include "object.h"

class Game
{
	public:
		Game();
		~Game();

		//Start main game
		int Execute();

	private:
		Timer* pTimer;
		Shader* pShader;

		Object* pCube;
		Object* pStick;
		Object* pMonkey;
		Object* pSphere;

		bool m_IsRunning;
		bool m_Is3D;

		bool Init();
		void EventHandler( SDL_Event* event );
		void Update();
		void Render();
		void CleanUp();
};

#endif








