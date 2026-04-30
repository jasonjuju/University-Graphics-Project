#version 450 core

layout (location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec3 FragPosWorldSpace;


uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 camPos;
uniform vec3 lightPos;


float phong;
float ambient;
float diffuse;
float specular;

float CalculateDirectionalIllumination() {


	ambient = 0.1f; 

	vec3 Nnor = normalize(nor);

	vec3 Nto_light = -(normalize(lightDirection));

	diffuse = max(dot(Nnor, Nto_light), 0);

	vec3 Nfrom_light = normalize(lightDirection);

	vec3 NrefLight = reflect(Nfrom_light, Nnor);

	vec3 camDirection = camPos - FragPosWorldSpace;

	vec3 NcamDirection = normalize(camDirection);

	specular = max(dot(NcamDirection, NrefLight), 0);

	return ambient + diffuse + specular;
}

float CalculatePositionalIllumination() {
	ambient = 0.1f; 

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace);
	diffuse = max(dot(Nnor, Nto_light), 0);



	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	specular = max(dot(NcamDirection, NrefLight), 0);



	float attenuation = 1 / (1.f + (0.05f * length(FragPosWorldSpace - lightPos)) + (0.002f * pow(length(FragPosWorldSpace - lightPos), 2)  )); 

	return (ambient + diffuse + specular) * attenuation;
}

float CalculateSpotIllumination() {

	ambient = 0.1f; 

	vec3 Nnor = normalize(nor);

	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace);

	diffuse = max(dot(Nnor, Nto_light), 0);

	vec3 Nfrom_light = -Nto_light;

	vec3 NrefLight = reflect(Nfrom_light, Nnor);

	vec3 camDirection = camPos - FragPosWorldSpace;

	vec3 NcamDirection = normalize(camDirection);

	specular = max(dot(NcamDirection, NrefLight), 0);



	float attenuation = 1 / (1.f + (0.05f * length(FragPosWorldSpace - lightPos)) + (0.002f * pow(length(FragPosWorldSpace - lightPos), 2)  )); 


	float phi = cos(radians(15.0f));

	vec3 NSpotDir = normalize(lightDirection);

	float theta = dot(Nfrom_light, NSpotDir);

	if (theta > phi) {
		return (ambient + diffuse + specular) * attenuation;
	}
	else {
		return ambient * attenuation;
	}
	
}


void main()
{
	
	phong = CalculateSpotIllumination();


	fColour = vec4(phong * col * lightColour, 1.f);

}
