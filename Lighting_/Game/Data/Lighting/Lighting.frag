#version 120
#define LIGHT_NUM 6


struct Light
{
	vec3 pos;
	float range;
	vec3 color;
	int on;
};

vec3 CalculatingLight(Light light, vec3 MaterialColor, vec3 SurfacePos, vec3 Normal, vec3 CameraPos)
{
	

	vec3 lightColor = light.color;
	
	float SpotLightAngle = 120.0;
	float fallOffaffectValue = 0.25;
	vec3 Light = vec3(MaterialColor.x * lightColor.x, MaterialColor.y * lightColor.y, MaterialColor.z * lightColor.z);
	
	// the vector point from the surface point to the light point
	vec3 dirToLight=light.pos-SurfacePos;
	float dist = length(dirToLight);
	
	// Normalize 
	vec3 dirToLightNormal = normalize(dirToLight);
	Normal = normalize(Normal);
	float diffusePercentage = dot(Normal, dirToLightNormal);

	// one way for calculating diffuse part
	//const float k1=0.1;
	//const float k2=0.2;
	//const float k3=0.5;
	//vec3 result = Light * diffusePercentage /(k1 * dist *dist + k2 * dist + k3); 

	//second way for calculating diffuse part
	float attenuation = max( 0 , pow( (1 - dist/light.range) , fallOffaffectValue)) ;
	//float attenuation = 0;
	vec3 result = Light * diffusePercentage * attenuation;

	//specular calculation
	vec3 dirToCamera = CameraPos - SurfacePos;
	vec3 dirToCameraNormal = normalize(dirToCamera);
	vec3 dirToVirtualLight = dirToCameraNormal + dirToLightNormal;
	vec3 dirToVirtualLightNormal = normalize(dirToVirtualLight);
	float specularPercentage = dot(Normal , dirToVirtualLightNormal);
	//clamp percentage
	specularPercentage = max(0,specularPercentage);
	result += pow(specularPercentage,SpotLightAngle) * lightColor * attenuation;

	

	return result;
}


varying vec3 v_Surface_WorldPos;

varying vec3 v_Normal;


uniform vec3 u_CameraWorldPos;

uniform Light u_Light[LIGHT_NUM];

varying vec2 v_UV;

uniform sampler2D u_Texture;

//uniform int u_LightNum;

void main()
{
//	Light u_Light[6];
//	for(int i=0;i<6;i++)
//	{
//		vec3 offset = vec3(10,0,0);
//		u_Light[i].pos = vec3(0,1,0) + offset * i;
//		u_Light[i].range = 35.0f;
//	}

	vec3 textureColor = vec3(texture2D(u_Texture,v_UV)) ;

	vec3 RedMaterial = vec3(1,0,0);
	vec3 GreenMaterial = vec3(0,1,0);
	vec3 result=vec3(0,0,0);
	for(int i=0;i<LIGHT_NUM;i++)
	{
		if(u_Light[i].on==1)
		result+=CalculatingLight(u_Light[i], textureColor, v_Surface_WorldPos,v_Normal,u_CameraWorldPos);

	}
	gl_FragColor=vec4(result,1);
}
