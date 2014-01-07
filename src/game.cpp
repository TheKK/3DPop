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
	//Status for return	
	bool status;

	int screenWidth = 800;
	int screenHeight = 800;
	char* screenTitle = "POP3D";

	char* vertexShaderPath = "./shader/basic.vs";
	char* fragmentShaderPath = "./shader/basic.fs";

	//Initialize window properties
	status = Window::Init( screenTitle, screenWidth, screenHeight );

	//Initialize and setup shader
	pShader = new Shader();
	status = pShader->BuildShaderProgram( vertexShaderPath, fragmentShaderPath );

	return status;
}

void
Game::EventHandler ( SDL_Event* event )
{
	switch( event->type ){
		case SDL_KEYDOWN:
			if( event->key.keysym.sym == SDLK_q )
				m_IsRunning = false;

			if( event->key.keysym.sym == SDLK_c )
				glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );

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
	delete pTimer;
}
