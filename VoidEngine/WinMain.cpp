#pragma once
#include <Windows.h>
#include "Vengine.h"
#include "Graphics.h"


Vengine* vengine;
Graphics* graphics;

HWND windowHandle;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CLOSE: {
		DestroyWindow(hwnd);
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,PSTR cmdLine,int showCmd){
	

	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = 0;

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = "Vengine Class";
	wc.lpszMenuName = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

	RegisterClassEx(&wc);


	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	windowHandle = CreateWindowEx(
						WS_EX_OVERLAPPEDWINDOW,
						"Vengine Class",
						"First Window!",
						WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						100, 100,
						rect.right - rect.left, rect.bottom - rect.top,
						0,
						0,
						hInstance,
						0
					);

	if (windowHandle == 0)
		MessageBox(0, "Create Window failed!", "error", 0);

	// Init engine
	vengine = new Vengine();
	vengine->Start();

	// Init graphics
	graphics = new Graphics();

	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}



	ShowWindow(windowHandle, showCmd);
	UpdateWindow(windowHandle);




	MSG msg;
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //not waiting for message
		{
			DispatchMessage(&msg);
		}
		else
		{
	
			vengine->Update();

			graphics->BeginDraw();

			vengine->Render(graphics);

			graphics->EndDraw();
			
		}
	}


	delete graphics;

	return (int)msg.wParam;
}