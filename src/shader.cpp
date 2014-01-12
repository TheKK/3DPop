/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * shader.cpp
 *
 */

#include "shader.h"

Shader::Shader ()
{
}

Shader::~Shader ()
{
	glDeleteProgram( m_ShaderProgram );
	glDeleteShader( m_VertexShader );
	glDeleteShader( m_FragmentShader );
}

bool
Shader::BuildShaderProgram ( string vertexShaderPath, string fragmentShaderPath )
{
	string source;
	GLint errorStatus;

	//Load, create and compile vertex shader
	source = LoadString( vertexShaderPath );
	if( source == "" )
		return false;

	m_VertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( m_VertexShader,		//Shader for used
			1,			//Number of array to load
			(const GLchar**)&source,//Path of array
			NULL			//When loaded "NULL", terminate loading array
		      );
	glCompileShader( m_VertexShader );

	//Check error after compiling vertex shader
	glGetShaderiv( m_VertexShader, GL_COMPILE_STATUS, &errorStatus );
	if( errorStatus != GL_TRUE ){
		char errorLog[ 512 ];

		glGetShaderInfoLog( m_VertexShader, 512, NULL, errorLog );

		fprintf( stderr, "Shader Compile Error: %s\n", errorLog );

		return false;
	}

	//Load, create and compile fragment shader
	source = LoadString( fragmentShaderPath );
	if( source == "" )
		return false;

	m_FragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( m_FragmentShader,	//Shader for used
			1,			//Number of array to load
			(const GLchar**)&source,//Path of array
			NULL			//When loaded "NULL, terminate loading array
		      );
	glCompileShader( m_FragmentShader );

	//Check error after compiling fragment shader
	glGetShaderiv( m_FragmentShader, GL_COMPILE_STATUS, &errorStatus );
	if( errorStatus != GL_TRUE ){
		char errorLog[ 512 ];

		glGetShaderInfoLog( m_FragmentShader, 512, NULL, errorLog );

		fprintf( stderr, "Shader Compile Error: &s\n", errorLog );

		return false;
	}

	//Create a shader program and bind our vertex and fragment shader into it
	m_ShaderProgram = glCreateProgram();

	glAttachShader( m_ShaderProgram, m_VertexShader );
	glAttachShader( m_ShaderProgram, m_FragmentShader );

	glBindFragDataLocation( m_ShaderProgram, 0, "outColor" );

	glLinkProgram( m_ShaderProgram );
	glUseProgram( m_ShaderProgram );	

	//Enable depth test
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	return true;
}

string
Shader::LoadString ( string filePath )
{
	//Create file stream and check error
	ifstream source( filePath.c_str(), ios::in );
	if( !source.good() ){
		fprintf( stderr, "File open failed: %s\n", filePath.c_str() );
		return "";
	}

	//Stream the file data into string	
	stringstream buffer;
	buffer << source.rdbuf();

	source.close();

	//Return the string pointer
	return buffer.str();
}

GLuint
Shader::GetShaderProgram ()
{
	return m_ShaderProgram;
}
