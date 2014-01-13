/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * window.h
 *
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>		//glew must diclare brfore SDL_opengl.h
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window
{
	public:
		Window();
		~Window();

		static bool Init( char* windowTitle, int width, int height );

		static void Clear();
		static void Present();
		static void Event( SDL_Event* event );

		static void Quit();

		static SDL_Window* GetWindow();
	private:
		//SDL window
		static SDL_Window* m_Window;

		static float m_WindowAspect;

		//OpenGL context in SDL
		static SDL_GLContext m_GLContext;

		static bool m_IsWindowed;

		static void WindowResize( int width, int height );
};

#endif
