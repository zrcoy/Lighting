#version 130

attribute vec3 a_Position;

uniform mat4 u_WorldMatrix;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

varying vec3 v_textureDir;

uniform vec3 u_CameraWorldPos;

void main()
{
	vec4 objectPos = vec4( a_Position, 1.0 );
	vec4 worldPos = u_WorldMatrix * objectPos;

	vec4 viewPos = u_ViewMatrix * worldPos;
	vec4 clipPos = u_ProjectionMatrix * viewPos;
	
    gl_Position = clipPos;

	v_textureDir = worldPos.xyz - u_CameraWorldPos;//fix the skybox 
}
