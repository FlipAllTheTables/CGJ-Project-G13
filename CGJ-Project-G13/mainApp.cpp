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
    Triangle *triangle;
    Square *square;
    Parallelogram *parallelogram;
    const GLuint POSITION = 0, COLOR = 1;
    std::unique_ptr<mgl::ShaderProgram> Shaders = nullptr;
    GLint MatrixId, ColorId;
    void createShaderProgram();
    void createBufferObjects();
    void destroyBufferObjects();
    void drawScene();
    void createTransformations();
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

void MyApp::createBufferObjects() {
    triangle = new Triangle(MatrixId, ColorId);
    square = new Square(MatrixId, ColorId);
    parallelogram = new Parallelogram(MatrixId, ColorId);
}

void MyApp::destroyBufferObjects() {
    triangle->destroyBufferObjects();
    square->destroyBufferObjects();
    parallelogram->destroyBufferObjects();
    delete triangle;
    delete square;
    delete parallelogram;
}

//////////////////////////////////////////////////////////////////// MATRICES

std::vector<glm::mat4> matrices(7, glm::mat4(1.0f));

/*
 * The first transformation in code is the first transformation applied to the piece.
 * Eg. the large blue triangle first rotates -135 degrees around Z axis, then translates by (sqrt(2)/2, -sqrt(2)/2, 0).
 * This was done to make code easier to write and to understand, together with having one transformation per line.
 * 
 * To create the tangram shape, first step is to scale pieces appropriately, then rotate, then translate.
 * This ensures that all the pieces are in the correct position relative to each other.
 * 
 * Once this is done, there is an additional scaling, rotation and translation done to all pieces equally ('for loop')
 * Scaling and translation ensure all pieces fit cleanly in clipspace.
 * The rotation tilts the entire "Sea Dinosaur" shape slightly upwards.
 * These transformations are applied after individual pieces transformations, meaning they change the "Sea Dinosaur"
 * shape rather than individual pieces.
 */
void MyApp::createTransformations() {

    glm::mat4 I = glm::mat4(1.0f); // Identity matrix

    // Large blue triangle
    matrices[0] = glm::rotate(I, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * matrices[0];
    matrices[0] = glm::translate(I, glm::vec3(std::sqrt(2) / 2, -sqrt(2) / 2, 0)) * matrices[0];

    // Large magenta triangle
    matrices[1] = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * matrices[1];

    // Medium purple triangle
    matrices[2] = glm::scale(I, glm::vec3(std::sqrt(2) / 2, std::sqrt(2) / 2, 0.0f)) * matrices[2];
    matrices[2] = glm::translate(I, glm::vec3(-std::sqrt(2) / 4, -std::sqrt(2) / 4, 0.0f)) * matrices[2];

    // Small teal triangle
    matrices[3] = glm::scale(I, glm::vec3(0.5f, 0.5f, 1.0f)) * matrices[3];
    matrices[3] = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * matrices[3];
    matrices[3] = glm::translate(I, glm::vec3(-std::sqrt(2) / 4, -std::sqrt(2) / 2, 0.0f)) * matrices[3];

    // Small orange triangle
    matrices[4] = glm::scale(I, glm::vec3(0.5f, 0.5f, 1.0f)) * matrices[4];
    matrices[4] = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))* matrices[4];
    matrices[4] = glm::translate(I, glm::vec3(-sqrt(2) / 2 - 1.25f, 0.25f, 0.0f)) * matrices[4];

    // Green square
    matrices[5] = glm::scale(I, glm::vec3(0.5f, 0.5f, 1.0f)) * matrices[5];
    matrices[5] = glm::translate(I, glm::vec3(-sqrt(2) / 2 - 0.75f, 0.25f, 0.0f)) * matrices[5];

    // Orange parallelogram
    matrices[6] = glm::scale(I, glm::vec3(0.5f, 0.5f, 1.0f)) * matrices[6];
    matrices[6] = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * matrices[6];
    matrices[6] = glm::translate(I, glm::vec3(-sqrt(2) / 2 - 0.25f, 0.0f, 0.0f)) * matrices[6];

    // Universal transformations applied to the entire figure
    for (int i = 0; i < matrices.size(); i++) {
        matrices[i] = glm::scale(I, glm::vec3(0.5f, 0.5f, 1.0f)) * matrices[i];
        matrices[i] = glm::rotate(I, glm::radians(-11.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * matrices[i];
        matrices[i] = glm::translate(I, glm::vec3(0.25f, 0.0f, 0.0f)) * matrices[i];
    }
}

////////////////////////////////////////////////////////////////////////// SCENE

void MyApp::drawScene() {
    // Drawing directly in clip space
    Shaders->bind();
    triangle->draw(matrices[0], glm::vec4((15.0 / 255), (130.0 / 255), (242.0 / 255), 1.0f));       //Large blue triangle
    triangle->draw(matrices[1], glm::vec4((205.0 / 255), (14.0 / 255), (102.0 / 255), 1.0f));       //Large magenta triangle
    triangle->draw(matrices[2], glm::vec4((109.0 / 255), (59.0 / 255), (191.0 / 255), 1.0f));       //Medium purple triangle
    triangle->draw(matrices[3], glm::vec4((0.0 / 255), (158.0 / 255), (166.0 / 255), 1.0f));        //Small teal triangle
    triangle->draw(matrices[4], glm::vec4((235.0 / 255), (71.0 / 255), (38.0 / 255), 1.0f));        //Small orange triangle
    square->draw(matrices[5], glm::vec4((34.0 / 255), (171.0 / 255), (36.0 / 255), 1.0f));          //Green square
    parallelogram->draw(matrices[6], glm::vec4((253.0 / 255), (140.0 / 255), (0.0 / 255), 1.0f));   //Orange parallelogram
    Shaders->unbind();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow* win) {
    createShaderProgram();
    createBufferObjects();
    createTransformations();
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
