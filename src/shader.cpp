#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"


Shader::Shader(const char * vsFile, const char * fsFile)
{
    std::string  vsSource = loadShader(vsFile);
    const char * vsShader = vsSource.c_str();

    std::string fsSource = loadShader(fsFile);
    const char * fsShader = fsSource.c_str();

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsShader, NULL);
    glCompileShader(vs);
     
    //frag shader compile
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsShader, NULL);
    glCompileShader(fs);


}
Shader::~Shader()
{

}

std::string Shader::loadShader(const char* filePath)
{
    std::fstream stream;
    std::stringstream ss;
    std::string line;

    stream.open(filePath);
    while(getline(stream, line ))
    {
        ss << line << '\n';
        
    }
    ss.str();
   
    //stream.close();
    return ss.str();
}

unsigned int Shader::compile()
{
    shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glValidateProgram(shader);

    return shader;
}

void Shader::remove()
{
    glDeleteShader(vs);
    glDeleteShader(fs);
}