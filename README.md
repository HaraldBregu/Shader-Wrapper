Shader-Wrapper
==============

C++ Shader class to use in all platforms


glShader C++ class implementation

1- Ceate vsh and fsh files (if not created yet)
2- Edit "glShaderHeader.h" for attributes and uniforms
3- Add "glShaderHeader.h" to your implementation class
4- Load sources of vertex and fragment shader

    //######## LOAD FILES OBJECTIVE-C ########//
	NSString *vshPath = [[NSBundle mainBundle] pathForResource:@"template" ofType:@"vsh"];
	const char *vshSource = [[NSString stringWithContentsOfFile:vshPath encoding:NSUTF8StringEncoding error:nil] UTF8String];
	NSString *fshPath = [[NSBundle mainBundle] pathForResource:@"template" ofType:@"fsh"];
	const char *fshSource = [[NSString stringWithContentsOfFile:fshPath encoding:NSUTF8StringEncoding error:nil] UTF8String];
    //######## LOAD FILES OBJECTIVE-C ########//

5- Create an instance of shader class "glShaderWrapper.h" and use it

    //######## LOAD SHADER ########//
    glShaderWrapper loadShader = glShaderWrapper(vshSource, fshSource);
    
    loadShader.bindAttributeLocation(ATTRIB_VERTEX, "position");    // 1
    loadShader.bindAttributeLocation(ATTRIB_COLOR, "color");        // 1
    
    loadShader.link();                                              // Link shader

    GLuint position = loadShader.attributeLocation("position");   // Optional get attribute location
    GLuint color = loadShader.attributeLocation("color");         // Optional get attribute location

    uniforms[U_MV_PROJ_MTX] = loadShader.uniformLocation("modelViewProjectionMatrix");  // Get uniform location
    
    loadShader.use();                                               // Use shader
    //######## LOAD SHADER ########//
    
    

//######################## FAST IMPLEMENTATION ###################################//

//## include "glShaderHeader.h" ##//

    //######## LOAD FILES ########//
	NSString *vshPath = [[NSBundle mainBundle] pathForResource:@"template" ofType:@"vsh"];
	const char *vshSource = [[NSString stringWithContentsOfFile:vshPath encoding:NSUTF8StringEncoding error:nil] UTF8String];
	NSString *fshPath = [[NSBundle mainBundle] pathForResource:@"template" ofType:@"fsh"];
	const char *fshSource = [[NSString stringWithContentsOfFile:fshPath encoding:NSUTF8StringEncoding error:nil] UTF8String];
    //######## LOAD SHADER ########//
    glShaderWrapper loadShader = glShaderWrapper(vshSource, fshSource);
    loadShader.bindAttributeLocation(ATTRIB_VERTEX, "position");
    loadShader.bindAttributeLocation(ATTRIB_COLOR, "color");
    loadShader.link();
    GLuint position = loadShader.attributeLocation("position"); //Optional
    GLuint color = loadShader.attributeLocation("color"); //Optional
    uniforms[U_MV_PROJ_MTX] = loadShader.uniformLocation("modelViewProjectionMatrix");
    loadShader.use();
    //######## LOAD SHADER ########//
