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

class Win32Mouse
{
public:
	Win32Mouse();
	virtual ~Win32Mouse();

protected:
	unsigned char m_unmodelled[0x5E24];
	int m_currentCursor;
};

class W3DMouse : public Win32Mouse
{
public:
	W3DMouse();
	virtual ~W3DMouse();

private:
	void freeD3DAssets();
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
