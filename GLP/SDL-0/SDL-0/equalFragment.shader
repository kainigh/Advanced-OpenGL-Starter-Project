#version 330
out vec4 FragColor;

in vec4 ourColor;

in vec4 vert_pos;

void main()
{	

	//FragColor = ourColor;

	FragColor = vert_pos;

}