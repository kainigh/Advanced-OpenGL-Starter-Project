#version 330 core
in vec3 pos;
uniform mat4 mv_matrix;
uniform mat4 projection;

out VS_OUT{
vec4 color;
} vs_out;

void main()
{
    gl_Position =  projection * mv_matrix * vec4(pos, 1.0);
    vs_out.color = vec4((pos*2.0f)+1.0f, 1.0);
}