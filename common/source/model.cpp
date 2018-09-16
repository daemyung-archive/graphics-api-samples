// MIT License
//
// Copyright (c) 2018 DAEMYUNG, JANG
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "common/model.h"

#include <cassert>

Model::Model (std::string const &path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        assert(false);
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode (aiNode *node, const aiScene *scene)
{
    for (auto i = 0; i != node->mNumMeshes; ++i)
    {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (auto i = 0; i != node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh (aiMesh *assimpMesh, const aiScene *scene)
{
    Mesh mesh;

    for (auto i = 0; i != assimpMesh->mNumVertices; ++i)
    {
        Vertex vertex = { };

        if (assimpMesh->HasPositions())
        {
            vertex.position.x = assimpMesh->mVertices[i].x;
            vertex.position.y = assimpMesh->mVertices[i].y;
            vertex.position.z = assimpMesh->mVertices[i].z;
        }

        if (assimpMesh->HasNormals())
        {
            vertex.normal.x = assimpMesh->mNormals[i].x;
            vertex.normal.y = assimpMesh->mNormals[i].y;
            vertex.normal.z = assimpMesh->mNormals[i].z;
        }

        if (assimpMesh->HasTextureCoords(0))
        {
            vertex.texCoords.x = assimpMesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = assimpMesh->mTextureCoords[0][i].y;
        }

        if (assimpMesh->HasTangentsAndBitangents())
        {
            //
        }

        mesh.vertices.push_back(vertex);

    }

    for (auto i = 0; i != assimpMesh->mNumFaces; ++i)
    {
        auto face = assimpMesh->mFaces[i];

        for (auto j = 0; j != face.mNumIndices; ++j)
        {
            mesh.indicies.push_back(face.mIndices[j]);
        }
    }

    if (scene->HasMaterials())
    {
        auto mat = scene->mMaterials[assimpMesh->mMaterialIndex];    
        for (auto i = 0; i != mat->GetTextureCount(aiTextureType_DIFFUSE); ++i)
        {
            aiString texPath;
            mat->GetTexture(aiTextureType_DIFFUSE, i, &texPath);

            std::string fileName = texPath.C_Str();
            auto ridx = fileName.rfind('\\');
            if (std::string::npos == ridx)
            {
                ridx = fileName.rfind('/');
            }

            fileName = fileName.substr(ridx + 1);
            mesh.diffuse = fileName;
        }
    }

    mMeshes.push_back(mesh);
}