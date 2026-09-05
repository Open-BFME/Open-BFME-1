// cl: /DNDEBUG /MD /EHsc
// readable body of ?setDisplayMode@W3DDisplay@@UAE_NIII_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

class RectClass
{
public:
	RectClass(float left, float top, float right, float bottom)
	{
		Left = left;
		Top = top;
		Right = right;
		Bottom = bottom;
	}

	float Left;
	float Top;
	float Right;
	float Bottom;
};

class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
};

// 0x008FD1C0 calls DX8Wrapper::Set_Device_Resolution (0x00908EC0) then
// test al,al / setne al / ret — BOOL in AL, not WW3DErrorType.
class WW3D
{
public:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
};

class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void setBitDepth(unsigned int bitDepth);
	virtual unsigned int getBitDepth();
	virtual void setWindowed(bool windowed);
	virtual bool getWindowed();
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed);
};

class W3DDisplay : public Display
{
public:
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed);

private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_2DRender;
};

// ?setDisplayMode@W3DDisplay@@UAE_NIII_N@Z
bool W3DDisplay::setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed)
{
	W3DRadarResetGuard lock;
	if (WW3D::Set_Device_Resolution((int)xres, (int)yres, (int)bitdepth, (int)windowed, true) == true)
	{
		m_2DRender->Set_Coordinate_Range(RectClass(0, 0, (float)xres, (float)yres));
		Display::setDisplayMode(xres, yres, bitdepth, windowed);
		return true;
	}

	WW3D::Set_Device_Resolution((int)getWidth(), (int)getHeight(), (int)getBitDepth(), (int)getWindowed(), true);
	Display::setDisplayMode(getWidth(), getHeight(), getBitDepth(), getWindowed());
	return false;
}
