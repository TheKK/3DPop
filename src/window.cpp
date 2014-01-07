/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * window.cpp
 *
 */

#include "window.h"

//Static members in Window class
SDL_Window* Window::m_Window;
SDL_GLContext Window::m_GLContext;

bool
Window::Init ( char* windowTitle, int width, int height )
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return false;

	//Create and setup new SDL window, and check error
	m_Window = SDL_CreateWindow(
			windowTitle,					//Window title
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//Position of window
			width, height,					//Size of window
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL		//Window flags
			);
	if( m_Window == NULL ){
		fprintf( stderr, "SDL error: %s\n", SDL_GetError() );
		return false;
	}

	//Create OpenGL context for window, m_Window
	m_GLContext = SDL_GL_CreateContext( m_Window );

	//Force GLEW to use morden OpenGL method for checking functions
	glewExperimental = GL_TRUE;
	glewInit();

	//Set OpenGL clear color
	glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );

	//Check error
	GLenum error = glGetError();
	if( error != GL_NO_ERROR ){
		fprintf( stderr, "OpenGL error: %s\n", gluErrorString( error ) );
		return false;
	}

	srand( time( NULL ) );

	return true;
}

void
Window::Clear ()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void
Window::Present ()
{
	SDL_GL_SwapWindow( m_Window );
}

void
Window::Quit ()
{
	SDL_DestroyWindow( m_Window );
	m_Window = NULL;

	SDL_GL_DeleteContext( m_GLContext );

	SDL_Quit();
}
