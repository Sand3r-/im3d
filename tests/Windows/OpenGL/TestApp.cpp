#include "TestApp.h"

#include "common.h"

#include "GL/wglew.h"
#include <cstring>
#include <cstdio>

using namespace Im3d;

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormat = 0;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs = 0;


/*******************************************************************************

                                  TestApp

*******************************************************************************/

struct TestApp::Impl
{
 // window
	HWND   m_hwnd;

	static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam);

	bool initWindow(int& _width_, int& _height_, const char* _title);

 // gl context
	HDC    m_hdc;
	HGLRC  m_hglrc;

	bool initGl(int _vmaj, int _vmin);

};

LRESULT CALLBACK TestApp::Impl::WindowProc(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_umsg) {
	case WM_PAINT:
		//IM3D_ASSERT(false); // should be suppressed by calling ValidateRect()
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0; // prevent DefWindowProc from destroying the window
	default:
		break;
	};
	return DefWindowProc(_hwnd, _umsg, _wparam, _lparam);
}

bool TestApp::Impl::initWindow(int& _width_, int& _height_, const char* _title)
{
	static ATOM wndclassex = 0;
	if (wndclassex == 0) {
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;// | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = Impl::WindowProc;
		wc.hInstance = GetModuleHandle(0);
		wc.lpszClassName = "Im3dTestApp";
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		IM3D_PLATFORM_VERIFY(wndclassex = RegisterClassEx(&wc));
	}

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	if (_width_ == -1 || _height_ == -1) {
	 // auto size; get the dimensions of the primary screen area and subtract the non-client area
		RECT r;
		IM3D_PLATFORM_VERIFY(SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0));
		_width_  = r.right - r.left;
		_height_ = r.bottom - r.top;

		RECT wr = {};
		IM3D_PLATFORM_VERIFY(AdjustWindowRectEx(&wr, dwStyle, FALSE, dwExStyle));
		_width_  -= wr.right - wr.left;
		_height_ -= wr.bottom - wr.top;
	}

	RECT r; r.top = 0; r.left = 0; r.bottom = _height_; r.right = _width_;
	IM3D_PLATFORM_VERIFY(AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle));
	m_hwnd = CreateWindowEx(
		dwExStyle, 
		MAKEINTATOM(wndclassex), 
		_title, 
		dwStyle, 
		0, 0, 
		r.right - r.left, r.bottom - r.top, 
		NULL, 
		NULL, 
		GetModuleHandle(0), 
		NULL
		);
	IM3D_ASSERT(m_hwnd);
	return true;
}

