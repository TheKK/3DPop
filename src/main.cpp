/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * main.cpp
 *
 */

#include <iostream>
#include <cstdio>
#include "game.h"

int
main ( int argc, char* argv[] )
{
	//Create and initialize main game
	Game* game;
	game = new Game();

	game->Execute();

	return 0;
}
