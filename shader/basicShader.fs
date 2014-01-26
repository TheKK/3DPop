/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * basic.fs
 *
 */

#version 400 core

in vec3 color;

out vec4 outColor;

float Grey ( vec3 color )
{
	float grey = ( 0.2989 * color.r ) + ( 0.5870 * color.g ) + ( 0.1140 * color.b );
	return grey;
}

void main()
{
	/*outColor = vec4( Grey( color ), Grey( color ), 0.0, 1.0 );*/
	outColor = vec4( 1.0, 1.0, 1.0, 1.0 );
}
