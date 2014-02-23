
#include "glShaderWrapper.h"

#include <stdlib.h>
#include <fstream>

#include <sys/types.h>
#include <dirent.h>


#pragma mark - Private Functions

bool compileShader(GLuint *shader, GLenum type, const GLchar *source)
{
    GLint status;
    
    if (!source) {
        printf("Failed to load vertex shader");
        return false;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
            
			GLchar *log = (GLchar *)malloc(logLength);
			glGetShaderInfoLog(*shader, logLength, &logLength, log);
			printf("Shader compile log:\n%s", log);
			free(log);
		}
	}
    return status == GL_TRUE;
}

/*void loadFile()
{
    
//    // Get a reference to the main bundle
//    CFBundleRef mainBundle = CFBundleGetMainBundle();
//    // Get a reference to the file's URL
//    
//    CFStringRef name = CFSTR("template");
//    //CFStringRef CFSTR ( const char *cStr );
//    
//    CFURLRef fileURL = CFBundleCopyResourceURL(mainBundle, name, CFSTR("vsh"), NULL);
//    // Convert the URL reference into a string reference
//    CFStringRef filePath = CFURLCopyFileSystemPath(fileURL, kCFURLPOSIXPathStyle);
//    // Get the system encoding method
//    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
//    // Convert the string reference into a C string
//    const char *path = CFStringGetCStringPtr(filePath, encodingMethod);
//    
//
//    fstream f(path, fstream::in );
//    string s;
//    getline( f, s, '\0');
//    //printf("%s", s.c_str());
//    //cout << s << endl;
//    f.close();
//    
//
//    DIR *dir = opendir(".");
//    if(dir)
//    {
//        struct dirent *ent;
//        while((ent = readdir(dir)) != NULL)
//        {
//            cout << (ent->d_name);
//        }
//    }
//    else
//    {
//        cout << "Error opening directory" << endl;
//    }
    
    //CFReadStreamRef readStream = NULL;
    //CFReadStreamOpen(readStream);
}*/

#pragma mark - Init
glShaderWrapper::glShaderWrapper(const char *vshSource, const char *fshSource)
{
    // Creating a program
    program = glCreateProgram();
    
    //TODO
    /*
     Get the filepath in the bundle
     Get the string in the file
     
     Using CoreFoundation
     or C++ functions
     */
    
    // Compile shader
    if (!compileShader(&vertShader, GL_VERTEX_SHADER, vshSource))
        printf("Failed to compile vertex shader");
    
    if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, fshSource))
        printf("Failed to compile fragment shader");
    
    // Attach shader
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
}

glShaderWrapper::~glShaderWrapper()
{
    if (vertShader)
        glDeleteShader(vertShader);
    
    if (fragShader)
        glDeleteShader(fragShader);
    
    if (program)
        glDeleteProgram(program);
}

#pragma mark - Get attribute and uniforms
void glShaderWrapper::bindAttributeLocation(GLuint index, const GLchar *name)
{
    glBindAttribLocation(program, index, name);
}

bool glShaderWrapper::link()
{
    GLint status;
    
    glLinkProgram(program);
    glValidateProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        return false;
    
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);
    
    return true;
}

GLuint glShaderWrapper::attributeLocation(const char *attributeName)
{
    return glGetAttribLocation(program, attributeName);
}

GLuint glShaderWrapper::uniformLocation(const char *uniformName)
{
    return glGetUniformLocation(program, uniformName);
}

void glShaderWrapper::use()
{
    glUseProgram(program);
}

void glShaderWrapper::validate()
{
    GLint logLength;
	
	glValidateProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar *)malloc(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, log);
		printf("Program validate log:\n%s", log);
		free(log);
	}
}