bool TestApp::Impl::initGl(int _vmaj, int _vmin)
{
	// create dummy context for extension loading
	static ATOM wndclassex = 0;
	if (wndclassex == 0) {
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;// | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = DefWindowProc;
		wc.hInstance = GetModuleHandle(0);
		wc.lpszClassName = "Im3dTestApp_GlDummy";
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		IM3D_PLATFORM_VERIFY(wndclassex = RegisterClassEx(&wc));
	}
	HWND hwndDummy = CreateWindowEx(0, MAKEINTATOM(wndclassex), 0, NULL, 0, 0, 1, 1, NULL, NULL, GetModuleHandle(0), NULL);
	IM3D_PLATFORM_ASSERT(hwndDummy);
	HDC hdcDummy = 0;
	IM3D_PLATFORM_VERIFY(hdcDummy = GetDC(hwndDummy));	
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	IM3D_PLATFORM_VERIFY(SetPixelFormat(hdcDummy, 1, &pfd));
	HGLRC hglrcDummy = 0;
	IM3D_PLATFORM_VERIFY(hglrcDummy = wglCreateContext(hdcDummy));
	IM3D_PLATFORM_VERIFY(wglMakeCurrent(hdcDummy, hglrcDummy));
	
 // check the platform supports the requested GL version
	GLint platformVMaj, platformVMin;
	glAssert(glGetIntegerv(GL_MAJOR_VERSION, &platformVMaj));
	glAssert(glGetIntegerv(GL_MINOR_VERSION, &platformVMin));
	if (platformVMaj < _vmaj || (platformVMaj >= _vmaj && platformVMin < _vmin)) {
		fprintf(stderr, "OpenGL version %d.%d is not available (max version is %d.%d)\n", _vmaj, _vmin, platformVMaj, platformVMin);
		fprintf(stderr, "\t(This error may occur if the platform has an integrated GPU)\n");
		return false;
	}
	

 // load wgl extensions for true context creation
	IM3D_PLATFORM_VERIFY(wglChoosePixelFormat = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB"));
	IM3D_PLATFORM_VERIFY(wglCreateContextAttribs = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB"));

 // delete the dummy context
	IM3D_PLATFORM_VERIFY(wglMakeCurrent(0, 0));
	IM3D_PLATFORM_VERIFY(wglDeleteContext(hglrcDummy));
	IM3D_PLATFORM_VERIFY(ReleaseDC(hwndDummy, hdcDummy) != 0);
	IM3D_PLATFORM_VERIFY(DestroyWindow(hwndDummy) != 0);

 // create true context
	IM3D_PLATFORM_VERIFY(m_hdc = GetDC(m_hwnd));
	const int pfattr[] = {
		WGL_SUPPORT_OPENGL_ARB, 1,
		WGL_DRAW_TO_WINDOW_ARB, 1,
		WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
		WGL_DOUBLE_BUFFER_ARB,  1,
		WGL_COLOR_BITS_ARB,     24,
		WGL_ALPHA_BITS_ARB,     8,
		WGL_DEPTH_BITS_ARB,     0,
		WGL_STENCIL_BITS_ARB,   0,
		0
	};
    int pformat = -1, npformat = -1;
	IM3D_PLATFORM_VERIFY(wglChoosePixelFormat(m_hdc, pfattr, 0, 1, &pformat, (::UINT*)&npformat));
	IM3D_PLATFORM_VERIFY(SetPixelFormat(m_hdc, pformat, &pfd));
	int profileBit = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
	int attr[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,	_vmaj,
		WGL_CONTEXT_MINOR_VERSION_ARB,	_vmin,
		WGL_CONTEXT_PROFILE_MASK_ARB,	profileBit,
		0
	};
	IM3D_PLATFORM_VERIFY(m_hglrc = wglCreateContextAttribs(m_hdc, 0, attr));

 // load extensions
	if (!wglMakeCurrent(m_hdc, m_hglrc)) {
		fprintf(stderr, "wglMakeCurrent failed");
		return false;
	}
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	IM3D_ASSERT(err == GLEW_OK);
	glGetError(); // clear any errors caused by glewInit()

	fprintf(stdout, "OpenGL context:\n\tVersion: %s\n\tGLSL Version: %s\n\tVendor: %s\n\tRenderer: %s",
		GlGetString(GL_VERSION),
		GlGetString(GL_SHADING_LANGUAGE_VERSION),
		GlGetString(GL_VENDOR),
		GlGetString(GL_RENDERER)
		);
	return true;
}


// PUBLIC

TestApp::TestApp()
	: m_impl(nullptr)
{
}

bool TestApp::init(int _width, int _height, const char* _title)
{
	shutdown();
	
	m_impl = new Impl;
	
	m_width = _width;
	m_height = _height;
	m_title = _title;
	
	if (!m_impl->initWindow(m_width, m_height, m_title)) {
		shutdown();
		return false;
	}
	if (!m_impl->initGl(4, 5)) {
		shutdown();
		return false;
	}

	ShowWindow(m_impl->m_hwnd, SW_SHOW);
	return true;
}

void TestApp::shutdown()
{
	if (m_impl) {
		IM3D_PLATFORM_VERIFY(wglMakeCurrent(0, 0));
		IM3D_PLATFORM_VERIFY(wglDeleteContext(m_impl->m_hglrc));
		IM3D_PLATFORM_VERIFY(ReleaseDC(m_impl->m_hwnd, m_impl->m_hdc) != 0);
		IM3D_PLATFORM_VERIFY(DestroyWindow(m_impl->m_hwnd));
		delete m_impl;
	}
}

bool TestApp::update()
{
	MSG msg;
	while (PeekMessage(&msg, (HWND)m_impl->m_hwnd, 0, 0, PM_REMOVE) && msg.message != WM_QUIT) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message != WM_QUIT;
}

void TestApp::draw()
{
	IM3D_PLATFORM_VERIFY(SwapBuffers(m_impl->m_hdc));
	IM3D_PLATFORM_VERIFY(ValidateRect(m_impl->m_hwnd, 0)); // suppress WM_PAINT
}