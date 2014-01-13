/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * shader.cpp
 *
 */

#include "shader.h"

Shader::Shader ()
{
	//Initialze view matrix
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ){
			if( i == j )
				m_ViewMatrix[ i ][ j ] = 1;
			else
				m_ViewMatrix[ i ][ j ] = 0;
		}
	CameraRotateX( m_ViewMatrix, -1 * 3.14 / 2 );

	//Initialze projection matrix
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			m_ProjectMatrix[ i ][ j ] = 0;

	SetPerspective( 5, 5, 1, 100 );

	m_ViewScale = 0.1;
	m_ViewAngle = 0.03;

	//Initialize move status
	m_MovingRight = false;
	m_MovingLeft = false;
	m_MovingFront = false;
	m_MovingBack = false;

	//Initialize move speed
	m_MovingSpeed = 0.3;
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

		fprintf( stderr, "Vertex Shader Compile Error: %s\n", errorLog );

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

		fprintf( stderr, "Fragment Shader Compile Error: %s\n", errorLog );

		return false;
	}

	//Create a shader program and bind our vertex and fragment shader into it
	m_ShaderProgram = glCreateProgram();

	glAttachShader( m_ShaderProgram, m_VertexShader );
	glAttachShader( m_ShaderProgram, m_FragmentShader );

	glBindFragDataLocation( m_ShaderProgram, 0, "outColor" );

	glLinkProgram( m_ShaderProgram );
	glUseProgram( m_ShaderProgram );	

	//Get uniform loaction in GLSL
	m_UniViewMatrix = glGetUniformLocation( m_ShaderProgram, "V" );
	m_UniProjectMatrix = glGetUniformLocation( m_ShaderProgram, "P" );

	//Enable depth test
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	return true;
}

void
Shader::Update ()
{
	if( m_MovingFront == true )
		CameraMove( 0, 0, m_MovingSpeed );
	
	if( m_MovingBack == true )
		CameraMove( 0, 0, -1 * m_MovingSpeed );
	
	if( m_MovingLeft == true )
		CameraMove( m_MovingSpeed, 0, 0 );
	
	if( m_MovingRight == true )
		CameraMove( -1 * m_MovingSpeed, 0, 0 );
	
	glUniformMatrix4fv( m_UniViewMatrix, 1, GL_TRUE, ( GLfloat* )m_ViewMatrix );
	glUniformMatrix4fv( m_UniProjectMatrix, 1, GL_TRUE, ( GLfloat* )m_ProjectMatrix );
}

void
Shader::Event ( SDL_Event* event )
{
	switch( event->type ){
		case SDL_KEYDOWN:
			if( event->key.keysym.sym == SDLK_w )
				m_MovingFront = true;

			if( event->key.keysym.sym == SDLK_s )
				m_MovingBack = true;

			if( event->key.keysym.sym == SDLK_a )
				m_MovingLeft = true;
			
			if( event->key.keysym.sym == SDLK_d )
				m_MovingRight = true;

			if( event->key.keysym.sym == SDLK_KP_1 )
				m_ViewScale = 0.1;
				
			if( event->key.keysym.sym == SDLK_KP_2 )
				m_ViewScale = 0.2;
				
			if( event->key.keysym.sym == SDLK_KP_3 )
				m_ViewScale = 0.3;
				
			if( event->key.keysym.sym == SDLK_KP_4 )
				m_ViewScale = 0.4;
				
			if( event->key.keysym.sym == SDLK_KP_5 )
				m_ViewScale = 0.5;
				
			break;

		case SDL_KEYUP:
			if( event->key.keysym.sym == SDLK_w )
				m_MovingFront = false;

			if( event->key.keysym.sym == SDLK_s )
				m_MovingBack = false;

			if( event->key.keysym.sym == SDLK_a )
				m_MovingLeft = false;
			
			if( event->key.keysym.sym == SDLK_d )
				m_MovingRight = false;
			break;

		case SDL_MOUSEMOTION:
			if( event->motion.xrel != 0 )
				CameraRotateZ( m_ViewMatrix, event->motion.xrel / 200.0 );

			if( event->motion.yrel != 0 )
				CameraRotateX( m_ViewMatrix, event->motion.yrel / 200.0 );
			break;

		case SDL_MOUSEWHEEL:
			if( event->wheel.y > 0 )
				m_ViewAngle += 0.005;
			else if( event->wheel.y < 0 && m_ViewAngle - 0.005 > 0 )
				m_ViewAngle -= 0.005;
			else
				m_ViewAngle = 0;
			break;
	}
}

