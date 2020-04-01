#include "mainview.h"
#include "model.h"
#include "vertex.h"

#include <QDateTime>


/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    qDebug() << "MainView destructor";

    makeCurrent();
    for(uint i = 0; i < meshVector.size(); i++) {
        meshVector.at(i)->deleteTextures();
    }
    destroyModelBuffers();
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    connect(&debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
            this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if (debugLogger.initialize()) {
        qDebug() << ":: Logging initialized";
        debugLogger.startLogging(QOpenGLDebugLogger::SynchronousLogging);
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    //glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color to be used by glClear. This is, effectively, the background color.
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();
    meshVector.push_back(&cookieMesh1);
    meshVector.push_back(&cookieMesh2);
    meshVector.push_back(&cookieMesh3);
    meshVector.push_back(&cookieMesh4);
    meshVector.push_back(&cookieMesh5);
    meshVector.push_back(&cookieMesh6);
    meshVector.push_back(&cookieMesh7);
    meshVector.push_back(&cookieMesh8);
    meshVector.push_back(&cookieMesh9);
    meshVector.push_back(&cookieMesh10);
    meshVector.push_back(&cookieMesh11);
    meshVector.push_back(&cookieMesh12);
    meshVector.push_back(&cookieMesh13);
    meshVector.push_back(&cookieMesh14);
    meshVector.push_back(&cookieMesh15);

    meshVector.push_back(&mesh1);
    meshVector.push_back(&mesh2);
    meshVector.push_back(&mesh3);
    meshVector.push_back(&mesh4);

    meshVector.push_back(&planetMesh);
    meshVector.push_back(&enduranceMesh);
    meshVector.push_back(&spaceMesh);
    meshVector.push_back(&ufoMesh);

    for(uint i = 0; i < NR_COOKIES; i++) {
        meshVector.at(i)->loadMesh();
        meshVector.at(i)->loadTexture(":/textures/cookie_diff.jpg");
        meshVector.at(i)->setScale(10);
        meshVector.at(i)->setTranslate((i % 5) * 2 - 4, (i/5)*2 - 2, -7);
        meshVector.at(i)->setRotate(0, 0, 60);
        meshVector.at(i)->rotateAnimation = {0, 1, 0};
    }
    meshVector.at(NR_COOKIES)->loadMesh();
    meshVector.at(NR_COOKIES)->loadTexture(":/textures/yona_diff.jpg");
    meshVector.at(NR_COOKIES+1)->loadMesh();
    meshVector.at(NR_COOKIES+1)->loadTexture(":/textures/yona_diff.jpg");
    meshVector.at(NR_COOKIES+2)->loadMesh();
    meshVector.at(NR_COOKIES+2)->loadTexture(":/textures/yona_diff.jpg");
    meshVector.at(NR_COOKIES+3)->loadMesh();
    meshVector.at(NR_COOKIES+3)->loadTexture(":/textures/yona_diff.jpg");

    meshVector.at(NR_COOKIES+4)->loadMesh();
    meshVector.at(NR_COOKIES+4)->loadTexture(":/textures/planet_diff.jpg");
    meshVector.at(NR_COOKIES+5)->loadMesh();
    meshVector.at(NR_COOKIES+5)->loadTexture(":/textures/UFO_diff.jpg");
    meshVector.at(NR_COOKIES+6)->loadMesh();
    meshVector.at(NR_COOKIES+6)->loadTexture(":/textures/milkyWay_diff.jpg");
    meshVector.at(NR_COOKIES+7)->loadMesh();
    meshVector.at(NR_COOKIES+7)->loadTexture(":/textures/UFO_diff.jpg");

    // Initialize transformations
    updateProjectionTransform();
    updateModelTransforms();

    timer.start(1000.0 / 60.0);

    //set initial properties for meshes

    mesh1.setScale(20);
    mesh1.setRotate(0, -75, 0);
    mesh1.setTranslate(-2, -2, -7);
    mesh1.rotateAnimation = {0, 1, 0};
    mesh1.translateAnimation = {0, 0, 0};

    mesh2.setScale(20);
    mesh2.setRotate(0, 75, 0);
    mesh2.setTranslate(2, -2, -7);
    mesh2.rotateAnimation = {0, 1, 0};
    mesh2.translateAnimation = {0, 0, 0};

    mesh3.setScale(20);
    mesh3.setRotate(0, -75, 0);
    mesh3.setTranslate(-2, 2, -7);
    mesh3.rotateAnimation = {0, 1, 0};
    mesh3.translateAnimation = {0, 0, 0};

    mesh4.setScale(20);
    mesh4.setRotate(0, 75, 0);
    mesh4.setTranslate(2, 2, -7);
    mesh4.rotateAnimation = {0, 1, 0};
    mesh4.translateAnimation = {0, 0, 0};

    planetMesh.setScale(20);
    planetMesh.setRotate(0, 0, 0);
    planetMesh.setTranslate(2, 2 , -19);
    planetMesh.rotateAnimation = {0, 0.05, 0};
    planetMesh.translateAnimation = {0, 0, 0};

    enduranceMesh.setScale(20);
    enduranceMesh.setRotate(-10, 0, 0);
    enduranceMesh.setTranslate(2, 2 , -7);
    enduranceMesh.rotateAnimation = {0, 0, 2};
    enduranceMesh.translateAnimation = {0, 0, 0};

    spaceMesh.setScale(20);
    spaceMesh.setRotate(0, 0, 0);
    spaceMesh.setTranslate(0, 0 , -5);
    spaceMesh.rotateAnimation = {0, 0, 0};
    spaceMesh.translateAnimation = {0, 0, 0};

    ufoMesh.setScale(10);
    ufoMesh.setRotate(0, 0, 0);
    ufoMesh.setTranslate(-2, -2 , -8);
    ufoMesh.rotateAnimation = {0, 0, 0};
    ufoMesh.translateAnimation = {0.01, 0.01, 0};
}

void MainView::createShaderProgram() {
    // Create shader program

    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");
    shaderProgramPhong.link();

    // set the uniforms

    uniformModelViewTransformPhong = shaderProgramPhong.uniformLocation("modelViewTransformPhong");
    uniformProjectionTransformPhong = shaderProgramPhong.uniformLocation("projectionTransformPhong");
    uniformNormalTransformPhong = shaderProgramPhong.uniformLocation("normalTransformPhong");
    uniformTextureSamplerPhong = shaderProgramPhong.uniformLocation("textureSamplerPhong");

    uniformMaterialPhong = shaderProgramPhong.uniformLocation("materialPhong");
    uniformLightPositionPhong = shaderProgramPhong.uniformLocation("lightPosPhong");
    uniformLightColorPhong = shaderProgramPhong.uniformLocation("lightColorPhong");

    currentScene = SPACE_SCENE;
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    shaderProgramPhong.bind();

    //animation
    uint i = 0;
    uint sz = meshVector.size();
    if(currentScene == 0) {
        sz = NR_COOKIES;
    } else if(currentScene == 1) {
        i = NR_COOKIES;
        sz = NR_COOKIES + 4;
    } else if(currentScene == 2) {
        i = NR_COOKIES + 4;
    }
    for(; i < sz; i++) {
        meshVector.at(i)->applyAnimation();
        updatePhongUniforms(i);
        meshVector.at(i)->drawMesh();
    }
    if(meshVector.at(22)->meshTransform.column(3).x() >= 2.15) {
        meshVector.at(22)->translateAnimation = {0, 0, 0};
        meshVector.at(22)->rotateAnimation = {0, 0, 2};
    }
    shaderProgramPhong.release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) {
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    updateProjectionTransform();
}

void MainView::updatePhongUniforms(int meshIdx) {
    glUniformMatrix4fv(uniformProjectionTransformPhong, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelViewTransformPhong, 1, GL_FALSE, meshVector.at(meshIdx)->meshTransform.data());
    glUniformMatrix3fv(uniformNormalTransformPhong, 1, GL_FALSE, meshVector.at(meshIdx)->meshNormalTransform.data());

    glUniform4fv(uniformMaterialPhong, 1, &material[0]);
    glUniform3fv(uniformLightPositionPhong, 1, &lightPosition[0]);
    glUniform3f(uniformLightColorPhong, lightColor.x(), lightColor.y(), lightColor.z());

    glUniform1i(uniformTextureSamplerPhong, 0);
}

void MainView::updateProjectionTransform() {
    float aspect_ratio = static_cast<float>(width()) / static_cast<float>(height());
    projectionTransform.setToIdentity();
    projectionTransform.perspective(60, aspect_ratio, 0.2, 20);
}

void MainView::updateModelTransforms() {
    uint i = 0;
    uint sz = meshVector.size();
    if(currentScene == 0) {
        sz = NR_COOKIES;
    } else if(currentScene == 1) {
        i = NR_COOKIES;
        sz = NR_COOKIES + 4;
    } else if(currentScene == 2) {
        i = NR_COOKIES + 4;
    }
    for(; i < sz; i++) {
        meshVector.at(i)->updateModelTransforms();
    }
    update();
}

// --- OpenGL cleanup helpers

void MainView::destroyModelBuffers() {
    for(uint i = 0; i < meshVector.size(); i++) {
        meshVector.at(i)->destroyModelBuffers();
    }
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ) {
    uint i = 0;
    uint sz = meshVector.size();
    if(currentScene == 0) {
        sz = NR_COOKIES;
    } else if(currentScene == 1) {
        i = NR_COOKIES;
        sz = NR_COOKIES + 4;
    } else if(currentScene == 2) {
        i = NR_COOKIES + 4;
    }
    for(; i < sz; i++) {
        meshVector.at(i)->setRotate(rotateX, rotateY, rotateZ);
    }
    updateModelTransforms();
}

void MainView::setScale(int newScale) {
    uint i = 0;
    uint sz = meshVector.size();
    if(currentScene == 0) {
        sz = NR_COOKIES;
    } else if(currentScene == 1) {
        i = NR_COOKIES;
        sz = NR_COOKIES + 4;
    } else if(currentScene == 2) {
        i = NR_COOKIES + 4;
    }
    for(; i < sz; i++) {
        meshVector.at(i)->setScale(newScale);
    }
    updateModelTransforms();
}

void MainView::setSceneMode(SceneMode scene) {
    currentScene = scene;
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}

