// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned long UnsignedLong;

class SurfaceResource
{
public:
	virtual void unused00();
	virtual UnsignedLong __stdcall addRef();
	virtual UnsignedLong __stdcall release();
};

class BfmeD3DDevice
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual UnsignedLong __stdcall getBackBuffer(
		unsigned swapChain, unsigned backBuffer, unsigned type, SurfaceResource **surface);
};

extern BfmeD3DDevice *g_bfmeD3DDevice;
extern unsigned g_bfmeD3DCallCount;

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(SurfaceResource *surface);
	W3DRadarResetSurface(unsigned width, unsigned height, unsigned format, unsigned pool);

	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}

	~W3DRadarResetSurface();

private:
	SurfaceResource *m_surface;
};

W3DRadarResetSurface getBackBufferSurface006e(Int index)
{
	SurfaceResource *surface = 0;
	g_bfmeD3DDevice->getBackBuffer(0, index, 0, &surface);
	++g_bfmeD3DCallCount;

	if (surface)
	{
		W3DRadarResetSurface result(surface);
		surface->release();
		surface = 0;
		return result;
	}

	return W3DRadarResetSurface(0x40, 0x40, 0x16, 2);
}
