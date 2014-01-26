/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * objectManager.h
 *
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include "object.h"

extern "C" {
#include <lua5.2/lua.hpp>
}

using namespace std;

class ObjectManager
{
	public:
		ObjectManager();
		~ObjectManager();

		static bool Init( GLuint shaderProgram );
		static void Draw();
		static void CleanUp();
	private:
		static lua_State* m_LuaState;

		static Object* pCube;
		static Object* pStick;
		static Object* pMonkey;
		static Object* pSphere;

		static int DrawObject( lua_State* L );
};

#endif
