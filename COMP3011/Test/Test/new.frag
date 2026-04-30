#version 450 core


#define MAX_LIGHTS 20

layout (location = 0) out vec4 fColour;

in vec3 nor;
in vec3 FragPosWorldSpace;
in vec2 TexCoord;

uniform vec3 lightDirection;
uniform vec3 lightColour[MAX_LIGHTS];

uniform vec3 lightPos[MAX_LIGHTS];

uniform int lightType[MAX_LIGHTS];

uniform int numLights;

uniform vec3 camPos;

uniform sampler2D texture1;

uniform sampler2D shadowMap;

in vec4 fragPosLight;

vec3 phong;
float ambient;
float diffuse;
float specular;

vec3 CalculateSpotIllumination(vec3 pos, vec3 col) {

	ambient = 0.5f; 

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(pos - FragPosWorldSpace);
	diffuse = max(dot(Nnor, Nto_light), 0);

	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);

	vec3 camDirection = camPos - FragPosWorldSpace;

	vec3 NcamDirection = normalize(camDirection);

	specular = max(dot(NcamDirection, NrefLight), 0);


	float attenuation = 1 / (1.f + (0.05f * length(FragPosWorldSpace - pos)) + (0.002f * pow(length(FragPosWorldSpace - pos), 2)  )); 

	float phi = cos(radians(15.0f));

	vec3 NSpotDir = normalize(lightDirection);

	float theta = dot(Nfrom_light, NSpotDir);

	float shadow = 0.0f;
	vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
	if (lightCoords.z <= 1.0f) {
		lightCoords = (lightCoords + 1.0f) /2.0f;

		float closestDepth = texture(shadowMap, lightCoords.xy).r;
		float currentDepth = lightCoords.z;

		float bias = 0.005f;
		if (currentDepth > closestDepth + bias) {
			shadow = 1.0f;
		}
	}



	if (theta > phi) {
		return ((ambient + diffuse * (1.0f-shadow) + specular * (1.0f-shadow)) * col * attenuation);
	}
	else {
		return ambient * attenuation * col;
	}

	
}

vec3 CalculatePositionalIllumination(vec3 pos, vec3 col) {

	ambient = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(pos - FragPosWorldSpace);
	diffuse = max(dot(Nnor, Nto_light), 0);



	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	specular = max(dot(NcamDirection, NrefLight), 0);


	float attenuation = 1 / (1.f + (0.05f * length(FragPosWorldSpace - pos)) + (0.002f * pow(length(FragPosWorldSpace - pos), 2)  )); 

	return ((ambient + diffuse + specular) * col * attenuation);
	
}


vec3 CalculateLighting() {

	//ambient = 0.1f;

	vec3 totLight = vec3(0.0f);


	for (int i = 0; i < numLights; ++i) {

		if (lightType[i] == 0) {
			totLight +=  CalculatePositionalIllumination(lightPos[i], lightColour[i]);
		}
		else if (lightType[i] == 1) {
			totLight +=  CalculateSpotIllumination(lightPos[i], lightColour[i]); 
		}
		
	}

	

	return totLight;
}

void main()
{
    phong = CalculateLighting();

	
	vec4 texColour = texture(texture1, TexCoord);

    fColour = texColour * vec4(phong , 1.0f); 
}