#include <iostream>
#include <complex> 
#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include <shader.h>


//My headers
#include <plot.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 600, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Holomorph", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glEnable(GL_MULTISAMPLE);  

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);


    // Build and compile our shader program
    Shader ourShader("shaders/shader.vs", "shaders/shader.frs");

    std::complex<GLfloat> UL(0.4f, 0.4f);
    std::complex<GLfloat> BR(0.8f, 0.0f);

    plot ourPlot,frame,backPlot;
    ourPlot.loadFrame(UL,BR, 8, 8);
    backPlot=ourPlot;
    ourPlot.prepare();
    backPlot.prepare();

    // Preparing coordinate frame
    coordinate z;
    z.x=3.0;
    z.y=0.0;
    frame.vertices.push_back(z);
    z.x=-3.0;
    frame.vertices.push_back(z);
    frame.indices.push_back(frame.vertices.size()-1);
    frame.indices.push_back(frame.vertices.size()-2);
    z.x=0.0;
    z.y=3.0;
    frame.vertices.push_back(z);
    z.y=-3.0;
    frame.vertices.push_back(z);
    frame.indices.push_back(frame.vertices.size()-1);
    frame.indices.push_back(frame.vertices.size()-2);
    z.x=0.33333333333333;
    z.y=-0.050;
    frame.vertices.push_back(z);
    z.y=0.050;
    frame.vertices.push_back(z);
    frame.indices.push_back(frame.vertices.size()-1);
    frame.indices.push_back(frame.vertices.size()-2);
    frame.prepare();
    double mx_old,my_old;
     int wind=0;


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Putting time value in the vertex shader
        GLfloat timeValue = glfwGetTime();
        GLfloat t = (sin(timeValue) / 2) + 0.5;
        GLint vertextimeLocation = glGetUniformLocation(ourShader.Program, "t");
        glUniform1f(vertextimeLocation, t);


        //Putting mouse position in the vertex shader
        double mousex,mousey;       
        glfwGetCursorPos(window,&mousex,&mousey);
        mousex=(mousex-300)/300;
        mousey=(mousey-300)/300;
        if(mx_old<=0 && my_old*mousey<=0)
        {
            if(my_old>=0)
                wind-=1;
            else
                wind+=1;

        }
        mx_old=mousex;
        my_old=mousey;
        GLint mousePos = glGetUniformLocation(ourShader.Program, "mouse");
       // GLint windPos = glGetUniformLocation(ourShader.Program, "winder");
        glUniform2f(mousePos, mousex, -mousey);
      //  glUniform1i(windPos, wind);
        //printf("%d",wind);

        GLint aflag = glGetUniformLocation(ourShader.Program, "animate");
        glUniform1i(aflag,0); 

        GLint mflag = glGetUniformLocation(ourShader.Program, "mouse_flag");
        glUniform1i(mflag,1); 




        // Draw the modified plot
        ourShader.Use();
        backPlot.draw(); 
        glUniform1i(aflag,1); 
        ourPlot.draw();
        glUniform1i(mflag,0);
        glUniform1i(aflag,0);
        frame.draw(); 

       
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    ourPlot.kill();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}