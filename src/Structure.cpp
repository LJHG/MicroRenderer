//
// Created by lm on 2022/5/22.
//

#include "Structure.h"

namespace MicroRenderer{
    void Mesh::asTriangle(VertexData v1, VertexData v2, VertexData v3) {
        vertices.empty();indices.empty();
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
}