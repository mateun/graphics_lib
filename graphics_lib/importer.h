#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "triangle.h"
#include <string>
#include <stdexcept>


// Blender import notes:
// set .obj settings to 
// - no edges
// - forward = -z
// - up = y
// selected objects only
std::vector<FBTriangle> importModel(const std::string& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |aiProcess_FlipWindingOrder );

	if (!scene) {
		throw std::runtime_error("error importing the file");
	}


	std::vector<FBTriangle> tris;
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
			aiFace face = mesh->mFaces[f];
			int findices = face.mNumIndices;
			int i0 = face.mIndices[0];
			int i1 = face.mIndices[1];
			int i2 = face.mIndices[2];

			aiVector3D p1 = mesh->mVertices[i0];
			aiVector3D p2 = mesh->mVertices[i1];
			aiVector3D p3 = mesh->mVertices[i2];

			aiVector3D n1 = mesh->mNormals[i0];
			aiVector3D n2 = mesh->mNormals[i1];
			aiVector3D n3 = mesh->mNormals[i2];

			FBTriangle tri;
			tri.p1 = XMFLOAT3(p1.x, p1.y, p1.z);
			tri.p2 = XMFLOAT3(p2.x, p2.y, p2.z);
			tri.p3 = XMFLOAT3(p3.x, p3.y, p3.z);
			tri.n1 = XMFLOAT3(n1.x, n1.y, n1.z);
			tri.n2 = XMFLOAT3(n2.x, n2.y, n2.z);
			tri.n3 = XMFLOAT3(n3.x, n3.y, n3.z);
			tris.push_back(tri);
		}
	
		

	}

	return tris;
}

