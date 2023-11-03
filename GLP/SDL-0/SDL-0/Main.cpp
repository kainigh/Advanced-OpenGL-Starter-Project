#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream>
#include <string>


using namespace std;
//#define GLEW_STATIC


string LoadShader(string fileName);


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 800;
	int height = 600;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


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
	
	float vertices[] = {
		//Triangle
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		 //Upside down triangle Coordinates
		 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f

		
	};
	

	float quad[] = {
	 //Quad Coordinates
		 -0.5f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f,

		 0.5f, -0.5, 0.0f, 1.0f, 0.0f, 0.0f,

		 0.5f, 0.5, 0.0f, 1.0f, 0.0f, 0.0f,

		 -0.5f, 0.5, 0.0f, 1.0f, 0.0f, 0.0f,

	};


	//Create an ID to be given at object generation
	

	string vs = LoadShader("equalVertex.shader");

	const char* vertexShaderSource = vs.c_str();

	string fs = LoadShader("equalFragment.shader");

	const char* fragmentShaderSource = fs.c_str();


	string vs2 = LoadShader("simpleVertex.shader");

	const char* vertexShaderSource2 = vs2.c_str();

	string fs2 = LoadShader("simpleFragment.shader");

	const char* fragmentShaderSource2 = fs2.c_str();



	unsigned int vertexShader, vertexShader2;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);




	//now that we have a vertex shader, let’s put the code text inside

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);



	//aaaaand… Compile !

	glCompileShader(vertexShader);
	glCompileShader(vertexShader2);



	//Do the same with the fragment shader !

	unsigned int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShader);



	unsigned int shaderProgram;

	shaderProgram = glCreateProgram();



	unsigned int fragmentShader2;

	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);

	glCompileShader(fragmentShader2);



	unsigned int shaderProgram2;

	shaderProgram2 = glCreateProgram();



	//now attach shaders to use to the program

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glAttachShader(shaderProgram2, vertexShader2);
	glAttachShader(shaderProgram2, fragmentShader2);


	//and link it 

	glLinkProgram(shaderProgram);
	glLinkProgram(shaderProgram2);



	//Create one ID to be given at object generation
	unsigned int vao, vbo;
	unsigned int vao2, vbo2;
	glGenVertexArrays(2, &vao);
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(2, &vbo);

	glGenVertexArrays(2, &vao2);
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(2, &vbo2);

	
	glBindVertexArray(vao);
	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	


	glBindVertexArray(vao2);
	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glUseProgram(shaderProgram);	


	// Color attribute

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);

	//Enable my vertex attrib array number 0 (we only have one attribute of position)

	//glEnableVertexAttribArray(0);


	bool isRunning = true;

	while (isRunning) {

		// Inputs

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_QUIT:

				isRunning = false;

				break;

			default:

				break;

			}

		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		//Shader to use next

			//now that the program is complete, we can use it 

	// Get the time in seconds 

		/*float timeValue = (float)SDL_GetTicks() / 1000;

		float redColor = (sin(timeValue) / 2.0f) + 0.5f;

		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, redColor, 1.0f, 0.0f, 1.0f);*/


		glUseProgram(shaderProgram);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		float timeValue = (float)SDL_GetTicks() / 1000;

		float move = (sin(timeValue) / 2.0f) + 0.05f;

		
		float h_offset = glGetUniformLocation(shaderProgram, "h_offset");

		glUniform1f(h_offset, move);


		

		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 1.0f, 1.0f);

		//VAO to use next
		glBindVertexArray(vao);

		//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
		//We draw from vertex 0 and we will be drawing 3 vertices

		glDrawArrays(GL_TRIANGLES, 0, 6);


		glUseProgram(shaderProgram2);

		glBindVertexArray(vao2);
		glDrawArrays(GL_QUADS, 0, 4);

		

		SDL_GL_SwapWindow(Window); // Swapbuffer


	}

	// Quit

	SDL_DestroyWindow(Window);

	SDL_GL_DeleteContext(Context);





	//cin.get();
	return 0;
}

string LoadShader(string fileName) {

	ifstream myFile;

	myFile.open(fileName);

	if (myFile.fail()) {

		cerr << "Error - failed to open " << fileName << endl;

	}

	string fileText = "";

	string line = "";

	while (getline(myFile, line)) {

		fileText += line + '\n';

	}



	myFile.close();

	return fileText;



}