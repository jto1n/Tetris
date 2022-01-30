#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.h"

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}


void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}
 
float vert[] = 
{
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};


GLint result = GL_FALSE;
/* Our program's entry point */
int main()
{



    SDL_Window *window; /* Our window handle */
    SDL_GLContext context; /* Our opengl context handle */


    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    /* Request opengl 4.6 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    
    context = SDL_GL_CreateContext(window);


    GLenum err = glewInit();
if (err != GLEW_OK)
{
    std::cout << "error: " << glewGetErrorString(err) <<  "\n";
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}


    //grabbing and compiling shaders.
    Shader shaderRaw("../shaders/vert.shader", "../shaders/frag.shader");
    unsigned int shader = shaderRaw.compile();
    shaderRaw.remove();




    //creating vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    

    //creating vertex buffer object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);



    //creating index buffer
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    

    SDL_Event event;
    bool running = true;

    glBindVertexArray(vao);

       std::cout<<"error: " << glGetError()<< "\n";

    glUseProgram(shader);
     
 
    //main while loop for program.
    while(running)
    {
        
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;

            }

        }
    
        /* Clear our buffer with a blue background*/
        glClearColor ( 0.0, 0.5, 1.0, 1.0 );

        glClear ( GL_COLOR_BUFFER_BIT );

        
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);



        // /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
           
