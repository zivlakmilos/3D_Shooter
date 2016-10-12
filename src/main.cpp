#include "engine/engine.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace zi;
using namespace std;

class Window : public zi::ZWindow
{
public:
    Window(void)
        : zi::ZWindow("Test", 1024, 768),
          m_camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f))
    {
//         m_vertexArray.setVertices({
//              -1.0f, -1.0f, -1.0f,
//               1.0f, -1.0f, -1.0f,
//               1.0f,  1.0f, -1.0f,
//              -1.0f,  1.0f, -1.0f,
//              -1.0f, -1.0f,  1.0f,
//               1.0f, -1.0f,  1.0f,
//               1.0f,  1.0f,  1.0f,
//              -1.0f,  1.0f,  1.0f,
//         });
//         m_vertexArray.setColors({
//             1.0f, 0.0f, 0.0f,
//             0.0f, 1.0f, 0.0f,
//             0.0f, 0.0f, 1.0f,
//             1.0f, 1.0f, 0.0f,
//             1.0f, 1.0f, 1.0f,
//             0.0f, 1.0f, 1.0f,
//             1.0f, 1.0f, 1.0f,
//             1.0f, 1.0f, 1.0f
//         });
//         m_vertexArray.setTextureCoords({
//             0.0f, 0.0f,
//             0.0f, 1.0f,
//             1.0f, 1.0f,
//             1.0f, 0.0f,
//             0.0f, 0.0f,
//             0.0f, 1.0f,
//             1.0f, 1.0f,
//             1.0f, 0.0f
//         });
//         m_vertexArray.setIndices({
//             0, 1, 2,    2, 3, 0,    // Front
//             4, 5, 6,    6, 7, 4,    // Back
//             1, 5, 6,    6, 2, 1,    // Left
//             0, 3, 7,    7, 4, 0,    // Right
//             0, 1, 5,    5, 3, 0,    // Bottom
//             3, 2, 6,    6, 7, 3     // Top
//         });
        
//         m_vertexArray.setVertices({
//             -1.0f, -1.0f, 0.0f,
//              1.0f, -1.0f, 0.0f,
//              1.0f,  1.0f, 0.0f,
//              1.0f,  1.0f, 0.0f,
//             -1.0f,  1.0f, 0.0f,
//             -1.0f, -1.0f, 0.0f
//         });
// //         m_vertexArray.setColors({
// //             1.0f, 0.0f, 0.0f,
// //             1.0f, 0.0f, 0.0f,
// //             1.0f, 0.0f, 0.0f,
// //             1.0f, 0.0f, 0.0f,
// //             1.0f, 0.0f, 0.0f,
// //             1.0f, 0.0f, 0.0f
// //         });
//         m_vertexArray.setTextureCoords({
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//             1.0f, 1.0f,
//             1.0f, 1.0f,
//             0.0f, 1.0f,
//             0.0f, 0.0f,
//         });
        
        m_vertexArray.setVertices({
            -1.0f, -1.0f, -1.0f,    // Back
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,    // Front
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,    // Bottom
             1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,    // Top
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,    // Right
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,    // Left
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
        });
        m_vertexArray.setTextureCoords({
            0.0f, 0.0f,     // Back
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,     // Front
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,     // Bottom
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,     // Top
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,     // Right
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,     // Left
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
        });
        
        try {
            m_texture.load("res/wood1.png");
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
        
        m_texture.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_texture.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        try {
            m_shader.loadVertexShader("shader/simpletexture.vertex");
            m_shader.loadFragmentShader("shader/simpletexture.fragment");
            m_shader.build();
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
        
        showCursos(false);
        glfwSetCursorPos(m_glfwWindow, 0.0f, 0.0f);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        //glEnable(GL_CULL_FACE);
    }
    
    virtual ~Window(void)
    {
    }
    
    virtual void logic(void)
    {
//         glm::mat4 rotation = glm::rotate(glm::mat4(),
//                                          3.0f * (float)getDeltaTime(),
//                                          glm::vec3(0.0f, 1.0f, 0.0f));
//         m_vertexArray.setTransform(m_vertexArray.getTransform() * rotation);
        
        double cursorX, cursorY;
        glfwGetCursorPos(m_glfwWindow, &cursorX, &cursorY);
        glfwSetCursorPos(m_glfwWindow, 0, 0);
        
        glm::vec3 up = zi::up;
        glm::vec3 right = glm::cross(m_camera.getDirection(), up);
        m_camera.rotate(-cursorX * 0.3f * getDeltaTime(), up);
        m_camera.rotate(-cursorY * 0.3f * getDeltaTime(), right);
        
        if(glfwGetKey(m_glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
            m_camera.move(zi::DirectionForward, (float)getDeltaTime() * 3.0f);
        if(glfwGetKey(m_glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
            m_camera.move(zi::DirectionBack, (float)getDeltaTime() * 3.0f);
        if(glfwGetKey(m_glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
            m_camera.move(zi::DirectionRight, (float)getDeltaTime() * 3.0f);
        if(glfwGetKey(m_glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
            m_camera.move(zi::DirectionLeft, (float)getDeltaTime() * 3.0f);
        
        zi::ZWindow::logic();
    }
    
    virtual void render(void)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        try {
            //m_renderer.render(m_vertexArray, m_shader, &m_texture);
            m_renderer.render(m_camera, m_vertexArray, m_shader, &m_texture);
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
        
        zi::ZWindow::render();
    }
    
private:
    VertexArray m_vertexArray;
    Shader m_shader;
    Renderer m_renderer;
    Texture m_texture;
    Camera m_camera;
};

int main(int argc, char *argv[])
{
    /*
     * Must init before create object of ZApllication
     */
    Debug::init();
    Debug::setDebugEnabled(true);
    
    try {
        ZApplication app(argc, argv);
        Window *window = new Window;
        app.addWindow(window);
        window->show();
        app.start();
    } catch(ZException ex) {
        Debug::error << ex;
    }
    
    return 0;
}
