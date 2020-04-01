#include "mesh.h"

Mesh::Mesh(QString filename) : model(filename) {
}

void Mesh::loadMesh() {
    initializeOpenGLFunctions();
    QVector<float> meshData = model.getVNTInterleaved();
    meshSize = model.getVertices().size();

    // Generate VAO
    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);

    // Generate VBO
    glGenBuffers(1, &meshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);


    // Write the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(GL_FLOAT), meshData.data(), GL_STATIC_DRAW);

    // Set vertex coordinates to location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // Set vertex normals to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), reinterpret_cast<void*>(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    // Set vertex texture coordinates to location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), reinterpret_cast<void*>(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


void Mesh::loadTexture(QString file) {
    glGenTextures(1, &textureName);
    // Set texture parameters.
    glBindTexture(GL_TEXTURE_2D, textureName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Push image data to texture.
    QImage image(file);
    QVector<quint8> imageData = imageToBytes(image);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
}

void Mesh::updateModelTransforms() {
    meshTransform.setToIdentity();

    meshTransform.translate(translate.x(), translate.y(), translate.z());

    meshTransform.rotate(rotation.x(), {1.0F, 0.0F, 0.0F});
    meshTransform.rotate(rotation.y(), {0.0F, 1.0F, 0.0F});
    meshTransform.rotate(rotation.z(), {0.0F, 0.0F, 1.0F});

    meshTransform.scale(scale);

    meshNormalTransform = meshTransform.normalMatrix();
}

void Mesh::destroyModelBuffers() {
    glDeleteBuffers(1, &meshVBO);
    glDeleteVertexArrays(1, &meshVAO);
}

void Mesh::deleteTextures() {
    glDeleteTextures(1, &textureName);
}

void Mesh::applyRotateAnimation() {
    meshTransform.rotate(rotateAnimation.x(), {1.0F, 0.0F, 0.0F});
    meshTransform.rotate(rotateAnimation.y(), {0.0F, 1.0F, 0.0F});
    meshTransform.rotate(rotateAnimation.z(), {0.0F, 0.0F, 1.0F});
    meshNormalTransform = meshTransform.normalMatrix();
}

void Mesh::applyAnimation() {
    meshTransform.translate(translateAnimation.x(), translateAnimation.y(), translateAnimation.z());

    applyRotateAnimation();
}

void Mesh::drawMesh() {
    // Set the texture and draw the mesh.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureName);

    glBindVertexArray(meshVAO);
    glDrawArrays(GL_TRIANGLES, 0, meshSize);
}

void Mesh::setRotate(int rotateX, int rotateY, int rotateZ){
    rotation = { static_cast<float>(rotateX),
                     static_cast<float>(rotateY),
                     static_cast<float>(rotateZ) };
    updateModelTransforms();

}

void Mesh::setScale(int newScale){
    scale = static_cast<float>(newScale) / 100.0F;
    updateModelTransforms();
}

void Mesh::setTranslate(int translateX, int translateY, int translateZ) {
    translate ={static_cast<float>(translateX),
                static_cast<float>(translateY),
                static_cast<float>(translateZ) };
    updateModelTransforms();
}
