#pragma once
#include <vector>
#include "triangle.h"


std::vector<FBTriangle> GetCube() {
	FBTriangle tri;
	tri.p1 = XMFLOAT3{ 1, -1, -1 };
	tri.p2 = XMFLOAT3(-1, 1, -1);
	tri.p3 = XMFLOAT3(-1, -1, -1);
	tri.n1 = XMFLOAT3(0, 0, -1);
	tri.n2 = XMFLOAT3(0, 0, -1);
	tri.n3 = XMFLOAT3(0, 0, -1);

	FBTriangle tri2;
	tri2.p1 = XMFLOAT3(-1, 1, -1);
	tri2.p2 = XMFLOAT3(1, -1, -1);
	tri2.p3 = XMFLOAT3(1, 1, -1);
	tri2.n1 = XMFLOAT3(0, 0, -1);
	tri2.n2 = XMFLOAT3(0, 0, -1);
	tri2.n3 = XMFLOAT3(0, 0, -1);

	// right
	FBTriangle tri3;
	tri3.p1 = XMFLOAT3(1, -1, -1);
	tri3.p2 = XMFLOAT3(1, -1, 1);
	tri3.p3 = XMFLOAT3(1, 1, 1);
	tri3.n1 = XMFLOAT3(1, 0, 0);
	tri3.n2 = XMFLOAT3(1, 0, 0);
	tri3.n3 = XMFLOAT3(1, 0, 0);


	FBTriangle tri4;
	tri4.p1 = XMFLOAT3(1, -1, -1);
	tri4.p2 = XMFLOAT3(1, 1, 1);
	tri4.p3 = XMFLOAT3(1, 1, -1);
	tri4.n1 = XMFLOAT3(1, 0, 0);
	tri4.n2 = XMFLOAT3(1, 0, 0);
	tri4.n3 = XMFLOAT3(1, 0, 0);

	// back
	FBTriangle tri5;
	tri5.p1 = XMFLOAT3(-1, -1, 1);
	tri5.p2 = XMFLOAT3(1, 1, 1);
	tri5.p3 = XMFLOAT3(1, -1, 1);
	tri5.n1 = XMFLOAT3(0, 0, 1);
	tri5.n2 = XMFLOAT3(0, 0, 1);
	tri5.n3 = XMFLOAT3(0, 0, 1);

	FBTriangle tri6;
	tri6.p1 = XMFLOAT3(1, 1, 1);
	tri6.p2 = XMFLOAT3(-1, -1, 1);
	tri6.p3 = XMFLOAT3(-1, 1, 1);
	tri6.n1 = XMFLOAT3(0, 0, 1);
	tri6.n2 = XMFLOAT3(0, 0, 1);
	tri6.n3 = XMFLOAT3(0, 0, 1);

	// left
	FBTriangle tri7;
	tri7.p1 = XMFLOAT3(-1, -1, 1);
	tri7.p2 = XMFLOAT3(-1, -1, -1);
	tri7.p3 = XMFLOAT3(-1, 1, -1);
	tri7.n1 = XMFLOAT3(-1, 0, 0);
	tri7.n2 = XMFLOAT3(-1, 0, 0);
	tri7.n3 = XMFLOAT3(-1, 0, 0);


	FBTriangle tri8;
	tri8.p1 = XMFLOAT3(-1, -1, 1);
	tri8.p2 = XMFLOAT3(-1, 1, -1);
	tri8.p3 = XMFLOAT3(-1, 1, 1);
	tri8.n1 = XMFLOAT3(-1, 0, 0);
	tri8.n2 = XMFLOAT3(-1, 0, 0);
	tri8.n3 = XMFLOAT3(-1, 0, 0);

	// top
	FBTriangle tri9;
	tri9.p1 = XMFLOAT3(1, 1, -1);
	tri9.p2 = XMFLOAT3(1, 1, 1);
	tri9.p3 = XMFLOAT3(-1, 1, 1);
	tri9.n1 = XMFLOAT3(0, 1, 0);
	tri9.n2 = XMFLOAT3(0, 1, 0);
	tri9.n3 = XMFLOAT3(0, 1, 0);

	FBTriangle tri10;
	tri10.p1 = XMFLOAT3(-1, 1, -1);
	tri10.p2 = XMFLOAT3(1, 1, -1);
	tri10.p3 = XMFLOAT3(-1, 1, 1);
	tri10.n1 = XMFLOAT3(0, 1, 0);
	tri10.n2 = XMFLOAT3(0, 1, 0);
	tri10.n3 = XMFLOAT3(0, 1, 0);

	// bottom
	FBTriangle tri11;
	tri11.p1 = XMFLOAT3(1, -1, -1);
	tri11.p2 = XMFLOAT3(-1, -1, -1);
	tri11.p3 = XMFLOAT3(-1, -1, 1);
	tri11.n1 = XMFLOAT3(0, -1, 0);
	tri11.n2 = XMFLOAT3(0, -1, 0);
	tri11.n3 = XMFLOAT3(0, -1, 0);

	FBTriangle tri12;
	tri12.p1 = XMFLOAT3(-1, -1, 1);
	tri12.p2 = XMFLOAT3(1, -1, 1);
	tri12.p3 = XMFLOAT3(1, -1, -1);
	tri12.n1 = XMFLOAT3(0, -1, 0);
	tri12.n2 = XMFLOAT3(0, -1, 0);
	tri12.n3 = XMFLOAT3(0, -1, 0);

	std::vector<FBTriangle> tris = { tri, tri2, tri3, tri4, tri5, tri6, tri7, tri8,  tri10, tri9, tri11, tri12 };
	return tris;
}

