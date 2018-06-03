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
			tri.p1 = XMVectorSet(p1.x, p1.y, p1.z, 0);
			tri.p2 = XMVectorSet(p2.x, p2.y, p2.z, 0);
			tri.p3 = XMVectorSet(p3.x, p3.y, p3.z, 0);
			tri.n1 = XMVectorSet(n1.x, n1.y, n1.z, 0);
			tri.n2 = XMVectorSet(n2.x, n2.y, n2.z, 0);
			tri.n3 = XMVectorSet(n3.x, n3.y, n3.z, 0);
			tris.push_back(tri);
		}
	
		

	}

	return tris;
}

