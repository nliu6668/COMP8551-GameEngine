#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "engine.h"

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "vertexBufferLayout.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// screen res
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    Engine& e = Engine::getInstance();

    entityx::Entity entity3 = e.entities.create();
    entity3.assign<Position>(
        -50.0f,  -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f,

        0,1,2,
        2,3,0
    );

    entity3.assign<ShaderComp>("src/res/shaders/Basic.shader");
    entity3.assign<TextureComp>("src/res/textures/tile_0028.png");
    entity3.assign<Translation>(0, 0, 0);
    entity3.assign<Rotate>(0, 0, 0, 1);

    entityx::Entity entity = e.entities.create();
    entity.assign<Position>(
        -50.0f,  -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f,

        0,1,2,
        2,3,0
    );

    entity.assign<ShaderComp>("src/res/shaders/Basic.shader");
    entity.assign<TextureComp>("src/res/textures/Torb.png");
    entity.assign<Translation>(200, 200, 0);
    entity.assign<Rotate>(0, 0, 0, 1);

    entityx::Entity entity2 = e.entities.create();
    entity2.assign<Position>(
        -50.0f,  -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f,

        0,1,2,
        2,3,0
    );

    entity2.assign<ShaderComp>("src/res/shaders/Basic.shader");
    entity2.assign<TextureComp>("src/res/textures/Sport.png");
    entity2.assign<Translation>(800, 200, 0);
    entity2.assign<Rotate>(180, 0, 0, 1);
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mada Mada", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //VSYNC
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        e.update();

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();

        /*
        // input
        // -----
        processInput(window);
        */
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    GLCall(glViewport(0, 0, width, height));
} 