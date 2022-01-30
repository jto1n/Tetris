#ifndef SHADER_H
#define SHADER_H

class Shader
{
    public :
        Shader(const char *, const char * );
        ~Shader();
        unsigned int compile();
        void bind();
        void remove();

    private:
        unsigned int vs;
        unsigned int fs;
        unsigned int shader;
        std::string loadShader(const char*);

};



#endif