﻿#include <iostream>

#include <SDL.h>
#include "glew.h"
#include <fstream>
#include <string>

#include "Window.h"
#include "Color.h"
#include "BaseScene.h"
#include "SceneManagement.h"
using namespace std;

int main(int argc, char* argv[])
{
	//Creating a new window w/ dimensions and background color (optional) 
	Window window(540.0f, 540.0f, Color(0.0f, 0.0f, 0.2f, 1.0f));

	//Use a SceneID (see SceneManagement.h) to quickly setup the correct scene for the build!
	Scene* scene = SceneSelector(MIP_MAP);
	if (scene == nullptr) return 1; //Scene doesn't exist yet

<<<<<<< Updated upstream
	//Preparing shaders, shader programs, vao and vbo
	scene->SetupScene();
=======
	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);


	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	glEnable(GL_DEPTH_TEST);


	glDepthFunc(GL_LESS);




	//Describe the shape by its vertices
	
	/*
	float vertice[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	*/

	float vertice[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

		 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f

		// -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		// 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f

	};


	/*
	float vertices[] = {
	0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	*/

	//Create an ID to be given at object generation

	unsigned int vbo;


	//Pass how many buffers should be created and the reference of the ID to get the value set

	glGenBuffers(1, &vbo);

	string vs = LoadShader("equalVertex.shader");

	const char* vertexShaderSource = vs.c_str();

	string fs = LoadShader("equalFragment.shader");

	const char* fragmentShaderSource = fs.c_str();

	unsigned int vertexShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);


	//now that we have a vertex shader, let’s put the code text inside

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);


	//aaaaand… Compile !

	glCompileShader(vertexShader);


	//Do the same with the fragment shader !

	unsigned int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShader);



	unsigned int shaderProgram;

	shaderProgram = glCreateProgram();




	//now attach shaders to use to the program

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);


	//and link it 

	glLinkProgram(shaderProgram);




	//Create one ID to be given at object generation
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glUseProgram(shaderProgram);


	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);


	// Position attribute

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	// Color attribute

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);






	//Enable my vertex attrib array number 0 (we only have one attribute of position)

	//glEnableVertexAttribArray(0);
>>>>>>> Stashed changes


	//Loop that keeps the window alive
	bool isRunning = true;
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			//If the user tries to quit the window, stop execution
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
			scene->HandleInputs(event);
		}
<<<<<<< Updated upstream
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//Drawing the shapes and filling the buffer
		scene->UpdateScene();
		//Swap the buffers --> Display the newly computed one, hide the one displayed last frame
		window.Update();
=======

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		//Shader to use next

			//now that the program is complete, we can use it 

	// Get the time in seconds 

		/*float timeValue = (float)SDL_GetTicks() / 1000;

		float redColor = (sin(timeValue) / 2.0f) + 0.5f;

		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, redColor, 1.0f, 0.0f, 1.0f);*/

		
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		float timeValue = (float)SDL_GetTicks() / 1000;

		float move = (sin(timeValue) / 2.0f) + 0.05f;

		//float x = 0.5f;

		float h_offset = glGetUniformLocation(shaderProgram, "h_offset");

		glUniform1f(h_offset, move);

		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, 1.0, 0.0, 1.0, 1.0f);

		//VAO to use next
		glBindVertexArray(vao);


		//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
		//We draw from vertex 0 and we will be drawing 3 vertices

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*
		glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 0.0);
		
		glVertex3f(-0.4, 0.5, 0.0);
		glVertex3f(-0.1, -0.2, 0.0);
		glVertex3f(-0.05, 0.3, 0.0);
	
		glEnd();

		
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0,1.0,0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);

		glEnd();
		*/



		SDL_GL_SwapWindow(Window); // Swapbuffer
>>>>>>> Stashed changes

	}
	
	// Quit
	window.Close();


	return 0;
}

