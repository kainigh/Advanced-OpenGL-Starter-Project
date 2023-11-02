#version 330 core

in vec3 pos;
in vec3 color;

out vec4 ourColor;
uniform float h_offset;


void main()
{
   //gl_Position = vec4(pos.x + h_offset, pos.y, pos.z, 1.0f);

   gl_Position = vec4(pos + h_offset, 1.0f);
   ourColor = vec4(color, 1.0);

     

};
