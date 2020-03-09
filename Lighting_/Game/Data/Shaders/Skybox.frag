#version 130

varying vec3 v_textureDir;// direction vector representing a 3D texture coordinate

uniform samplerCube u_Skybox;//cubemap texture sampler

void main()
{

	gl_FragColor = texture(u_Skybox,v_textureDir);

	


}
