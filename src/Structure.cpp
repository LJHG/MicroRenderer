//
// Created by lm on 2022/5/22.
//

#include "Structure.h"

namespace MicroRenderer{
    void Mesh::asTriangle(VertexData v1, VertexData v2, VertexData v3) {
        vertices.clear();indices.clear();
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
    }

    std::vector<VertexData> &Mesh::getVertices() {
        return vertices;
    }

    std::vector<unsigned int> &Mesh::getIndices() {
        return indices;
    }

    void Mesh::setVertices(const std::vector<VertexData>& _vertices) {
        vertices = _vertices;
    }

    void Mesh::setIndices(const std::vector<unsigned int>& _indices) {
        indices = _indices;
    }

    Mesh::Mesh() {
        modelMatrix = glm::mat4(1.0f);
        textureUrl = "none";
    }

    void Mesh::setModelMatrix(const glm::mat4 &m) {
        modelMatrix = m;
    }

    void Mesh::setMaterial(Material _material) {
        material = _material;
    }

    glm::mat4 Mesh::getModelMatrix() {
        return modelMatrix;
    }

    void Mesh::addVertex(VertexData v) {
        vertices.push_back(v);
    }
    void Mesh::addIndex(unsigned int idx) {
        indices.push_back(idx);
    }

    Material Mesh::getMaterial() {
        return material;
    }

    void Mesh::asCube(glm::vec3 center, float size, Material _material) {
        // generate a cube centered at a given position with a given size
        material = _material;
        VertexData v0,v1,v2,v3,v4,v5,v6,v7;
        //position
        v0.position = glm::vec3(center[0]-size/2,center[1]-size/2,center[2]-size/2); // ---
        v1.position = glm::vec3(center[0]-size/2,center[1]-size/2,center[2]+size/2); // --+
        v2.position = glm::vec3(center[0]-size/2,center[1]+size/2,center[2]-size/2); // -+-
        v3.position = glm::vec3(center[0]-size/2,center[1]+size/2,center[2]+size/2); // -++
        v4.position = glm::vec3(center[0]+size/2,center[1]-size/2,center[2]-size/2); // +--
        v5.position = glm::vec3(center[0]+size/2,center[1]-size/2,center[2]+size/2); // +-+
        v6.position = glm::vec3(center[0]+size/2,center[1]+size/2,center[2]-size/2); // ++-
        v7.position = glm::vec3(center[0]+size/2,center[1]+size/2,center[2]+size/2); // +++

        //normal 乱设的
        v0.normal = glm::vec3(1.0f,1.0f,1.0f);
        v1.normal = glm::vec3(1.0f,1.0f,1.0f);
        v2.normal = glm::vec3(1.0f,1.0f,1.0f);
        v3.normal = glm::vec3(1.0f,1.0f,1.0f);
        v4.normal = glm::vec3(1.0f,1.0f,1.0f);
        v5.normal = glm::vec3(1.0f,1.0f,1.0f);
        v6.normal = glm::vec3(1.0f,1.0f,1.0f);
        v7.normal = glm::vec3(1.0f,1.0f,1.0f);


        vertices = {v0,v1,v2,v3,v4,v5,v6,v7};
        indices.push_back(0);indices.push_back(1);indices.push_back(2);
        indices.push_back(1);indices.push_back(2);indices.push_back(3);
        indices.push_back(4);indices.push_back(5);indices.push_back(6);
        indices.push_back(5);indices.push_back(6);indices.push_back(7);
        indices.push_back(2);indices.push_back(3);indices.push_back(7);
        indices.push_back(2);indices.push_back(6);indices.push_back(7);
        indices.push_back(0);indices.push_back(1);indices.push_back(4);
        indices.push_back(0);indices.push_back(4);indices.push_back(5);
        indices.push_back(1);indices.push_back(3);indices.push_back(7);
        indices.push_back(1);indices.push_back(5);indices.push_back(7);
        indices.push_back(0);indices.push_back(2);indices.push_back(4);
        indices.push_back(2);indices.push_back(4);indices.push_back(6);

    }

    void Mesh::setTextureUrl(std::string _textureUrl) {
        textureUrl = _textureUrl;
    }

    std::string Mesh::getTextureUrl() {
        return textureUrl;
    }
}