void
Shader::CameraMove ( float x = 0, float y = 0, float z = 0 )
{
	m_ViewMatrix[ 0 ][ 3 ] += x;
	m_ViewMatrix[ 1 ][ 3 ] += y;
	m_ViewMatrix[ 2 ][ 3 ] += z;
}

void
Shader::CameraRotateZ( float matrix[ 4 ][ 4 ], float degree )
{
	//Tmp use to recored the result of operation
	float tmp[ 4 ][ 4 ];
	float rotateMatrix[ 4 ][ 4 ] = {
		{     cos( degree ), 0, sin( degree ), 0 },
		{                 0, 1,             0, 0 },
		{-1 * sin( degree ), 0, cos( degree ), 0 },
		{                 0, 0,             0, 1 }
	};

	//Matrix multiplication
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ){

			float sum = 0;
			for( int k = 0; k < 4; k++ )
				sum += rotateMatrix[ i ][ k ] * m_ViewMatrix[ k ][ j ];

			tmp[ i ][ j ] = sum;
		}

	//Read back the result
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			m_ViewMatrix[ i ][ j ] = tmp[ i ][ j ];
}

void
Shader::CameraRotateX( float matrix[ 4 ][ 4 ], float degree )
{
	//Tmp use to recored the result of operation
	float tmp[ 4 ][ 4 ];
	float rotateMatrix[ 4 ][ 4 ] = {
		{ 1,             0,                 0, 0 },
		{ 0, cos( degree ),-1 * sin( degree ), 0 },
		{ 0, sin( degree ),     cos( degree ), 0 },
		{ 0,             0,                 0, 1 }
	};

	//Matrix multiplication
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ){

			float sum = 0;
			for( int k = 0; k < 4; k++ )
				sum += rotateMatrix[ i ][ k ] * matrix[ k ][ j ];

			tmp[ i ][ j ] = sum;
		}

	//Read back the result
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			matrix[ i ][ j ] = tmp[ i ][ j ];
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

void
Shader::SetColorMask ( bool r, bool g, bool b, bool a )
{
	glColorMask( r, g, b, a );
}

void
Shader::SetPerspective ( float width, float height, float near, float far )
{
	m_ProjectMatrix[ 0 ][ 0 ] = width;	//Width of projection plane
	m_ProjectMatrix[ 1 ][ 1 ] = height;	//Height of projection plane
	m_ProjectMatrix[ 2 ][ 2 ] = ( far + near ) / ( near - far );
	m_ProjectMatrix[ 2 ][ 3 ] =-1.0;
	m_ProjectMatrix[ 3 ][ 2 ] = ( 2.0 * far * near ) / ( near - far ); 
}

void
Shader::SetRight ()
{
	float rightView[ 4 ][ 4 ];
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			rightView[ i ][ j ] = m_ViewMatrix[ i ][ j ];

	rightView[ 0 ][ 3 ] += m_ViewScale; 

	CameraRotateZ( rightView, m_ViewAngle );

	glUniformMatrix4fv( m_UniViewMatrix, 1, GL_TRUE, ( GLfloat* )rightView );
}

void
Shader::SetLeft ()
{
	float leftView[ 4 ][ 4 ];
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			leftView[ i ][ j ] = m_ViewMatrix[ i ][ j ];

	leftView[ 0 ][ 3 ] -= m_ViewScale; 

	CameraRotateZ( leftView, -1 * m_ViewAngle );

	glUniformMatrix4fv( m_UniViewMatrix, 1, GL_TRUE, ( GLfloat* )leftView );
}
