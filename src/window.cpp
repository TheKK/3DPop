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
float Window::m_WindowAspect;
bool Window::m_IsWindowed;

Window::Window ()
{
	m_IsWindowed = true;
	m_WindowAspect = 0;

	m_Window = NULL;
}

bool
Window::Init ( char* windowTitle, int width, int height )
{
	//Recored window aspect
	m_WindowAspect = width / height;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return false;

	//Create and setup new SDL window, and check error
	m_Window = SDL_CreateWindow(
			windowTitle,					//Window title
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//Position of window
			width, height,					//Size of window
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | 		//Window flags
			SDL_WINDOW_RESIZABLE
			);
	if( m_Window == NULL ){
		fprintf( stderr, "SDL error: %s\n", SDL_GetError() );
		return false;
	}

	//Lock mouse
	SDL_SetRelativeMouseMode( SDL_TRUE );

	//Create OpenGL context for window, m_Window
	m_GLContext = SDL_GL_CreateContext( m_Window );

	//Use double buffer
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );

	//Force GLEW to use morden OpenGL method for checking functions
	glewExperimental = GL_TRUE;
	glewInit();

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
	//Set OpenGL clear color
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void
Window::Present ()
{
	SDL_GL_SwapWindow( m_Window );
}

void
Window::Event ( SDL_Event* event )
{
	switch( event->type ){
		case SDL_KEYDOWN:
			if( event->key.keysym.sym == SDLK_RETURN ){
				if( m_IsWindowed == true ){
					SDL_SetWindowFullscreen( Window::GetWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP );
				m_IsWindowed = false;
				}

				else{
					SDL_SetWindowFullscreen( Window::GetWindow(), 0 );
					m_IsWindowed = true;
				}
			}
			break;

		case SDL_WINDOWEVENT:
			if( event->window.event == SDL_WINDOWEVENT_RESIZED ){
				WindowResize( event->window.data1, event->window.data2 );
			}
			break;
	}
}

void
Window::Quit ()
{
	SDL_DestroyWindow( m_Window );
	m_Window = NULL;

	SDL_GL_DeleteContext( m_GLContext );

	SDL_Quit();
}

SDL_Window*
Window::GetWindow ()
{
	return m_Window;
}

void
Window::WindowResize( int width, int height )
{
	if( ( ( float )width / ( float )height ) > m_WindowAspect ){
		int widthBlank = ( width - height * m_WindowAspect ) / 2;
		glViewport( widthBlank, 0, height * m_WindowAspect, height );
	}

	else if( ( ( float )width / ( float )height ) < m_WindowAspect ){
		int heightBlank = ( height - width / m_WindowAspect ) / 2;
		glViewport( 0, heightBlank, width, width / m_WindowAspect );
	}

	else if( ( ( float )width / ( float )height ) == m_WindowAspect )
		glViewport( 0, 0, width, height );
}
