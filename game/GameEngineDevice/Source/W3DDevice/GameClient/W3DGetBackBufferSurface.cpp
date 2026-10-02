// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD /EHsc
#include "dx8wrapper.h"


typedef int Int;
typedef unsigned long UnsignedLong;

struct BfmeRect;

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
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void __stdcall copySurfaceRects(SurfaceResource *source, const BfmeRect *sourceRect,
		SurfaceResource *destination, const BfmeRect *destinationRect, Int mode);
};

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

	__forceinline SurfaceResource *getSurface() const
	{
		return m_surface;
	}

private:
	SurfaceResource *m_surface;
};

W3DRadarResetSurface getBackBufferSurface006e(Int index)
{
	SurfaceResource *surface = 0;
	reinterpret_cast<BfmeD3DDevice *>(DX8Wrapper::_Get_D3D_Device8())->getBackBuffer(0, index, 0, &surface);
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

void copySurfaceRects006e(W3DRadarResetSurface source, const BfmeRect *sourceRect,
	W3DRadarResetSurface destination, const BfmeRect *destinationRect, Int mode)
{
	reinterpret_cast<BfmeD3DDevice *>(DX8Wrapper::_Get_D3D_Device8())->copySurfaceRects(
		source.getSurface(), sourceRect, destination.getSurface(), destinationRect, mode);
	++g_bfmeD3DCallCount;
}
