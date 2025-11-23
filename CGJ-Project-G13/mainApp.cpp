////////////////////////////////////////////////////////////////////////////////
//
// Basic Triangle rendering
//
// This program demonstrates fundamental Modern OpenGL concepts by rendering
// two triangle instances directly in Clip Space. It serves as an introductory
// example for understanding the OpenGL graphics pipeline and basic shader
// programming.
//
// Key Concepts Demonstrated:
// - Vertex Array Objects (VAOs) and Vertex Buffer Objects (VBOs)
// - Shader program creation and management
// - Attribute and uniform handling
// - Basic transformation matrices
// - Clip space rendering without model/view/projection matrices
//
// Copyright (c) 2013-25 by Carlos Martinho
//
////////////////////////////////////////////////////////////////////////////////

#include <memory>

#include "../mgl/mgl.hpp"
#include "./Shape.hpp"
#include "./Triangle.hpp"
#include "./Square.hpp"
#include "./Parallelogram.hpp"
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
public:
    MyApp() = default;
    ~MyApp() override = default;

    void initCallback(GLFWwindow* win) override;
    void displayCallback(GLFWwindow* win, double elapsed) override;
    void windowCloseCallback(GLFWwindow* win) override;
    void windowSizeCallback(GLFWwindow* win, int width, int height) override;

private:
    const GLuint POSITION = 0, COLOR = 1;
    GLuint VaoId[3], VboId[6];
    int N_SHAPES = 3;
    std::vector<std::unique_ptr<Shape>> shapes;
    std::unique_ptr<mgl::ShaderProgram> Shaders = nullptr;
    GLint MatrixId, ColorId;
    void createShaderProgram();
    void createBufferObjects();
    void destroyBufferObjects();
    void drawScene();
    void createShapes();
};

//////////////////////////////////////////////////////////////////////// SHADERs

void MyApp::createShaderProgram() {
    Shaders = std::make_unique<mgl::ShaderProgram>();
    Shaders->addShader(GL_VERTEX_SHADER, "clip-vs.glsl");
    Shaders->addShader(GL_FRAGMENT_SHADER, "clip-fs.glsl");

    Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, POSITION);
    Shaders->addAttribute(mgl::COLOR_ATTRIBUTE, COLOR);
    Shaders->addUniform("Matrix");
    Shaders->addUniform("Color");

    Shaders->create();

    MatrixId = Shaders->Uniforms["Matrix"].index;
    ColorId = Shaders->Uniforms["Color"].index;
}

//////////////////////////////////////////////////////////////////// VAOs & VBOs

typedef struct {
    GLfloat XYZW[4];
} Vertex;

// vertices[0] = Triangle; vertices[0] = Square; vertices[0] = Parallelogram; 
const std::vector<std::vector<Vertex>> Vertices = {
    { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} },
    { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} },
    { {-1.0f, -0.5f, 0.0f, 1.0f}, {0.0f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.5f, 0.0f, 1.0f}}
};

const std::vector<std::vector<GLubyte>> Indices = {
    { {0, 1, 2} },
    { {0, 1, 2, 0, 2, 3} },
    { {0, 1, 2, 1, 3, 2} }
};

void MyApp::createBufferObjects() {
    glGenVertexArrays(3, VaoId);
    glGenBuffers(6, VboId);
    for (int i = 0; i < N_SHAPES; i++) {
        glBindVertexArray(VaoId[i]);
        {
            glBindBuffer(GL_ARRAY_BUFFER, VboId[2*i]);
            {
                glBufferData(GL_ARRAY_BUFFER, Vertices[i].size() * sizeof(Vertex), Vertices[i].data(), GL_STATIC_DRAW);
                glEnableVertexAttribArray(POSITION);
                glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                    reinterpret_cast<GLvoid*>(0));

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2*i+1]);
                {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices[i].size() * sizeof(GLubyte), Indices[i].data(),
                        GL_STATIC_DRAW);
                }
            }
        }
        glBindVertexArray(0);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(6, VboId);
}

void MyApp::destroyBufferObjects() {
    for (int i = 0; i < 1; i++) {
        glBindVertexArray(VaoId[i]);
        glDisableVertexAttribArray(POSITION);
        glDisableVertexAttribArray(COLOR);
        glDeleteVertexArrays(1, &VaoId[i]);
        glBindVertexArray(0);
    }
}

void MyApp::createShapes() {
    std::unique_ptr<Triangle> t1 = std::make_unique<Triangle>(VaoId[0], glm::vec3((15.0 / 255), (130.0 / 255), (242.0 / 255)), MatrixId, ColorId);
    t1->translate(glm::vec3(-0.5, 0.5f, 0));
    t1->scale(glm::vec3(0.5f, 0.5f, 0.5f));
    t1->rotate(glm::vec3(0.0f, 0.0f, 1.0f), -135.0f);
    std::unique_ptr<Triangle> t2 = std::make_unique<Triangle>(VaoId[0], glm::vec3((205.0 / 255), (14.0 / 255), (102.0 / 255)), MatrixId, ColorId);
    std::unique_ptr<Triangle> t3 = std::make_unique<Triangle>(VaoId[0], glm::vec3((109.0 / 255), (59.0 / 255), (191.0 / 255)), MatrixId, ColorId);
    std::unique_ptr<Triangle> t4 = std::make_unique<Triangle>(VaoId[0], glm::vec3((0.0 / 255), (158.0 / 255), (166.0 / 255)), MatrixId, ColorId);
    std::unique_ptr<Triangle> t5 = std::make_unique<Triangle>(VaoId[0], glm::vec3((235.0 / 255), (71.0 / 255), (38.0 / 255)), MatrixId, ColorId);
    std::unique_ptr<Square> s = std::make_unique<Square>(VaoId[1], glm::vec3((34.0 / 255), (171.0 / 255), (36.0 / 255)), MatrixId, ColorId);
    s->translate(glm::vec3(-0.5, -0.5, 0));
    s->scale(glm::vec3(0.5f, 0.5f, 0.5f));
    std::unique_ptr<Parallelogram> p = std::make_unique<Parallelogram>(VaoId[2], glm::vec3((253.0 / 255), (140.0 / 255), (0.0 / 255)), MatrixId, ColorId);
    p->translate(glm::vec3(0.5, 0, 0));
    p->scale(glm::vec3(0.5f, 0.5f, 0.5f));
    this->shapes.push_back(std::move(t1));
    this->shapes.push_back(std::move(s));
    this->shapes.push_back(std::move(p));
}

////////////////////////////////////////////////////////////////////////// SCENE

void MyApp::drawScene() {
    // Drawing directly in clip space
    Shaders->bind();
    for (auto& shape : shapes) {
        shape->draw();
    }
    Shaders->unbind();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow* win) {
    createBufferObjects();
    createShaderProgram();
    createShapes();
}

void MyApp::windowCloseCallback(GLFWwindow* win) { destroyBufferObjects(); }

void MyApp::windowSizeCallback(GLFWwindow* win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
}

void MyApp::displayCallback(GLFWwindow* win, double elapsed) { drawScene(); }

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
    mgl::Engine& engine = mgl::Engine::getInstance();
    engine.setApp(new MyApp());
    engine.setOpenGL(4, 6);
    engine.setWindow(600, 600, "Hello Modern 2D World", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END
