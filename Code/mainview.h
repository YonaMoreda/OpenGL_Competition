#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "mesh.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QMatrix4x4>
#include <memory>
#include <vector>
#define NR_COOKIES 15

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    enum SceneMode : GLuint {
        COOKIES_SCENE = 0, FACE_SCENE, SPACE_SCENE
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setSceneMode(SceneMode scene);

    // Textures
    QVector<quint8> imageToBytes(QImage image);
//todo::    void loadTexture(QString file, GLuint texturePtr, Model model);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged(QOpenGLDebugMessage Message);

private:
    QOpenGLDebugLogger debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgramPhong;


    GLint uniformModelViewTransformPhong;
    GLint uniformProjectionTransformPhong;
    GLint uniformNormalTransformPhong;

    GLuint uniformMaterialPhong;
    GLuint uniformLightPositionPhong;
    GLuint uniformLightColorPhong;

    // Transforms
    QMatrix4x4 projectionTransform;

    SceneMode currentScene = SPACE_SCENE;

    // Texture
    GLuint texturePtr;
    GLuint uniformTextureSamplerPhong;

    void createShaderProgram();
    void loadMesh();

    void destroyModelBuffers();

    void updateProjectionTransform();
    void updateModelTransforms();

    void updatePhongUniforms(int meshIdx);

    QVector4D material = {0.5F, 0.5F, 0.5F, 5.0F};
    QVector3D lightPosition = {5.0F, 0.0F, -1.0F};
    QVector3D lightColor = {1.0F, 1.0F, 1.0F};

    //initial meshes
    Mesh mesh1{":/models/face.obj"};
    Mesh mesh2{":/models/face.obj"};
    Mesh mesh3{":/models/face.obj"};
    Mesh mesh4{":/models/face.obj"};
    Mesh cookieMesh1{":/models/cookie.obj"};
    Mesh cookieMesh2{":/models/cookie.obj"};
    Mesh cookieMesh3{":/models/cookie.obj"};
    Mesh cookieMesh4{":/models/cookie.obj"};
    Mesh cookieMesh5{":/models/cookie.obj"};
    Mesh cookieMesh6{":/models/cookie.obj"};
    Mesh cookieMesh7{":/models/cookie.obj"};
    Mesh cookieMesh8{":/models/cookie.obj"};
    Mesh cookieMesh9{":/models/cookie.obj"};
    Mesh cookieMesh10{":/models/cookie.obj"};
    Mesh cookieMesh11{":/models/cookie.obj"};
    Mesh cookieMesh12{":/models/cookie.obj"};
    Mesh cookieMesh13{":/models/cookie.obj"};
    Mesh cookieMesh14{":/models/cookie.obj"};
    Mesh cookieMesh15{":/models/cookie.obj"};
    Mesh planetMesh{":/models/sphere.obj"};
    Mesh enduranceMesh{":/models/endurance.obj"};
    Mesh spaceMesh{":/models/sphere.obj"};
    Mesh ufoMesh{":/models/UFO.obj"};
    std::vector<Mesh *> meshVector;
};

#endif // MAINVIEW_H
