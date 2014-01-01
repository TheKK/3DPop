/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * window.cpp
 *
 */

#include "window.h"

//Static members in Window class
SDL_Window* Window::m_Window;
SDL_Renderer* Window::m_Renderer;

bool
Window::Init ( char* windowTitle, int width, int height )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return false;

	m_Window = SDL_CreateWindow(
			windowTitle,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN
			);
	if( m_Window == NULL ){
		fprintf( stderr, "SDL error: %s\n", SDL_GetError() );
		return false;
	}

	m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED );
	if( m_Renderer == NULL ){
		fprintf( stderr, "SDL error: %s\n", SDL_GetError() );
		return false;
	}

	SDL_SetRenderDrawColor( m_Renderer, 0x00, 0xFF, 0xFF, 0xFF );

	srand( time( NULL ) );

	return true;
}

void
Window::Clear ()
{
	SDL_RenderClear( m_Renderer );	
}

void
Window::Present ()
{
	SDL_RenderPresent( m_Renderer );
}

void
Window::Quit ()
{
	SDL_DestroyWindow( m_Window );
	m_Window = NULL;

	SDL_DestroyRenderer( m_Renderer );
	m_Renderer = NULL;

	SDL_Quit();
}
