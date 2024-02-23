#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* window;

// Mira abajo del todo jaja, esto es como el .h
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


/*
Inicializamos openGL, la libreria glfw y creamos una ventana
*/
void inicializar()
{

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "> Error al cargar la libreria" << std::endl;

	}

	// Ehh no se, creo que es para avisara de la version que tengo
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "> Error al iniciar la ventana" << std::endl;
		glfwTerminate();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// Cargar GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "> Error GLAD - Problemas al cargar los punteros de funcion de openGL" << std::endl;
		glfwTerminate();
	}

}

/*
Limpiamos los 2 buffers.
Front buffer y back buffer.
El front buffer es el que muestra por pantalla
El back buffer es el que renderiza.
El Render hace esto, pinta esto otro y tal, una vez acaba se intercambian.
El render pasa a ser el buffer que se muestra y el otro pasa a ser el que calucla.


Es como si te enseño un dibujo y por detras voy pintando el siguiente.
*/
void buffers()
{
	// Le decimos que para limpiar la pantalla ponga este color:
	glClearColor(0.3f, 0.1f, 0.6f, 1.0f);

	/* Limpiamos la pantalla */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();


}

int main(void)
{
	std::cout << "#### INICIO PROGRAMA ####" << std::endl;
	inicializar();

	/*Shaders, El chico dice que esto se suele meter em un archivo aparte*/
	// Esto es opengl script o algo asi
	const char* vertexShaderSrc = 
		"#version 400 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\0";

	// Ni zorra, el color del triangulo se define aqui
	const char* fragmentShaderSrc = 
		"#version 400 core\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"    fragColor = vec4(0.0f, 1.0, 1.0f, 1.0f);\n"
		"}\0";


	/*
	El fragment es toda la informacion necesaria para que OpenGl renderice cada pixel
	
	Esto contiene cosas del rollo luces, sombras, el color de la luz.
	Con esta info sabe como pintar el pixel
	*/

	// Le pasamos cositas al opengl
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, 0);

	// Ahora compilamos el vertex shader
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
		std::cout << "> Error al compilar el vertex shader!\n\tERR " << infoLog << std::endl;
	}

	// Ahora compilamos el fragmentShader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, 0);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
		std::cout << "> Error al compilar el fragment shader!\n\tERR " << infoLog << std::endl;
	}

	// No entiendo muy bien pero como que le decimos al programa que usar?
	// Rollo arriba lo creamos y compilamos y ahora lo linkamos con el programa principal? No veo cambios visuales jaja
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Y ahora lo linkamos que es como decir que lo compile
	// Intenta compilarlo
	glLinkProgram(shaderProgram);
	// Mira si hay algo mal
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cout << "> Error al linkar el shaderProgram!\n\tERR " << infoLog << std::endl;
	}

	// Como ya estan compilados y linkados no los necesitamos mas. Los eliminamos para liberar recursos
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Si pulsas escape ce cierra la venana
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		buffers();


	}

	glfwTerminate();
	return 0;
}

// Eeeh mira esto l hago por que lo he aprendido jajaja, para crear funcines abajo, uso encima del main
// como si fuera la cabecera.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ 
	std::cout << "El tamaño de la pantalla es: " << width << "x" << height << std::endl;
	// Actualizamos el viewport. Es decir le decimos a opengl cual es su area de render
	glViewport(0, 0, width, height);
}

/*
https://www.youtube.com/watch?v=e1i_a68CgYE
*/