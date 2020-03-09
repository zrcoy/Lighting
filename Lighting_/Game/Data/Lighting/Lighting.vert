#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_RotateMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec3 v_Normal;

varying vec3 v_Surface_WorldPos;

varying vec2 v_UV;

//varying vec2 v_UV;

void main()
{
	vec4 objectPos = vec4( a_Position, 1.0 );
	vec4 worldPos = u_WorldMatrix * objectPos;
    v_Surface_WorldPos=vec3(worldPos.x,worldPos.y,worldPos.z);

	vec4 viewPos = u_ViewMatrix * worldPos;
	vec4 clipPos = u_ProjectionMatrix * viewPos;
	
    gl_Position = clipPos;

	//v_UV = a_UV * u_UVScale + u_UVOffset;

	vec4 Normal = vec4(a_Normal,0);

	Normal = u_RotateMatrix * Normal;

	v_Normal=vec3(Normal.x,Normal.y,Normal.z);
	v_UV = a_UV;
}
