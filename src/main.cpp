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
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
};
const 
std::string getShader(const char* filePath )
{
    std::fstream stream;
    std::stringstream ss;
    std::string line;

    stream.open(filePath);
    while(getline(stream, line ))
    {
        ss << line << '\n';
        
    }
    std::cout<<ss.str() << '\n';
    ss.str();
   
    //stream.close();
    return ss.str();;
}

GLint result = GL_FALSE;
/* Our program's entry point */
int main()
{
    //read shaders
    std::string  vsSource = getShader("../shaders/vert.shader");
    const char * vsShader = vsSource.c_str();

    std::string fsSource = getShader("../shaders/frag.shader");
    const char * fsShader = fsSource.c_str();


    SDL_Window *window; /* Our window handle */
    SDL_GLContext context; /* Our opengl context handle */


    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    /* Request opengl 4.6 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

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
   
    unsigned int vs;
    unsigned int fs;
    unsigned int shader;

    vs = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vs, 1, &vsShader, NULL);
    
    glCompileShader(vs);
     

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsShader, NULL);
    glCompileShader(fs);

    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glValidateProgram(shader);

   

    glDeleteShader(vs);
    glDeleteShader(fs);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    

    SDL_Event event;
    bool running = true;

    glBindVertexArray(VAO);

       std::cout<<"error: " << glGetError()<< "\n";

    glUseProgram(shader);
     
 
    
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
    
        /* Clear our buffer with a red background */
    //glClearColor ( 1.0, 0.0, 0.0, 1.0 );

        glClear ( GL_COLOR_BUFFER_BIT );

        
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        


        // /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
           
