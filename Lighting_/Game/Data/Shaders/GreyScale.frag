#version 120

uniform sampler2D u_Texture;

varying vec2 v_UV;

void main()
{
	vec4 outColor = vec4(1.0,1.0,1.0,1.0) - texture2D( u_Texture, v_UV );

	//greyscale
	outColor = texture2D(u_Texture,v_UV);
	float avg = (outColor.r + outColor.g + outColor.b)/ 3.0;
	outColor = vec4(avg, avg, avg, 1);

	// better with weighed channels
//	outColor = texture(texFramebuffer, Texcoord);
//	float avg = 0.2126 * outColor.r + 0.7152 * outColor.g + 0.0722 * outColor.b;
//	outColor = vec4(avg, avg, avg, 1.0);
	gl_FragColor = outColor;
}
