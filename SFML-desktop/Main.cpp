#include "stdafx.h"
#include <sdkddkver.h>
#include "App.hpp"
#include <vector>
#include <list>

// Global Variables
HINSTANCE hInst;
HWND hMain;
HWND hView0;
HWND hView1;

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK subProc(HWND, UINT, WPARAM, LPARAM);

ATOM MyRegisterClass(HINSTANCE);

BOOL InitInstance(HINSTANCE, int);

void updateWindow(HWND &hWnd)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	InvalidateRect(hWnd, &clientRect, TRUE);
}

void updateWindow(HWND &hWnd, RECT rect)
{
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, TRUE);
}

void updateWindow(HWND &hWnd, std::vector<RECT> rect)
{
	for (size_t i = 0; i < rect.size(); i++)
	{
		GetClientRect(hWnd, &rect[i]);
		InvalidateRect(hWnd, &rect[i], TRUE);
	}
}

std::vector<std::unique_ptr<App>> &apps()
{
	static std::vector<std::unique_ptr<App>> s_apps;
	return s_apps;
};

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
			for (auto it = apps().begin(); it != apps().end();)
			{
				if ((*it)->frame())
					++it;
				else
					it = apps().erase(it);
			}

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

	ZeroMemory(&mainWnd, sizeof(WNDCLASSEX));

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

	if (!RegisterClassExW(&mainWnd))
	{
		MessageBoxW(hMain, L"Registration of 'Main Wndclass' failed", L"Registration failed", MB_ICONERROR);
		return 0;
	}


	WNDCLASSEXW sub;

	ZeroMemory(&sub, sizeof(WNDCLASSEX));

	sub.cbSize = sizeof(WNDCLASSEX);

	sub.style = CS_HREDRAW | CS_VREDRAW;
	sub.lpfnWndProc = subProc;
	sub.cbClsExtra = 0;
	sub.cbWndExtra = 0;
	sub.hInstance = hInstance;
	sub.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	sub.hCursor = LoadCursor(nullptr, IDC_ARROW);
	sub.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0)));
	sub.lpszMenuName = MAKEINTRESOURCEW(IDR_GAMEMENU);
	sub.lpszClassName = L"Sub-class";
	sub.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassExW(&sub))
	{
		MessageBoxW(hMain, L"Registration of 'Sub Wndclass' failed", L"Registration failed", MB_ICONERROR);
		return 0;
	}

    return RegisterClassExW(&mainWnd);

	////
	// Don't know if this is the right place for it
	//
	//UnregisterClassW(mainWnd.lpszClassName, mainWnd.hInstance);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hMain = CreateWindowExW(NULL, L"SFML-class", L"SFML", WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	// Check if main window is created
	assert(hMain != 0);

	if (!hMain)
	{
		return FALSE;	
	}

	ShowWindow(hMain, nCmdShow);
	UpdateWindow(hMain);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// No point in using enum class, as the case has to be of type int
	enum button { Quit, GameWindow, MB, backgroundButton };

	PAINTSTRUCT ps;
	HDC hDC;

	static RECT rect, testRect;

	static bool changeBackground = false;

	switch (msg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse menu selections
		switch (wmId)
		{
		case Quit:
			PostQuitMessage(0);
			break;
		case ID_OPEN_GAMEWINDOW:
		case GameWindow:
		{
			HWND hGameWnd = CreateWindowExW(NULL, L"Sub-class", L"Game Selection", WS_SYSMENU,
				CW_USEDEFAULT, 0, 990, 900, hWnd, NULL, hInst, NULL);
			assert(hGameWnd != 0);

			ShowWindow(hGameWnd, SW_SHOWDEFAULT);
			
			auto &newGame = apps().emplace_back();
			newGame = std::make_unique<App>();
			newGame->init(hGameWnd);
		}
			break;
		case MB:
		{
			int mb = 0;
			while ((mb = MessageBoxExW(hWnd, L"Noge tull", L"TulleBoks", MB_ABORTRETRYIGNORE | MB_ICONERROR, NULL)) == IDRETRY);
			
			switch (mb)
			{
			case IDABORT:
				SetRect(&rect, 500, 0, 600, 50);
				updateWindow(hWnd);
				break;
			case IDIGNORE:
				SetRect(&testRect, 0, 0, 400, 500);
				updateWindow(hWnd);
				break;
			default:
				break;
			}
		}
		break;
		case ID_FILE_BACKGROUNDTODESKTOP:
		case backgroundButton:
			changeBackground = !changeBackground;
			updateWindow(hWnd);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);

		if (changeBackground)
			PaintDesktop(hDC);

		if (RectVisible(hDC, &rect))
			FillRect(hDC, &rect, CreateSolidBrush(RGB(0, 0, 0)));

		if (RectVisible(hDC, &testRect))
			FillRect(hDC, &testRect, CreateSolidBrush(RGB(0, 0, 0)));

		EndPaint(hWnd, &ps);
	}
		break;
	case WM_KEYDOWN:
	{
		int keyId = LOWORD(wParam);

		switch (keyId)
		{
		case ' ':
				changeBackground = !changeBackground;
				updateWindow(hWnd, rect);
			break;
		case 'E':
		case VK_ESCAPE:
		{
			SetRectEmpty(&rect);
			SetRectEmpty(&testRect);
			std::vector<RECT> v_rect = { rect, testRect };
			updateWindow(hWnd, v_rect);
		}
			break;
		case 'R':
		{
			SetRect(&testRect, 0, 0, 400, 500);
			SetRect(&rect, 500, 0, 600, 50);
			std::vector<RECT> v_rect = { rect, testRect };
			updateWindow(hWnd, v_rect);
			break;
		}
		}
	}
		break;
	case WM_KEYUP:
	{
		int keyId = LOWORD(wParam);

		switch (keyId)
		{
		case VK_ESCAPE:
			break;
		default:
			break;
		}
	}
		break;
	case WM_CREATE:
	{
		// Children
		DWORD childStyle = WS_CHILD | WS_VISIBLE | WS_BORDER;

		HWND hExitButton = CreateWindowExW(NULL, L"BUTTON", L"Quit", childStyle,
			1330, 630, 80, 40, hWnd, (HMENU) Quit, hInst, NULL);

		hView0 = CreateWindowExW(NULL, L"STATIC", NULL, childStyle,
			50, 100, 300, 400, hWnd, NULL, hInst, NULL);

		hView1 = CreateWindowExW(NULL, L"STATIC", NULL, childStyle,
			400, 100, 300, 400, hWnd, NULL, hInst, NULL);

		HWND hGameButton = CreateWindowExW(NULL, L"BUTTON", L"To Game Selection", childStyle,
			1200, 500, 150, 40, hWnd, (HMENU) GameWindow, hInst, NULL);

		HWND hMbButton = CreateWindowExW(NULL, L"BUTTON", L"MessageBox", childStyle,
			0, 0, 110, 40, hWnd, (HMENU)MB, hInst, NULL);

		HWND hBackgroundButton = CreateWindowExW(NULL, L"BUTTON", L"Background to Desktop", childStyle,
			0, 600, 175, 40, hWnd, (HMENU)backgroundButton, hInst, NULL);

		// Check if windows are successfully created
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK subProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	enum Button { Quit };
	switch (msg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		
		switch (wmId)
		{
		case ID_GAME_EXIT:
			DestroyWindow(hWnd);
			break;
		}
	}
	break;
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}