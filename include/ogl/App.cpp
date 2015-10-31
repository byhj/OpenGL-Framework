#include "App.h"


namespace byhj
{
namespace ogl
{


std::shared_ptr<App> App::app;

bool gLookAtOther = true;

void App::Run(std::shared_ptr<App> the_app)
{	
	app = the_app;

	double time = 0, dt;// Current time and enlapsed time
	double turn = 0;    // Model turn counter
	double speed = 0.3; // Model rotation speed
	int wire = 0;       // Draw model in wireframe?
	float bgColor[] ={ 0.1f, 0.2f, 0.4f };         // Background color 
	unsigned char cubeColor[] ={ 255, 0, 0, 128 }; // Model color (32bits RGBA)

    app = the_app;

	std::cout << "Starting GLFW context" << std::endl;
	if (!glfwInit()) 
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	v_InitInfo();

	//Add this to use the debug output
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, true );

	GLFWwindow *window = glfwCreateWindow(windowInfo.Width, windowInfo.Height,
		                                  windowInfo.title.c_str(), nullptr, nullptr);
	glfwSetWindowPos(window, windowInfo.posX, windowInfo.posY);
	glfwMakeContextCurrent(window);


	//glfwSetKeyCallback(window, glfw_key);
	//glfwSetCursorPosCallback(window, glfw_mouse);
	//glfwSetScrollCallback(window, glfw_scroll);

	//GLFWkeyfun is the 

	//// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	//glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
	glfwSetCursorPosCallback(window, glfw_mouse);          // - Directly redirect GLFW mouse position events to AntTweakBar
	glfwSetScrollCallback(window, glfw_scroll);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
	glfwSetKeyCallback(window, glfw_key);                         // - Directly redirect GLFW key events to AntTweakBar
	//glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);                      // - Directly redirect GLFW char events to AntTweakBar



	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}	
	glewExperimental = GL_TRUE;

	//Check the GLSL and OpenGL status 
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return ;
	}
	const GLubyte *renderer = glGetString( GL_RENDERER );  
	const GLubyte *vendor = glGetString( GL_VENDOR );  
	const GLubyte *version = glGetString( GL_VERSION );  
	const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );  
	GLint major, minor;  
	glGetIntegerv(GL_MAJOR_VERSION, &major);  
	glGetIntegerv(GL_MINOR_VERSION, &minor);  
	std::cout << "GL Vendor    :" << vendor << std::endl;  
	std::cout << "GL Renderer  : " << renderer << std::endl;  
	std::cout << "GL Version (std::string)  : " << version << std::endl;  
	std::cout << "GL Version (integer) : " << major << "." << minor << std::endl;  
	std::cout << "GLSL Version : " << glslVersion << std::endl;    
	std::cout << "--------------------------------------------------------------------------------" 
		      << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); //opengl 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	v_Init();

	glViewport(0, 0, windowInfo.Width, windowInfo.Height);

	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
		//v_Movement(window);

		//Render for the object
		v_Render();



		glfwSwapBuffers(window);
	}
	v_Shutdown();


	glfwTerminate();
}

float App::GetAspect()
{
	return static_cast<float>(ScreenWidth) / static_cast<float>(ScreenHeight);
}

int App::GetScreenWidth()
{
	return ScreenWidth;
}

int App::GetScreenHeight()
{
	return ScreenHeight;
}

}

}
