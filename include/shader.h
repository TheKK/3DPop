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
#include <cmath>
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

		void Update();
		void Event( SDL_Event* event );

		void CameraMove( float x, float y, float z );
		//Rotate according to z-axis in world position
		void CameraRotateZ( float matrix[ 4 ][ 4 ], float degree );
		//Rotate according to x-axis in world position
		void CameraRotateX( float matrix[ 4 ][ 4 ], float degree );

		void SetColorMask( bool r, bool g, bool b, bool a );

		void SetPerspective( float width, float height, float near, float far );

		void SetRight();
		void SetLeft();

		//Return m_ShaderProgram
		GLuint GetShaderProgram();
	private:
		//Shader and program
		GLuint m_VertexShader;
		GLuint m_FragmentShader;
		GLuint m_ShaderProgram;

		GLuint m_UniViewMatrix;
		float m_ViewMatrix[ 4 ][ 4 ];

		GLuint m_UniProjectMatrix;
		float m_ProjectMatrix[ 4 ][ 4 ];

		float m_ViewScale;

		//Moving status
		bool m_MovingRight, m_MovingLeft, m_MovingFront, m_MovingBack;

		//Moving speed
		float m_MovingSpeed;

		string LoadString( string filePath );
};

#endif
