/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * object.h
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;

class Object
{
	public:
		//Can set position when construct this object
		Object( float x, float y, float z );
		~Object();

		void Draw();
		void Update();
		void Event( SDL_Event* event );

		void Move( float x, float y, float z );
		void SetPosition( float x, float y, float z );

		void SetShader( GLuint shaderProgram ); 
		bool LoadOBJ( char* path );

	private:
		//Vertex array object
		GLuint m_VAO;

		//Vertex buffer object
		GLuint m_VBO;
		//Normal buffer object	
		GLuint m_NBO;
		//Element buffer object
		GLuint m_EBO;

		//Shader program used to render this object
		GLuint m_ShaderProgram;

		//Recored how many element need to be drawn
		unsigned int m_ElementNum;

		GLuint m_UniModelMatrix;
		float m_ModelMatrix[ 4 ][ 4 ];
		
		bool OBJConvert( char* path, vector<GLfloat> &vertex, vector<GLfloat> &normal, vector<GLuint> &element );
		void CleanUp();
};

#endif
