#ifndef MESH_H
#define MESH_H

#include "model.h"

#include <QImage>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector>
#include <QVector3D>

#include <memory>


class Mesh : protected QOpenGLFunctions_3_3_Core {

public:
    Model model;

    // Buffers
    GLuint meshVAO;
    GLuint meshVBO;
    GLuint meshSize;

    // Uniforms for the Phong shader program.
    GLint uniformModelViewTransformPhong;
    GLint uniformNormalTransformPhong;

    // Texture
    GLuint textureName;

    // Transforms
    float scale = 1.0F;
    QVector3D rotation;
    QVector3D translate;
    QMatrix3x3 meshNormalTransform;
    QMatrix4x4 meshTransform;

    //animation transforms
    QVector3D rotateAnimation;
    QVector3D translateAnimation;

    explicit Mesh(QString filename);
    void loadMesh();
    void loadTexture(QString file);
    void updateModelTransforms();
    void destroyModelBuffers();
    void deleteTextures();
    void applyRotateAnimation();
    void applyAnimation();
    void drawMesh();
    void setRotate(int rotateX, int rotateY, int rotateZ);
    void setScale(int newScale);
    void setTranslate(int translateX, int translateY, int translateZ);

private:
    QVector<quint8> imageToBytes(QImage image);
};

#endif // MESH_H
