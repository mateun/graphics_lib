// TestGameWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestGameWin32.h"
#include <graphics_lib.h>
#include <triangle.h>
#include <basic_3d_objects.h>
#include <importer.h>
#include <string>
#include <scenegraph.h>
#include <scene_node.h>
#include "Player.h"
#include <camera.h>
#include "player_char_go.h"
#include <scene.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

FBGraphics* graphics;							// Our graphics library instance
std::vector<FBTriangle> modelTris;				// Our single global model for now :) 
FBSceneGraph* sceneGraph = nullptr;
FBCamera* camera;								// The camera through which everything is rendered!
PlayerChar* playerChar;							// A game object representing the player char
FBScene* level1;								// A scene representing the first level of the game


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void gameFrame() {

	// move the camera forward...
	static float camZ = 0; camZ += 0.0000f;
	
	XMVECTOR newPos = XMVectorAdd(camera->GetPosition(), XMVectorSet(0, camZ, 0, 0));
	camera->SetPosition(newPos);


	graphics->clear(10, 10, 10);
	auto tris = GetCube();

	static float rotY = 0.0f; rotY += 0.005f;
	//graphics->renderTriangleList(tris, XMVectorSet(-10, 0, 0, 0), XMVectorSet(0, 1, 0, 0), rotY, 1, XMVectorSet(1.0f, 0.2f, 0.2f, 0.0f));
	//graphics->renderTriangleList(tris, XMVectorSet(10, 0, 0, 0), XMVectorSet(0, 0.5f, 0.5f, 0), rotY*1.3, 1, XMVectorSet(0.2f, 0.2f, 1.0f, 0.0f));

	//graphics->renderTriangleList(modelTris, XMVectorSet(0, 0, 0,0), XMVectorSet(0, 1, 0, 0), rotY*1.0f, 1, 1, 1, XMVectorSet(0.7f, 0.3f, 0.6f, 0));

	for (auto i = 0; i < 20; i++) {
		graphics->renderTriangleList(tris, XMVectorSet(-3, 1.0f, -20 + (i*10), 0), XMVectorSet(0, 1, 0, 0), rotY*0, XMVectorSet(0.2f, 1.0f, 0.2f, 0.0f),
			XMVectorSet(0.2f, 1.0f, 0.2f, 0.0f), *camera);
	}

	// now lets test the scenegraph as well
	// TODO calculate real frametime to pass into scenegraph
	sceneGraph->update(16);
	sceneGraph->render(graphics, *camera);

	//playerChar->render(graphics, camera);
	level1->render(*graphics);

	graphics->swapBuffers();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTGAMEWIN32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTGAMEWIN32));

	modelTris = importModel("D:/Projects/C++/graphics_lib/x64/Debug/model.obj");
	sceneGraph = new TreeSceneGraph();
	FBSceneNode* rootNode = new FBSceneNode();
	sceneGraph->addRootNode(rootNode);

	FBSceneNode* playerNode = new Player(modelTris);
	playerNode->position = XMFLOAT3(1, 0, -4);
	
	rootNode->addChild(playerNode);

	camera = new FBCamera(XMVectorSet(0, 5, -15, 0), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0), 1.5f, (float) 800.0f/600.0f, 1, 200);
	
	playerChar = new PlayerChar();
	XMStoreFloat3(&playerChar->_position, XMVectorSet(5, 0, -5, 0));
	playerChar->meshTriangles = modelTris;
	playerChar->_scale = 1.0f;

	PlayerChar* soldier2 = new PlayerChar();
	XMStoreFloat3(&soldier2->_position, XMVectorSet(3, 0, 3, 0));
	soldier2->_scale = 1.0f;
	soldier2->meshTriangles = importModel("D:/Projects/C++/graphics_lib/x64/Debug/soldier.obj");

	level1 = new FBScene();
	level1->addGameObject(playerChar);
	level1->addGameObject(soldier2);
	level1->addCamera(camera);
	level1->setMainCamera(camera);

	
	

    MSG msg;

    // Main message loop:
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		gameFrame();
	}

	delete(graphics);
    

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTGAMEWIN32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTGAMEWIN32);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   graphics = new DX9Graphics(hWnd);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
