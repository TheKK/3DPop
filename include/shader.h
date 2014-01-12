/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * shader.h
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;

class Shader
{
	public:
		Shader();
		~Shader();

		bool BuildShaderProgram( string vertexShader, string fragmentShader );

		//Return m_ShaderProgram
		GLuint GetShaderProgram();
	private:
		//Shader and program
		GLuint m_VertexShader;
		GLuint m_FragmentShader;
		GLuint m_ShaderProgram;

		string LoadString( string filePath );
};

#endif
