
#include <windows.h>
#include <gl/gl.h>
#include <string>
#include "Define.h"
#include "Simulation.h"
#include <chrono>
#include "workGL.h"
#include "KeyManager.h"

#pragma comment(lib, "opengl32.lib")

float lv = 0.5;

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
	KeyManeger keys;

	/* register window class */
	RegisterWindowClass(wcex, hInstance);
	if (!RegisterClassEx(&wcex)) return 0;

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
	if(ms == IDCANCEL) return 0;

	global.Init();
	std::chrono::system_clock::time_point beg = std::chrono::system_clock::now(), end;
	Simulation sim;
	sim.Init(SIMULATION_STARTED_CELLS);

	keys.InsertKey(VK_F4);
	keys.InsertKey(VK_TAB);
	keys.InsertKey(VK_F10);
	keys.InsertKey(VK_F1);

	/* program main loop */
	while (!bQuit) {
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT) {
				ms = DisplayResourceNAMessageBox(NULL, L"Launcher", L"Quit from application?", MB_ICONQUESTION | MB_YESNO);
				if(ms== IDYES) bQuit = TRUE;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			for (int i = 0;i < keys.Size();i++) {
				if (keys.Feel(i)) {
					switch (i) {
						case 0:
							msg.message = WM_QUIT;
							break;
						case 1:
							sim.SwitchMode();
							break;
						case 2:
							AskSettings();
							break;
						case 3:
							AskHelp();
							break;
					}
					Sleep((5000.0 / WINDOW_FREQUENCY));
				}
			}

			/* OpenGL animation code goes here */
			glClearColor(0, 0, 0, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

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
