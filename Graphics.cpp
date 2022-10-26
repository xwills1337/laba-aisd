#include "Graphics.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <exception>
#include <mutex>
#include <thread>
#include <condition_variable>

#pragma comment (lib,"Gdiplus.lib")

namespace gdi = Gdiplus;

namespace Internal {
	struct GraphicsInternals {
		gdi::Graphics graphics;
		GraphicsInternals(HDC hdc) : graphics(hdc) {}
	};
};




static gdi::GdiplusStartupInput gdiplusStartupInput;
static ULONG_PTR           gdiplusToken;
MSG                 msg;
std::once_flag gdi_init_flag;


auto classname = L"class62xx";
static void init_gdi() {
	gdi::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	WNDCLASSEXW wndclass = { sizeof(WNDCLASSEX), 0, DefWindowProc,
							0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
							LoadCursor(0,IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH),
							0,classname, LoadIcon(0,IDI_APPLICATION) };
	RegisterClassEx(&wndclass);
}


static void make_window(const LPCWSTR name, int w, int h, HWND* result, std::condition_variable& cv, std::mutex& m) {
	std::call_once(gdi_init_flag, init_gdi);
	HWND window;
	{
		std::unique_lock<std::mutex> lk(m);
		window = CreateWindowEx(0, classname, name,
			WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT,
			w, h, 0, 0, GetModuleHandle(0), 0);

		if (window)
			ShowWindow(window, SW_SHOWDEFAULT);

		UpdateWindow(window);
		*result = window;
	}
	cv.notify_one();
	if (!window)
		return;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

Graphics::Graphics(size_t w, size_t h)
{
	std::mutex m;
	std::condition_variable cv;

	HWND window = NULL;

	{
		std::unique_lock<std::mutex> l{ m };
		std::thread t(make_window, L"Graphics", w, h, &window, std::ref(cv), std::ref(m));
		cv.wait(l);
		t.detach();
	}

	if (!window)
		throw std::exception("Failed to create window");

	auto hdc = GetDC(window);
	auto* p = new Internal::GraphicsInternals{ hdc };
	_internals = std::unique_ptr<Internal::GraphicsInternals>(p);

}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, Color color)
{
	Gdiplus::Pen p(Gdiplus::Color(color.R, color.G, color.B));
	_internals->graphics.DrawLine(&p, gdi::PointF(x1, y1), gdi::PointF(x2, y2));
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, Color color)
{
	Gdiplus::Pen p(Gdiplus::Color(color.R, color.G, color.B));
	_internals->graphics.FillRectangle(p.GetBrush(), gdi::RectF(x1, y1, x2 - x1, y2 - y1));
}

void Graphics::DrawSquare(float x, float y, float a, Color color)
{
	this->DrawRectangle(x, y, x + a, y + a, color);
}

Graphics::~Graphics() = default;