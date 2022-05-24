//
// Created by lm on 2022/5/22.
//

#ifndef MICRORENDERER_STRUCTURE_H
#define MICRORENDERER_STRUCTURE_H
#include "glm/glm.hpp"
#include <vector>


// define vertex, fragment and mesh...

namespace MicroRenderer{
    struct VertexData{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color;
    };
    struct VertexOutData{
        glm::vec4 position;
        glm::vec3 normal;
        glm::vec4 color;
    };


    struct FragmentData{
        //to be filled...
    };
    class Mesh{
    public:
        void asTriangle(VertexData v1, VertexData v2, VertexData v3); // read 3 vertices and as a triangle
        std::vector<VertexData>& getVertices();
        std::vector<unsigned int>& getIndices();
        void setVertices(const std::vector<VertexData>& _vertices);
        void setIndices(const std::vector<unsigned int>& _indices);
    private:
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
    };
}



#endif //MICRORENDERER_STRUCTURE_H
