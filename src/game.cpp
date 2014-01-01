/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * game.cpp
 *
 */

#include "game.h"

Game::Game ()
{
}

Game::~Game ()
{
	CleanUp();
}

bool
Game::Init ()
{	
	int screenWidth = 500;
	int screenHeight = 500;
	char* screenTitle = "POP3D";

	bool status = Window::Init( screenTitle, screenWidth, screenHeight );

	return status;
}

void
Game::EventHandler ( SDL_Event* event )
{
	switch( event->type ){
		case SDL_KEYDOWN:
			if( event->key.keysym.sym == SDLK_q )
				m_IsRunning = false;
			break;
	};
}

void
Game::Update ()
{
}

void
Game::Render ()
{
	Window::Clear();
	Window::Present();
}

int
Game::Execute ()
{
	if( Init() == false )
		return 1;
	else{
		pTimer = new Timer();
		
		m_IsRunning = true;

		SDL_Event event;

		while( m_IsRunning ){
			pTimer->start();
			
			while( SDL_PollEvent( &event ) ){
				EventHandler( &event );
			}	

			Update();

			Render();

			//Limit max frame rate per second( FPS )
			if( pTimer->getTicks() < 1000 / 60 )
				SDL_Delay( ( 1000 / 60 ) - pTimer->getTicks() );
		}
	}	
	return 0;
}

void
Game::CleanUp ()
{
}
