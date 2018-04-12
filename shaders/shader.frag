#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(std140, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
    vec3 camPos;
    vec3 camUp;
} ubo;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec3 pos;

layout(location = 0) out vec4 outColor;

float saturate(float x) 			{ return clamp(x, 0.0, 1.0); }

void main() 
{
	vec3 Ld = normalize(ubo.camUp + vec3(1, 2, 3)); // some random offset

    vec3 N = normalize(cross(dFdy(pos), dFdx(pos)));
    vec3 V = normalize(ubo.camPos - pos);
    vec3 H = normalize(V + Ld);

	float n_dot_l = saturate( dot(N, Ld) );
	float n_dot_h = saturate( dot(N, H) );

    float diffuse = n_dot_l;
    float spec = pow(n_dot_h, 8);
    
    outColor.rgb = fragColor.rgb * (diffuse + 0.5) * 0.5 + vec3(0.1, 0.1, 0.1) * spec;

    // gamma correction
    float gamma = 2.2;
    outColor.rgb = pow(outColor.rgb, vec3(1.0 / gamma));
    outColor.a = fragColor.a;
}
