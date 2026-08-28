// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef unsigned long UnsignedLong;

struct BfmeRect
{
	long left;
	long top;
	long right;
	long bottom;
};

extern "C" __declspec(dllimport) Int __stdcall IsRectEmpty(const BfmeRect *rect);

class SurfaceResource
{
public:
	virtual void unused00();
	virtual UnsignedLong __stdcall addRef();
};

class W3DRadarResetSurface
{
public:
	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}

	~W3DRadarResetSurface();

private:
	SurfaceResource *m_surface;
};

struct ImageSurfaceState
{
	char unused00[0x10];
	UnsignedLong status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class Image
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
	virtual const W3DRadarResetSurface &getSurface() const;

	char padding04[0x08];
	Int width;
	Int height;
	char padding14[0x14];
	unsigned char ready;
	char padding29[0x17];
	ImageSurfaceState *surfaceState;
};

W3DRadarResetSurface getBackBufferSurface006e(Int index);
void copySurfaceRects006e(W3DRadarResetSurface source, const BfmeRect *sourceRect,
	W3DRadarResetSurface destination, const BfmeRect *destinationRect, Int mode);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
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
	virtual void unused18();
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
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void drawImageCore(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);
	virtual void endImageDraw();
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);
};

// ?drawImage@W3DDisplay@@UAEXPAVImage@@MMMMH@Z
void W3DDisplay::drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color)
{
	if (!image->ready)
		return;

	if (image->surfaceState && (image->surfaceState->status & 4))
	{
		W3DRadarResetSurface source = image->getSurface();
		W3DRadarResetSurface destination = getBackBufferSurface006e(0);
		BfmeRect sourceRect = { 0, 0, image->width, image->height };
		BfmeRect destinationRect = { (long)x0, (long)y0, (long)x1, (long)y1 };

		if (!IsRectEmpty(&sourceRect) && !IsRectEmpty(&destinationRect))
			copySurfaceRects006e(source, &sourceRect, destination, &destinationRect, 2);
	}
	else
	{
		beginImageDraw();
		drawImageCore(image, x0, y0, x1, y1, color);
		endImageDraw();
	}
}
