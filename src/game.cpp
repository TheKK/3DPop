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
	//Status flag
	bool status;

	int screenWidth = 800;
	int screenHeight = 800;
	char* screenTitle = "POP3D";

	char* vertexShaderPath = "./shader/basic.vs";
	char* fragmentShaderPath = "./shader/basic.fs";

	//Initialize window properties
	status = Window::Init( screenTitle, screenWidth, screenHeight );
	if( status == false )
		return status;

	//Initialize and setup shader
	pShader = new Shader();
	status = pShader->BuildShaderProgram( vertexShaderPath, fragmentShaderPath );
	if( status == false )
		return status;

	//Initialize and setup cube object
	pCube = new Object();
	pCube->SetShader( pShader->GetShaderProgram() ); 
	status = pCube->LoadOBJ( "obj/cube.obj" );
	if( status == false )
		return status;

	test1 = new Object();
	test1->SetShader( pShader->GetShaderProgram() ); 
	status = test1->LoadOBJ( "obj/test1.obj" );
	if( status == false )
		return status;

	test2 = new Object();
	test2->SetShader( pShader->GetShaderProgram() ); 
	status = test2->LoadOBJ( "obj/test2.obj" );
	if( status == false )
		return status;
	
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

	Window::Event( event );

	pCube->Event( event );
}

void
Game::Update ()
{
}

void
Game::Render ()
{
	Window::Clear();
	
	test1->Draw();
	test2->Draw();

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
	delete pCube;
}
