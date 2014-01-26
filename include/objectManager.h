/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * objectManager.h
 *
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <iostream>
#include "object.h"

using namespace std;

class ObjectManager
{
	public:
		ObjectManager();
		~ObjectManager();

		void Init();
		void Draw();
		void CleanUp();
	private:
		Object* pCube;
		Object* pStick;
		Object* pMonkey;
		Object* pSphere;
};

#endif
