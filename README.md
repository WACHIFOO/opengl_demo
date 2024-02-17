# opengl_demo
## Tutoriales seguidos:
https://www.youtube.com/watch?v=uO__ntYT-2Q

https://learnopengl.com/book/book_pdf.pdf

## Pasos:
- Actualiza los drivers de la grafica
- De la web de GLFW descargate el binario para windows.
- Crea los siguientes directorios y pega los archivos del binario dentro:
  - C:/c++/__librerias/OpenGL/includes/GLFW
    - glfw3.h
    - glfw3native.h
  - C:/c++/__librerias/OpenGL/lib
    - glfw3.lib 
- Ahora desde el VisualStudio entra a properties y:
  -C/C++ -> General -> Additional Include Directories -> Pega la ruta de **Includes**
  - Linker -> General -> Additional Include Directories ->  Pega la ruta de **Lib**
  - Linker -> Inout -> Additional Dependences -> Pega lo siguiente:
    - glfw3.lib
    - opengl32.lib
    - user32.lib
    - gdi32.lib
    - shell32.lib
- Ahora en el codigo pega el siguiente codigo. Si todo va bien se te debería abrir un terminal y una ventana pequeña que pone Hello World

```
/* Includes */
#include <GLFW/glfw3.h>
int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```
