/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * game.cpp
 *
 */

#include "game.h"

Game::Game ()
{
	m_Render = false;
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

	//Initialize window properties
	status = Window::Init( screenTitle, screenWidth, screenHeight );
	if( status == false )
		return status;

	//Initialize and setup shader
	pRightShader = new Shader();
	status = pRightShader->BuildShaderProgram( "shader/right.vs", "shader/right.fs" );
	if( status == false )
		return status;

	//Initialize and setup cube object
	pCube = new Object( 5, 5, 0 );
	pCube->SetShader( pRightShader->GetShaderProgram() );
	status = pCube->LoadOBJ( "obj/cube.obj" );
	if( status == false )
		return status;

	pStick = new Object(-5, 5, 0 );
	pStick->SetShader( pRightShader->GetShaderProgram() );
	status = pStick->LoadOBJ( "obj/stick.obj" );
	if( status == false )
		return status;

	pSphere = new Object(-5,-5, 0 );
	pSphere->SetShader( pRightShader->GetShaderProgram() );
	status = pSphere->LoadOBJ( "obj/sphere.obj" );
	if( status == false )
		return status;

	pMonkey = new Object( 5,-5, 0 );
	pMonkey->SetShader( pRightShader->GetShaderProgram() );
	status = pMonkey->LoadOBJ( "obj/monkey.obj" );
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

			if( event->key.keysym.sym == SDLK_e ){
				if( m_Render )
					m_Render = false;
				else
					m_Render = true;
			}

			if( event->key.keysym.sym == SDLK_UP )
				pMonkey->Move( 0.05, 0, 0 );

			break;
	};

	Window::Event( event );

	pRightShader->Event( event );
}

void
Game::Update ()
{
	pRightShader->Update();
}

void
Game::Render ()
{
	Window::Clear();
	
	//Right eye part
	pRightShader->SetColorMask( true, true, true, true );

	pRightShader->SetColorMask( true, false, false, true );
	pRightShader->SetRight();

	pMonkey->Draw();
	pSphere->Draw();
	pStick->Draw();
	pCube->Draw();

	pRightShader->SetColorMask( true, true, true, true );

	glDrawBuffer( GL_BACK );
	
	glClear( GL_DEPTH_BUFFER_BIT );

	//Left eye part
	pRightShader->SetColorMask( true, true ,true, true );

	pRightShader->SetColorMask( false, false ,true, true );
	pRightShader->SetLeft();

	pMonkey->Draw();
	pSphere->Draw();
	pStick->Draw();
	pCube->Draw();

	pRightShader->SetColorMask( true, true, true, true );

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
	delete pStick;
	delete pMonkey;
	delete pSphere;
}
