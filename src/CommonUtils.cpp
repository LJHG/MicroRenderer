//
// Created by lm on 2022/5/19.
//

#include "CommonUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MicroRenderer{
    Image CommonUtils::loadImage(std::string url) {
        int width,height,channel;
        uint8_t* rgb_image = stbi_load(url.c_str(), &width, &height, &channel, 3);
        Image image(rgb_image,width,height,channel);
        return image;
    }

    std::vector<Mesh> CommonUtils::loadObjModel(std::string filepath){
        std::vector<Mesh> meshes;
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
        // 异常处理
        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "读取模型出现错误: " << import.GetErrorString() << std::endl;
            exit(-1);
        }
        // 模型文件相对路径
        std::string rootPath = filepath.substr(0, filepath.find_last_of('/'));

        // 循环生成 mesh
        for (int i = 0; i < scene->mNumMeshes; i++)
        {
            // 创建mesh
            Mesh mesh;

            // 获取 assimp 的读取到的 aiMesh 对象
            aiMesh* aiMesh = scene->mMeshes[i];

            VertexData vertexData;
            // 我们将数据传递给我们自定义的mesh
            for (int j = 0; j < aiMesh->mNumVertices; j++)
            {
                // 顶点
                glm::vec3 vvv;
                vvv.x = aiMesh->mVertices[j].x;
                vvv.y = aiMesh->mVertices[j].y;
                vvv.z = aiMesh->mVertices[j].z;
                vertexData.position = vvv;

                // 法线
                vvv.x = aiMesh->mNormals[j].x;
                vvv.y = aiMesh->mNormals[j].y;
                vvv.z = aiMesh->mNormals[j].z;
                vertexData.normal = glm::normalize(vvv); // 法线记得要归一化

                // 纹理坐标: 如果存在则加入。assimp 默认可以有多个纹理坐标 我们取第一个（0）即可
                glm::vec2 vv(0.0f, 0.0f);
                if (aiMesh->mTextureCoords[0])
                {
                    vv.x = aiMesh->mTextureCoords[0][j].x;
                    vv.y = aiMesh->mTextureCoords[0][j].y;
                }
                vertexData.textureCoord = vv;
                vertexData.color = glm::vec4(128,128,128,0); //设置一个默认颜色。。
                mesh.addVertex(vertexData);
            }

            // 传递面片索引
            for (int j = 0; j < aiMesh->mNumFaces; j++)
            {
                aiFace face = aiMesh->mFaces[j];
                for (int k = 0; k < face.mNumIndices; k++)
                {
                    mesh.addIndex(face.mIndices[k]);
                }
            }

            // 读取材质和贴图
            if(aiMesh->mMaterialIndex >= 0){
                aiMaterial *material = scene->mMaterials[aiMesh->mMaterialIndex];
                // 这里只考虑漫反射贴图了，暂时先不去管镜面反射贴图
                if(material->GetTextureCount(aiTextureType_DIFFUSE) == 0){
                    //没有漫反射贴图，直接读取 ka kd ks
                    std::cout<<"do not has texture, read material"<<std::endl;
                    aiColor3D color;
                    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
                    glm::vec3 ka = glm::vec3(color.r,color.g, color.b);
                    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
                    glm::vec3 kd = glm::vec3(color.r,color.g, color.b);
                    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
                    glm::vec3 ks = glm::vec3(color.r,color.g, color.b);
                    mesh.setMaterial(Material(ka,kd,ks,16.0f)); // set shininess at 16.0f...
                }
                else{
                    //有漫反射贴图，记录 ka ,ks，并且把贴图路径记录下来
                    std::cout<<"has texture"<<std::endl;
                    aiColor3D color;
                    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
                    glm::vec3 ka = glm::vec3(color.r,color.g, color.b);
                    glm::vec3 kd = glm::vec3(0.0f,0.0f, 0.0f);
                    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
                    glm::vec3 ks = glm::vec3(color.r,color.g, color.b);
                    mesh.setMaterial(Material(ka,kd,ks,16.0f)); // set shininess at 16.0f...
                    // 贴图路径
                    aiString _textureUrl;
                    material->GetTexture(aiTextureType_DIFFUSE,0,&_textureUrl);
                    mesh.setTextureUrl(rootPath + "/" + _textureUrl.C_Str());
                }
            }


            // add mesh
            meshes.push_back(mesh);
        }

        return meshes;
    }
}
