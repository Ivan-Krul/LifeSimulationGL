
#include <windows.h>
#include <gl/gl.h>
#include <string>
#include "Define.h"
#include "Simulation.h"
#include <chrono>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

float lv = 0.5;

int DisplayResourceNAMessageBox(HWND hwnd, std::wstring title, std::wstring text, UINT type)
{
	int msgboxID = MessageBox(
		hwnd,
		text.c_str(),
		title.c_str(),
		type
	);

	//MB_ICONERROR
	//MB_ICONSTOP
	//MB_ICONHAND
	//MB_ICONQUESTION
	//MB_ICONWARNING
	//MB_ICONEXCLAMATION 
	//MB_ICONINFORMATION
	//MB_ICONASTERISK 

	//IDCANCEL
	//IDTRYAGAIN
	//IDCONTINUE
	//IDABORT
	//IDIGNORE
	//IDNO
	//IDOK
	//IDRETRY
	//IDYES

	return msgboxID;
}

void AskSettings() {
	std::wstring text = L"Application \"LifeSimulationGL\" use this settings\n";
	text += L"Window width = " + std::to_wstring(WINDOW_X) + L'\n';
	text += L"Window heigth = " + std::to_wstring(WINDOW_Y) + L'\n';
	text += L"Window relation = " + std::to_wstring(WINDOW_RELATION) + L'\n';
	text += L"Window frequency = " + std::to_wstring(WINDOW_FREQUENCY) + L'\n';
	text += L'\n';
	text += L"Map width = " + std::to_wstring(MAP_X) + L'\n';
	text += L"Map heigth = " + std::to_wstring(MAP_Y) + L'\n';
	text += L"Map scale = " + std::to_wstring(MAP_SCALE) + L'\n';
	text += L"Map detailness = " + std::to_wstring(MAP_DETAIL_CHANGES) + L'\n';
	text += L"Map octaves = " + std::to_wstring(MAP_NUM_OCTAVES) + L'\n';
	text += L'\n';
	text += L"Cell count of genes = " + std::to_wstring(CELL_COUNT_GENES) + L'\n';
	text += L"Cell chance of mutation = " + std::to_wstring(CELL_CHANCE_MUTATION) + L'\n';
	text += L"Cell started energy = " + std::to_wstring(CELL_STARTED_ENERGY) + L'\n';
	text += L"Cell first number of gene = " + std::to_wstring(CELL_STARTED_NUM_GENE) + L'\n';
	text += L'\n';
	text += L"Simulation started count of cells = " + std::to_wstring(SIMULATION_STARTED_CELLS) + L'\n';

	DisplayResourceNAMessageBox(NULL, L"Settings", text, NULL);
}
void AskHelp() {
	std::wstring text = L"Application \"LifeSimulationGL\" use this keys\n";
	text += L"Quit - ESCAPE\n";
	text += L"Show keys - F1\n";
	text += L"Change vision mode - TAB\n";
	text += L"Restart - F4\n";
	text += L"Change sea level - F6(if decrease), F7(if increase)\n";
	text += L"Show settings - F10\n";

	DisplayResourceNAMessageBox(NULL, L"Key helper", text, NULL);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;
	int ms;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		L"GLSample",
		L"LifeSimulationGL",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_X,
		WINDOW_Y,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	/* enable OpenGL for the window */
	EnableOpenGL(hwnd, &hDC, &hRC);

	ms = DisplayResourceNAMessageBox(NULL, L"Launcher", L"Application \"LifeSimulationGL\" is launched", MB_ICONINFORMATION | MB_OKCANCEL);

	if(ms == IDCANCEL)
		return 0;

	std::chrono::system_clock::time_point beg = std::chrono::system_clock::now(), end;
	Simulation sim;
	sim.Init(SIMULATION_STARTED_CELLS);

	/* program main loop */
	while (!bQuit)
	{

		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */

			if (msg.message == WM_QUIT)
			{
				ms = DisplayResourceNAMessageBox(NULL, L"Launcher", L"Quit from application?", MB_ICONQUESTION | MB_YESNO);
				if(ms== IDYES)
					bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			/* OpenGL animation code goes here */

			//beg = std::chrono::system_clock::now();

			if (GetAsyncKeyState(VK_F4)) {
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(VK_F6)) {
				lv -= 0.01;
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(VK_F7)) {
				lv += 0.01;
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(VK_TAB)) {
				sim.SwitchMode();
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(VK_F10)) {
				AskSettings();
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(VK_F1)) {
				AskHelp();
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}
			if (GetAsyncKeyState(' ')) {
				Sleep((10000.0 / WINDOW_FREQUENCY));
			}


			glClearColor(0, 0, 0, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//sim.Do();
			sim.GeneRetarget();
			sim.GeneSwitch();
			sim.GeneAction();
			sim.Paint();

			SwapBuffers(hDC);

			end = std::chrono::system_clock::now();
			
			std::wstring text = L"LifeSimulationGL " + std::to_wstring(std::chrono::duration_cast<std::chrono::milliseconds>(end - beg).count())+L" ms";

			beg = std::chrono::system_clock::now();

			SetWindowText(hwnd, text.c_str());

			theta += 1.0f;
			Sleep((1000.0/WINDOW_FREQUENCY));
		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hwnd, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}
