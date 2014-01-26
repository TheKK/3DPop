/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * objectManager.cpp
 *
 */

#include "objectManager.h"

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

void
ObjectManager::Init ()
{
}

void
ObjectManager::Draw ()
{
}

void
ObjectManager::CleanUp ()
{

}
