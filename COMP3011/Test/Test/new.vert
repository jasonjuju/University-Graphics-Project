#version 450 core

layout(location = 0) in vec3 vPos;    

layout(location = 1) in vec2 vTexCoord; 

layout(location = 2) in vec3 vNor;





uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;




out vec3 nor;
out vec3 FragPosWorldSpace;
out vec2 TexCoord;
out vec4 fragPosLight;

uniform mat4 camMatrix;


void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0); 
    //gl_Position = camMatrix * model * vec4(vPos, 1.0); 
    nor = mat3(transpose(inverse(model))) * vNor;
    FragPosWorldSpace = vec3(model * vec4(vPos, 1.0));

    TexCoord = vTexCoord;



    fragPosLight = lightSpaceMatrix* model * vec4(vPos, 1.0);
    
}