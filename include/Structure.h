//
// Created by lm on 2022/5/22.
//

#ifndef MICRORENDERER_STRUCTURE_H
#define MICRORENDERER_STRUCTURE_H
#include "glm/glm.hpp"
#include <vector>
#include <string>


// define vertex, fragment and mesh...

namespace MicroRenderer{
    struct Material{
        glm::vec3 ka;
        glm::vec3 kd;
        glm::vec3 ks;
        float shininess;
        // default initialize
        Material(){
            ka = glm::vec3(0.2f,0.2f,0.2f);
            kd= glm::vec3(1.0f,0.5f,0.5f);
            ks = glm::vec3(0.2f,0.2f,0.2f);
            shininess = 16.0f;
        }
        Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _shininess){
            ka = _ka;
            kd = _kd;
            ks = _ks;
            shininess = _shininess;
        }
    };

    struct VertexData{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color; //如果是Phong shader, 那么就不使用color这个属性，而是去查询纹理或者直接用材质
        bool hasTexture; //如果有纹理，那么把material的 kd 替换为纹理取到的颜色
        glm::vec2 textureCoord; // 纹理坐标
    };
    struct VertexOutData{
        glm::vec4 position;
        glm::vec3 normal;
        glm::vec4 color;
        bool hasTexture; //如果有纹理，那么把material的 kd 替换为纹理取到的颜色
        glm::vec2 textureCoord; // 纹理坐标
    };

    struct FragmentData{
        //to be filled...
    };

    class Mesh{
    public:
        Mesh();

        /** getter and setter for vertices and indices **/
        std::vector<VertexData>& getVertices();
        std::vector<unsigned int>& getIndices();
        Material getMaterial();
        void setVertices(const std::vector<VertexData>& _vertices);
        void setIndices(const std::vector<unsigned int>& _indices);
        void setMaterial(Material _material);
        void addVertex(VertexData v);
        void addIndex(unsigned int idx);

        /** set model matrix **/
        void setModelMatrix(const glm::mat4& m);
        glm::mat4 getModelMatrix();


        /** quick create mesh functions **/
        void asTriangle(VertexData v1, VertexData v2, VertexData v3); // read 3 vertices and as a triangle
        void asCube(glm::vec3 center, float size, Material _material); // use fot generate point light


    private:
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
        Material material;
        glm::mat4 modelMatrix;
    };
}



#endif //MICRORENDERER_STRUCTURE_H
