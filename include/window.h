/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * window.h
 *
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL2/SDL.h>

class Window
{
	public:
		Window();
		~Window();

		static bool Init( char* windowTitle, int width, int height );
		static void Clear();
		static void Present();
		static void Quit();

	private:
		//SDL stuffs
		static SDL_Window* m_Window;
		static SDL_Renderer* m_Renderer;
};

#endif
