#include <iostream>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;
/*
Inicializamos openGL, la libreria glfw y creamos una ventana
*/
void inicializar()
{

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "> Error al cargar la libreria" << std::endl;

	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "> Error al iniciar la ventana" << std::endl;
		glfwTerminate();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

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
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();


}

int main(void)
{
	inicializar();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		buffers();


	}

	glfwTerminate();
	return 0;
}