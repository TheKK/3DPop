/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * objectManager.cpp
 *
 */

#include "objectManager.h"

lua_State* ObjectManager::m_LuaState;
Object* ObjectManager::pCube;
Object* ObjectManager::pStick;
Object* ObjectManager::pMonkey;
Object* ObjectManager::pSphere;

int
ObjectManager::DrawObject( lua_State* L )
{
	const char* objectType;

	//Get object type
	objectType = lua_tostring( L, 1 );
	if( objectType == NULL ){
		fprintf( stderr, "Error: non-string.\n" );
		exit( 1 );
	}

	//Get coordinate
	int x = lua_tonumber( L, 2 );
	int y = lua_tonumber( L, 3 );
	int z = lua_tonumber( L, 4 );

	if( strcmp( objectType, "sphere" ) == 0 ){
		pSphere->SetPosition( x, y, z );
		pSphere->Draw();
	}
	else if( strcmp( objectType, "cube" ) == 0 ){
		pCube->SetPosition( x, y, z );
		pCube->Draw();
	}
	else if( strcmp( objectType, "stick" ) == 0 ){
		pStick->SetPosition( x, y, z );
		pStick->Draw();
	}
	else if( strcmp( objectType, "monkey" ) == 0 ){
		pMonkey->SetPosition( x, y, z );
		pMonkey->Draw();
	}

	return 0;
}

ObjectManager::ObjectManager ()
{
	pCube = NULL;
	pStick = NULL;
	pMonkey = NULL;
	pSphere = NULL;
}

ObjectManager::~ObjectManager ()
{
	CleanUp();
}

bool
ObjectManager::Init ( GLuint shaderProgram )
{
	/*Lua*/
	//Create new Lua state
	m_LuaState = luaL_newstate();

	//Open Lua build-in libs
	luaL_openlibs( m_LuaState );

	//Regist our C function
	lua_register( m_LuaState, "Draw", DrawObject );

	/*Object*/
	//Status flag
	bool status;

	//Initialize and setup cube object
	pCube = new Object( 0, 0, 0 );
	pCube->SetShader( shaderProgram );
	status = pCube->LoadOBJ( "obj/cube.obj" );
	if( status == false )
		return status;

	pStick = new Object( 0, 0, 0 );
	pStick->SetShader( shaderProgram );
	status = pStick->LoadOBJ( "obj/stick.obj" );
	if( status == false )
		return status;

	pSphere = new Object( 0, 0, 0 );
	pSphere->SetShader( shaderProgram );
	status = pSphere->LoadOBJ( "obj/sphere.obj" );
	if( status == false )
		return status;

	pMonkey = new Object( 0, 0, 0 );
	pMonkey->SetShader( shaderProgram );
	status = pMonkey->LoadOBJ( "obj/monkey.obj" );
	if( status == false )
		return status;

	return status;
}

void
ObjectManager::Draw ()
{
	if( luaL_dofile( m_LuaState, "script/drawSomething.lua" ) ){
		fprintf( stderr, "Lua error: %s.\n", lua_tostring( m_LuaState, -1 ) );
		exit( 1 );
	}
}

void
ObjectManager::CleanUp ()
{
	lua_close( m_LuaState );

	delete pCube;
	delete pStick;
	delete pMonkey;
	delete pSphere;
}
