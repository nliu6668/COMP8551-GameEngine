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

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// screen res
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    Engine& e = Engine::getInstance();
    e.update();
    
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

    float positions[] = {
        //x       y      texcoords
        -50.0f,  -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
    };
    
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //For large objects just 1 vertex buffer and multiple index buffers for different material types
    //create vertex buffer
    vertexArray va;
    vertexBuffer vb(positions, 4 * 4 * sizeof(float));

    vertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);


    //create index buffer
    indexBuffer ib(indices, 6);



    //Orthographic projection between (-2 and 2 (x) / -1.5 and 1.5 (y) / -1 and 1 (z))
    //This is the view, if any of the positions are outside of this view, they won't be rendered
    //EG. if position x is -0.5 and ortho view is -2  - 2:
    //  then it will be a quarter of the way to the left since -0.5 is 1/4th of 2 which will make it 0.25
    //1:1 pixel mapping for 960x540 res:
    //  glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    
    /*
    Model matrix: defines position, rotation and scale of the vertices of the model in the world.
    View matrix: defines position and orientation of the "camera".
    Projection matrix: Maps what the "camera" sees to NDC, taking care of aspect ratio and perspective.
    */
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //Need to eventually move this model view out in to imgui

    //Have to set uniforms to the same bind slot (default 0)
    shader shader("src/res/shaders/Basic.shader");
    shader.Bind();
    //shader.setUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f); //sets colours
    //shader.setUniformsMat4f("u_MVP", mvp); // sets textures

    texture textureTorb("src/res/textures/Torb.png"); 
    texture textureSport("src/res/textures/Sport.png");
    textureTorb.Bind();
    shader.setUniforms1i("u_Texture", 0);

    /*
    Shader binds program for the gpu to use and tells it what to do with data
    VA = The Data itself.
    VB = vertex data, positions, texture coords
    IB = contains vertex indices
    //Draw uses IB access VB and call shader program on all vertices individually
    */
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    renderer renderer;

    glm::vec3 translationA(200,200, 0);
    glm::vec3 translationB(800,200, 0);


    float r = 0.0f;
    float increment = 0.05f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        shader.Bind();
        //scope
        {
            textureTorb.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA));
            glm::mat4 mvp = proj * view * model; 
            // shader.setUniforms4f("u_Color", r, 0.3f, 0.8f, 1.0f); //swaps colours
            shader.setUniformsMat4f("u_MVP", mvp);
            
            renderer.Draw(va, ib, shader);
        }

        {
            textureSport.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translationB));
            glm::mat4 mvp = proj * view * model; 
            // shader.setUniforms4f("u_Color", r, 0.3f, 0.8f, 1.0f); //swaps colours
            shader.setUniformsMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }

        //swaps colours
        if(r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        translationB[0] -= r;

        r += increment;

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();

        /*
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
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