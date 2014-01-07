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

class Game
{
	public:
		Game();
		~Game();

		bool Init();
		void EventHandler( SDL_Event* event );
		void Update();
		void Render();
		int Execute();
		void CleanUp();

	private:
		Timer* pTimer;
		Shader* pShader;

		bool m_IsRunning;
};

#endif








