#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;



varying vec2 v_UV;

void main()
{
	//we need -1 to 1 in clip space, mesh for box is -0.5 to 0.5, so just * 2
	vec4 objectPos = vec4( a_Position*2 , 1 );


    gl_Position = objectPos;

	v_UV = a_UV ;
}
