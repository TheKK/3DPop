/*

vertexShader

author: TheKK <thumbd03803@gmail.com>
date: 10/16/2013

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
	gl_Position =  vec4( ( position_modelspace ), 1.0 );

	color = normal_modelspace;
};

