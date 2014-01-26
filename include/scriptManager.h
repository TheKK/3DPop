/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * scriptManager.h
 *
 */

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <iostream>
#include <cstdlib>

extern "C" {
#include <lua5.2/lua.hpp>
}

using namespace std;

class ScriptManager
{
	public:
		ScriptManager();
		~ScriptManager();

		static int GetInteger( char* filePath, char* variableName );
		static const char* GetString( char* filePath, char* variableName );

	private:


};

#endif
