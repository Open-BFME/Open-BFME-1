// cl: /DNDEBUG /MD /EHsc

class TextureClass
{
public:
	void Release_Ref();
};

class D3DSurfaceInterface
{
public:
	virtual unsigned long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class W3DMouseSurfaceRef
{
public:
	W3DMouseSurfaceRef();
	W3DMouseSurfaceRef(D3DSurfaceInterface *surface) : m_surface(surface) {}
	~W3DMouseSurfaceRef();
	W3DMouseSurfaceRef &operator=(const W3DMouseSurfaceRef &that)
	{
		D3DSurfaceInterface *oldSurface = m_surface;
		if (oldSurface)
			oldSurface->Release();
		m_surface = that.m_surface;
		return *this;
	}

private:
	D3DSurfaceInterface *m_surface;
};

class Mouse
{
public:
	enum RedrawMode
	{
		RM_WINDOWS,
		RM_W3D,
		RM_POLYGON,
		RM_DX8
	};
	virtual ~Mouse();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void setCursor(int cursor);
};

class Win32Mouse : public Mouse
{
public:
	Win32Mouse();
	virtual ~Win32Mouse();

protected:
	unsigned char m_unmodelled[0x5E24];
	int m_currentCursor;
};

class D3DDeviceInterface;
struct D3DDeviceVTable
{
	void *m_slots[12];
	int (__stdcall *ShowCursor)(D3DDeviceInterface *device, int show);
};
class D3DDeviceInterface
{
public:
	D3DDeviceVTable *m_vtable;
};

class MouseThreadHandle
{
public:
	~MouseThreadHandle();
};

class MouseThreadClass
{
public:
	void Stop();
	bool Is_Running();
	void Execute();
	virtual void Thread_Function();
	unsigned char m_unmodelled[0x50];
	MouseThreadHandle *m_handle;
};

class MouseThreadRunGuard
{
public:
	MouseThreadRunGuard(void *lock, bool acquire);
	MouseThreadRunGuard(void *lock, int acquire);
	~MouseThreadRunGuard();
	bool isRunning() const { return m_running; }

private:
	void *m_lock;
	bool m_running;
};

class MouseThreadGuardOwner
{
public:
	void prepareStop();
	void assign(MouseThreadRunGuard *guard);
};

class W3DMouseDrawInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void draw() = 0;
};

class W3DMouse : public Win32Mouse
{
public:
	W3DMouse();
	virtual ~W3DMouse();
	virtual void setRedrawMode(Mouse::RedrawMode mode);

private:
	void freeD3DAssets();
	void freeW3DAssets();
	void initD3DAssets();
	void initW3DAssets();
	void initPolygonAssets();
	W3DMouseSurfaceRef m_currentD3DSurface[21];
	unsigned char m_gap5E80[8];
	int m_currentPolygonCursor;
	int m_currentD3DCursor;
	int m_currentW3DCursor;
	void *m_camera;
	float m_currentFMS;
	bool m_drawing;
	unsigned char m_gap5E9D[3];
	int m_currentAnimFrame;
	int m_currentD3DFrame;
	int m_currentFrames;
};

extern TextureClass *g_w3dMouseCursorTextures[50][21];
extern void *g_w3dMouseCursorModels[50];
extern void *g_w3dMouseCursorAnims[50];
extern D3DDeviceInterface *g_w3dMouseD3DDevice;
extern MouseThreadClass g_w3dMouseThread;
extern unsigned char g_w3dMouseThreadRunLock;
extern bool g_w3dMouseIsThread;
extern W3DMouseDrawInterface *g_w3dMouseDrawTarget;
extern void *g_w3dMouseCursorImages[50];

W3DMouse::W3DMouse() : m_camera(0)
{
	for (int cursor = 0; cursor < 50; ++cursor)
	{
		for (int frame = 0; frame < 21; ++frame)
		{
			TextureClass *texture = g_w3dMouseCursorTextures[cursor][frame];
			if (texture)
			{
				texture->Release_Ref();
				g_w3dMouseCursorTextures[cursor][frame] = 0;
			}
		}
		g_w3dMouseCursorModels[cursor] = 0;
		g_w3dMouseCursorAnims[cursor] = 0;
	}

	m_currentCursor = 0;
	m_currentD3DFrame = 0;
	m_currentFrames = 0;
	m_currentD3DCursor = 0;
	m_currentW3DCursor = 0;
	m_currentPolygonCursor = 0;
	m_currentAnimFrame = 0;
	m_drawing = false;
	m_currentFMS = 1.0f / 1000.0f;
}

