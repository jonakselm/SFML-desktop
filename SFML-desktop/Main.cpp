#include "stdafx.h"
#include <sdkddkver.h>
#include "App.hpp"

// Global Variables
HINSTANCE hInst;
HWND hMainWnd;
HWND hExitButton;
HWND hGameButton;
HWND hView0;
HWND hView1;

// Class Objects
StateHandler stateHandler;

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	// Initialize global variables
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// SFML
	sf::RenderWindow wnd0(hView0);
	sf::RenderWindow wnd1(hView1);

	sf::CircleShape circle0(15.f);
	circle0.setFillColor(sf::Color::Magenta);

	sf::CircleShape circle1(15.f);
	circle1.setFillColor(sf::Color::Blue);

	sf::Vector2f screenSize(300, 400);

	// Main message loop
	MSG msg;
	msg.message = ~WM_QUIT;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				circle0.getPosition().y > 0)
				circle0.move(0, -1);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				circle0.getPosition().y < (screenSize.y - 30))
				circle0.move(0, 1);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
				circle0.getPosition().x > 0)
				circle0.move(-1, 0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				circle0.getPosition().x < (screenSize.x - 30))
				circle0.move(1, 0);


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				circle1.getPosition().y > 0)
				circle1.move(0, -1);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				circle1.getPosition().y < (screenSize.y - 30))
				circle1.move(0, 1);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				circle1.getPosition().x > 0)
				circle1.move(-1, 0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				circle1.getPosition().x < (screenSize.x - 30))
				circle1.move(1, 0);


			// SFML rendering code goes here
			wnd0.clear(sf::Color::White);
			wnd0.draw(circle0);
			wnd0.display();

			wnd1.clear();
			wnd1.draw(circle1);
			wnd1.display();
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW mainWnd;

    mainWnd.cbSize = sizeof(WNDCLASSEX);

    mainWnd.style          = CS_HREDRAW | CS_VREDRAW;
    mainWnd.lpfnWndProc    = WndProc;
    mainWnd.cbClsExtra     = 0;
    mainWnd.cbWndExtra     = 0;
    mainWnd.hInstance      = hInstance;
    mainWnd.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    mainWnd.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    mainWnd.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB (0, 255, 0)));
    mainWnd.lpszMenuName   = MAKEINTRESOURCEW(IDR_MAINMENUBAR);
    mainWnd.lpszClassName  = L"SFML-class";
    mainWnd.hIconSm        = LoadIcon(mainWnd.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&mainWnd);

	////
	// Don't know if this is the right place for it
	//
	//UnregisterClassW(mainWnd.lpszClassName, mainWnd.hInstance);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hMainWnd = CreateWindowW(L"SFML-class", L"SFML", WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	// Check if main window is created
	assert(hMainWnd != 0);

	if (!hMainWnd)
	{
		return FALSE;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse menu selections
		switch (wmId)
		{
		case 0:
			PostQuitMessage(0);
			break;
		case 1:
		{
			HWND hGameWnd = CreateWindowW(L"SFML-class", L"Game Selection", WS_VISIBLE | WS_BORDER | WS_SYSMENU,
				CW_USEDEFAULT, 0, 990, 900, hWnd, NULL, hInst, NULL);
			App app;
			app.run(hGameWnd);
		}
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
			break;
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_CREATE:
	{
		// Children
		DWORD childStyle = WS_CHILD | WS_VISIBLE | WS_BORDER;

		hExitButton = CreateWindowW(L"BUTTON", L"Quit", childStyle,
			1330, 630, 80, 40, hWnd, (HMENU) 0, hInst, NULL);

		hView0 = CreateWindowW(L"STATIC", NULL, childStyle,
			50, 100, 300, 400, hWnd, NULL, hInst, NULL);

		hView1 = CreateWindowW(L"STATIC", NULL, childStyle,
			400, 100, 300, 400, hWnd, NULL, hInst, NULL);

		hGameButton = CreateWindowW(L"BUTTON", L"To Game Selection", childStyle,
			1200, 500, 150, 40, hWnd, (HMENU) 1, hInst, NULL);

		// Check if windows are successfully created
		assert(hExitButton != 0);
		assert(hView0 != 0);
		assert(hView1 != 0);
		assert(hGameButton != 0);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}