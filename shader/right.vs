/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * basic.vs
 *
 */

#version 400 core

layout( location = 0 ) in vec3 position_modelspace;
layout( location = 1 ) in vec3 normal_modelspace;

out vec3 color;

//Model matrix
uniform mat4 M;
//Viewport matrix
uniform mat4 V;
//Projection matrix
uniform mat4 P;

void main () {
	mat4 rightView = V;
	rightView[ 0 ][ 3 ] += 1;

	gl_Position = P * V * M * vec4( ( position_modelspace ), 1.0 );

	//Out
	color = normalize( normal_modelspace );
}

