#pragma once
#include <gl/GL.h>
#include <Windows.h>

#pragma comment(lib,"opengl32.lib")


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

void RegisterWindowClass(WNDCLASSEX& wcex, HINSTANCE& hInstance) {
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
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}