void W3DMouse::freeD3DAssets()
{
	D3DSurfaceInterface *noSurface = 0;
	TextureClass *noTexture = 0;
	for (int frame = 0; frame < 21; ++frame)
		m_currentD3DSurface[frame] = noSurface;

	for (int cursor = 0; cursor < 50; ++cursor)
	{
		for (int frame = 0; frame < 21; ++frame)
		{
			TextureClass *texture = g_w3dMouseCursorTextures[cursor][frame];
			if (texture)
			{
				texture->Release_Ref();
				g_w3dMouseCursorTextures[cursor][frame] = noTexture;
			}
		}
	}
}

W3DMouse::~W3DMouse()
{
	D3DDeviceInterface *device = g_w3dMouseD3DDevice;
	if (device)
	{
		device->m_vtable->ShowCursor(device, 0);
		Win32Mouse::setCursor(2);
	}

	freeD3DAssets();
	freeW3DAssets();

	delete g_w3dMouseThread.m_handle;
	g_w3dMouseThread.m_handle = 0;
	g_w3dMouseThread.Stop();
}

void MouseThreadClass::Thread_Function()
{
	for (;;)
	{
		MouseThreadRunGuard guard(&g_w3dMouseThreadRunLock, true);
		if (!guard.isRunning())
			break;

		g_w3dMouseIsThread = true;
		if (g_w3dMouseDrawTarget)
			g_w3dMouseDrawTarget->draw();
		g_w3dMouseIsThread = false;
	}
}

void W3DMouse::setRedrawMode(Mouse::RedrawMode mode)
{
	int oldCursor = *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x4DA8);
	setCursor(0);
	*reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x10E0) = mode;

	switch (mode)
	{
	case Mouse::RM_WINDOWS:
		if (g_w3dMouseThread.Is_Running())
		{
			reinterpret_cast<MouseThreadGuardOwner *>(&g_w3dMouseThread.m_handle)->prepareStop();
			g_w3dMouseThread.Stop();
		}
		freeD3DAssets();
		freeW3DAssets();
		for (int cursor = 0; cursor < 50; ++cursor)
			g_w3dMouseCursorImages[cursor] = 0;
		m_currentCursor = 0;
		goto resetFrames;

	case Mouse::RM_W3D:
		if (g_w3dMouseThread.Is_Running())
		{
			reinterpret_cast<MouseThreadGuardOwner *>(&g_w3dMouseThread.m_handle)->prepareStop();
			g_w3dMouseThread.Stop();
		}
		freeD3DAssets();
		for (int cursor = 0; cursor < 50; ++cursor)
			g_w3dMouseCursorImages[cursor] = 0;
		m_currentCursor = 0;
		m_currentFrames = 0;
		initW3DAssets();
		goto restoreCursor;

	case Mouse::RM_POLYGON:
		if (g_w3dMouseThread.Is_Running())
		{
			reinterpret_cast<MouseThreadGuardOwner *>(&g_w3dMouseThread.m_handle)->prepareStop();
			g_w3dMouseThread.Stop();
		}
		freeD3DAssets();
		freeW3DAssets();
		m_currentCursor = 0;
		m_currentD3DFrame = 0;
		m_currentFrames = 0;
		initPolygonAssets();
		goto restoreCursor;

	case Mouse::RM_DX8:
		initD3DAssets();
		freeW3DAssets();
		for (int cursor = 0; cursor < 50; ++cursor)
			g_w3dMouseCursorImages[cursor] = 0;
		if (!g_w3dMouseThread.Is_Running())
		{
			MouseThreadRunGuard *guard = new MouseThreadRunGuard(&g_w3dMouseThreadRunLock, -1);
			reinterpret_cast<MouseThreadGuardOwner *>(&g_w3dMouseThread.m_handle)->assign(guard);
			g_w3dMouseThread.Execute();
		}
		break;

	default:
		goto restoreCursor;
	}

resetFrames:
	m_currentD3DFrame = 0;
	m_currentFrames = 0;
restoreCursor:
	setCursor(0);
	setCursor(oldCursor);
}
