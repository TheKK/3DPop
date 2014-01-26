/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * object.cpp
 *
 */

#include "object.h"

Object::Object ( float x = 0, float y = 0, float z = 0 )
{
	//Initialize model matrix
	for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ){
			if( i == j )
				m_ModelMatrix[ i ][ j ] = 1;
			else
				m_ModelMatrix[ i ][ j ] = 0;
		}

	SetPosition( x, y, z );
}

Object::~Object ()
{
	CleanUp();
}

void
Object::Draw ()
{
	//Change to shader program we set
	glUseProgram( m_ShaderProgram );

	//Bind our array setting
	glBindVertexArray( m_VAO );

	glUniformMatrix4fv( m_UniModelMatrix, 1, GL_TRUE, ( GLfloat* )m_ModelMatrix );

	//Draw
	glDrawElements( GL_TRIANGLES, m_ElementNum, GL_UNSIGNED_INT, 0 );
}

void
Object::Event ( SDL_Event* event )
{
	switch( event->type ){
		case SDL_KEYDOWN:
			break;
	}
}

void
Object::Move( float x, float y, float z )
{
	m_ModelMatrix[ 0 ][ 3 ] += x;
	m_ModelMatrix[ 1 ][ 3 ] += y;
	m_ModelMatrix[ 2 ][ 3 ] += z;
}

void
Object::SetPosition( float x, float y, float z )
{
	m_ModelMatrix[ 0 ][ 3 ] = x;
	m_ModelMatrix[ 1 ][ 3 ] = y;
	m_ModelMatrix[ 2 ][ 3 ] = z;
}

void
Object::SetShader ( GLuint shaderProgram )
{
	m_ShaderProgram = shaderProgram;

	//Get uniform location in GLSL
	m_UniModelMatrix = glGetUniformLocation( m_ShaderProgram, "M" );
}

bool
Object::LoadOBJ ( char* path )
{
	//Contain data from .obj file
	vector<GLfloat> vertex;
	vector<GLfloat> normal;
	vector<GLuint> element;

	if( OBJConvert( path, vertex, normal, element ) == false )
		return false;

	//Link to our shader program
	glUseProgram( m_ShaderProgram );

	//Create new vertex array object
	glGenVertexArrays( 1, &m_VAO );
	glBindVertexArray( m_VAO );

	//Store vertex buffer object
	glGenBuffers( 1, &m_VBO );
	glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
	glBufferData( GL_ARRAY_BUFFER,
			vertex.size() * sizeof( GLfloat ),
			&vertex[ 0 ],
			GL_STATIC_DRAW
		    );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), 0 );

	//Store normal buffer object
	glGenBuffers( 1, &m_NBO );
	glBindBuffer( GL_ARRAY_BUFFER, m_NBO );
	glBufferData( GL_ARRAY_BUFFER,
			normal.size() * sizeof( GLfloat ),
			&normal[ 0 ],
			GL_STATIC_DRAW
		    );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), 0 );

	//Store element buffer object
	glGenBuffers( 1, &m_EBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,
			element.size() * sizeof( GLuint ),
			&element[ 0 ],
			GL_STATIC_DRAW
		    );

	return true;
}

bool
Object::OBJConvert ( char* path, vector<GLfloat> &vertex, vector<GLfloat> &normal, vector<GLuint> &element )
{
	//Read OBJ file and check error
	ifstream OBJSource( path, ios::in );
	if( !OBJSource.good() ){
		fprintf( stderr, "OBJ file does not exist: %s\n", path );
		return false;
	}

	//Template for each line in OBJ file
	string strTmp;
	//Normal table as same as in OBJ file
	vector<GLfloat> normalTable;
	//Contain normal indice in each face
	vector<GLfloat> normalIndice;

	float vertex_x, vertex_y, vertex_z;
	float normal_x, normal_y, normal_z;
	int vertex1, vertex2, vertex3;
	int normalIndex1, normalIndex2, normalIndex3;

	while( getline( OBJSource, strTmp ) ){
		if( sscanf( strTmp.c_str(), "v %f %f %f\n", &vertex_x, &vertex_y, &vertex_z ) ){
			vertex.push_back( vertex_x );
			vertex.push_back( vertex_y );
			vertex.push_back( vertex_z );
		}

		else if( sscanf( strTmp.c_str(), "vn %f %f %f", &normal_x, &normal_y, &normal_z ) ){
			normalTable.push_back( normal_x );
			normalTable.push_back( normal_y );
			normalTable.push_back( normal_z );
		}

		else if( sscanf( strTmp.c_str(), "f %d//%d %d//%d %d//%d", &vertex1, &normalIndex1, &vertex2, &normalIndex2, &vertex3, &normalIndex3 ) ){
			element.push_back( vertex1 - 1 );
			element.push_back( vertex2 - 1 );
			element.push_back( vertex3 - 1 );

			normalIndice.push_back( normalIndex1 - 1 );
			normalIndice.push_back( normalIndex2 - 1 );
			normalIndice.push_back( normalIndex3 - 1 );
		}
	}
	OBJSource.close();

	//Check if OBJ file broken
	if( ( vertex.size() == 0 ) || ( normalTable.size() == 0 ) || ( element.size() == 0 ) || ( normalIndice.size() == 0 ) ){
		fprintf( stderr, "OBJ file broken: %s\n", path );
		return false;
	}

	//Match normal to each vertex
	normal.resize( vertex.size(), 0 );
	for( unsigned int i = 0; i < element.size(); i++ ){
		normal[ element[i] * 3 + 0 ] += normalTable[ normalIndice[i] * 3 + 0 ];
		normal[ element[i] * 3 + 1 ] += normalTable[ normalIndice[i] * 3 + 1 ];
		normal[ element[i] * 3 + 2 ] += normalTable[ normalIndice[i] * 3 + 2 ];
	}

	m_ElementNum = element.size();

	return true;
}

void
Object::CleanUp ()
{
	glDeleteBuffers( 1, &m_VBO );
	glDeleteBuffers( 1, &m_NBO );
	glDeleteBuffers( 1, &m_EBO );

	glDeleteVertexArrays( 1, &m_VAO );
}













