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



void MyApp::createTransformations() {
    /*
    The first transformation in code is the first transformation applied to a piece.
    Eg. the large blue triangle first rotates -135 degrees around Z axis, then translates by (sqrt(2)/2, -sqrt(2)/2, 0).
    This was done to make code easier to write and more intuitive.

    To create the tangram shape, first step is to scale pieces appropriately, then rotate, then translate.
    This ensures that all the pieces are in the correct position relative to each other.

    Once this is done, there is an additional scaling, rotation and translation done to all pieces equally ('for loop')
    Scaling and translation ensure all pieces fit cleanly in clipspace.
    The rotation tilts the entire "Sea Dinosaur" shape slightly upwards.
    These transformations are applied after individual pieces transformations, meaning they change the "Sea Dinosaur"
    shape rather than individual pieces.
    */

    // Large blue triangle
    //std::unique_ptr<Triangle> t1 = std::make_unique<Triangle>(VaoId[0], glm::vec3((15.0 / 255), (130.0 / 255), (242.0 / 255)), MatrixId, ColorId);
    //t1->rotate(glm::vec3(0.0f, 0.0f, 1.0f), -135.0f);
    //t1->translate(glm::vec3(std::sqrt(2) / 2, -std::sqrt(2) / 2, 0));

    //// Large magenta triangle
    //std::unique_ptr<Triangle> t2 = std::make_unique<Triangle>(VaoId[0], glm::vec3((205.0 / 255), (14.0 / 255), (102.0 / 255)), MatrixId, ColorId);
    //t2->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 45.0f);

    //// Medium purple triangle
    //std::unique_ptr<Triangle> t3 = std::make_unique<Triangle>(VaoId[0], glm::vec3((109.0 / 255), (59.0 / 255), (191.0 / 255)), MatrixId, ColorId);
    //t3->scale(glm::vec3(std::sqrt(2) / 2, std::sqrt(2) / 2, 0.0f));
    //t3->translate(glm::vec3(-std::sqrt(2) / 4, -std::sqrt(2) / 4, 0.0f));

    //// Small teal triangle
    //std::unique_ptr<Triangle> t4 = std::make_unique<Triangle>(VaoId[0], glm::vec3((0.0 / 255), (158.0 / 255), (166.0 / 255)), MatrixId, ColorId);
    //t4->scale(glm::vec3(0.5f, 0.5f, 0.0f));
    //t4->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 45.0f);
    //t4->translate(glm::vec3(-std::sqrt(2) / 4, -std::sqrt(2) / 2, 0.0f));

    //// Small orange triangle
    //std::unique_ptr<Triangle> t5 = std::make_unique<Triangle>(VaoId[0], glm::vec3((235.0 / 255), (71.0 / 255), (38.0 / 255)), MatrixId, ColorId);
    //t5->scale(glm::vec3(0.5f, 0.5f, 0.0f));
    //t5->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);
    //t5->translate(glm::vec3(-sqrt(2) / 2 - 1.25f, 0.25f, 0.0f));

    //// Green square
    //std::unique_ptr<Square> s = std::make_unique<Square>(VaoId[1], glm::vec3((34.0 / 255), (171.0 / 255), (36.0 / 255)), MatrixId, ColorId);
    //s->scale(glm::vec3(0.5f, 0.5f, 0.0f));
    //s->translate(glm::vec3(-sqrt(2) / 2 - 0.75f, 0.25f, 0.0f));

    //// Orange parallelogram
    //std::unique_ptr<Parallelogram> p = std::make_unique<Parallelogram>(VaoId[2], glm::vec3((253.0 / 255), (140.0 / 255), (0.0 / 255)), MatrixId, ColorId);
    //p->scale(glm::vec3(0.5f, 0.5f, 0.0f));
    //p->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);
    //p->translate(glm::vec3(-sqrt(2) / 2 - 0.25f, 0.0f, 0.0f));

    //// Add all pieces to shapes array
    //this->shapes.push_back(std::move(t1));
    //this->shapes.push_back(std::move(t2));
    //this->shapes.push_back(std::move(t3));
    //this->shapes.push_back(std::move(t4));
    //this->shapes.push_back(std::move(t5));
    //this->shapes.push_back(std::move(s));
    //this->shapes.push_back(std::move(p));

    //// Universal transformations applied to the entire "Sea Dinosaur"
    //for (auto& shape : shapes) {
    //    shape->scale(glm::vec3(0.5f, 0.5f, 0.0f));
    //    shape->rotate(glm::vec3(0.0f, 0.0f, 1.0f), -11.0f);
    //    shape->translate(glm::vec3(0.25f, 0.0f, 0.0f));
    //}
}

////////////////////////////////////////////////////////////////////////// SCENE

void MyApp::drawScene() {
    // Drawing directly in clip space
    parallelogram->draw(glm::mat4(1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow* win) {
    createBufferObjects();
    createShaderProgram();
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
