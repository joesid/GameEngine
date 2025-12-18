#include<stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

int main() {

	// initialize GLFW Library
	if (!glfwInit())
	{
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "WorldEngine", nullptr, nullptr); // Create Window

	if (window == nullptr) // Check if Window was successfully created
	{
		std::cout << "Error creating window" << std::endl;
		glfwTerminate();  //Clean GLFW Library
		return -1;

	}

	glfwSetWindowPos(window, 2000, 150);
	glfwMakeContextCurrent(window);

	//Initialize GLEW Library to make use of OpenGL Functions
	if (glewInit() != GLEW_OK) 
	{
		glfwTerminate();
		return -1;
	}

	std::string vertexShaderSource = R"(
         #version 330 core
         layout (location = 0) in vec3 position;
         layout (location = 1) in vec3 color;
       
         out vec3 vColor;

         void main()
          {
            vColor = color;
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
          }
     )";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderCstr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderCstr, nullptr);
	glCompileShader(vertexShader);

	GLint success;  //Check if shader Compilation is successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
	}

	std::string fragmentShaderSource = R"(
         #version 330 core
         out vec4 FragColor;
         
         in vec3 vColor;

         void main()
         { 
           FragColor = vec4(vColor, 1.0);
         }
)";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
	 }

     //Create Object for the Shader program in the Graphics Card
	 GLuint shaderProgram = glCreateProgram();
	 glAttachShader(shaderProgram, vertexShader);
	 glAttachShader(shaderProgram, fragmentShader);
	 glLinkProgram(shaderProgram);

	 glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	 if (!success)
	 {
		 char infoLog[512];
		 glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		 std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
	 }

	 glDeleteShader(vertexShader);
	 glDeleteShader(fragmentShader);

	 //Draw Rectange - Vector Positions
	 std::vector<float> vertices =
	 {
		  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f,
		  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};
	

	 std::vector<unsigned int> indices =
	 {
		 0,1,2,
		 0,2,3
	 };

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Transfer Buffer Data from the System memory into the GPU memory
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.6f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate Shader program
		glUseProgram(shaderProgram);

		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}