#ifndef __OpenglESLibrary__glShaderWrapper__
#define __OpenglESLibrary__glShaderWrapper__

#include <iostream>
using namespace std;

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

class glShaderWrapper
{
public:
    glShaderWrapper(const char *vshSource, const char *fshSource);
    ~glShaderWrapper();
    
    void bindAttributeLocation(GLuint index, const GLchar *name);
    
    bool link();

    GLuint attributeLocation(const char *attributeName);
    GLuint uniformLocation(const char *uniformName);
    
    void use();

    //TODO: Log risults
    /*
    const char *vertexShaderLog();
    const char *fragmentShaderLog();
    const char *programLog;
    
    */
    void validate();

private:
    GLuint program, vertShader, fragShader;
};

#endif