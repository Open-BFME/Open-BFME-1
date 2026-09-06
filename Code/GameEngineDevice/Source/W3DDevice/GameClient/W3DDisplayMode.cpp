// cl: /DNDEBUG /MD /EHsc
// readable body of ?setWidth@W3DDisplay@@UAEXI@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?setHeight@W3DDisplay@@UAEXI@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?setDisplayMode@W3DDisplay@@UAE_NIII_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?setGamma@W3DDisplay@@UAEXMMM_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
//
// The four W3DDisplay overrides that change the mode the device is running in:
// the two extent setters, the resolution change they are the pieces of, and the
// gamma ramp. Three files carried three copies of Display, of W3DDisplay, and
// -- twice each -- of RectClass, Render2DClass and the reset guard; 219 lines
// become 156.
//
// One W3DDisplay declaration is what the merge buys. Each copy described the
// object as the one field its own body reached, so setGamma's could see
// m_windowed at +0x14 and stop, while the other two started their padding at
// +0x04 and ran straight past it to m_2DRender at +0x164. The union below says
// both, and all four bodies byte-verify against it.

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

// The lock is taken by a scope guard, not by a pair of calls: retail unwinds it
// through an EH funclet, which is what puts the /EHsc frame on setDisplayMode
// and setGamma.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	void Set_Coordinate_Range(const RectClass &range);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Gamma(float gamma, float bright, float contrast, bool calibrate, bool uselimit);
};

// 0x008FD1C0 calls DX8Wrapper::Set_Device_Resolution (0x00908EC0) then
// test al,al / setne al / ret -- BOOL in AL, not WW3DErrorType.
class WW3D
{
public:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay : public Display
{
public:
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed);
	virtual void setGamma(float gamma, float bright, float contrast, bool calibrate);

private:
	unsigned char m_unmodelled_04[0x14 - 0x04];
	unsigned char m_windowed;                       // +0x14, gamma is a no-op in a window
	unsigned char m_unmodelled_15[0x164 - 0x15];
	Render2DClass *m_2DRender;                      // +0x164
};

// ?setWidth@W3DDisplay@@UAEXI@Z
void W3DDisplay::setWidth(unsigned int width)
{
	Display::setWidth(width);
	m_2DRender->Set_Coordinate_Range(RectClass(0, 0, (float)getWidth(), (float)getHeight()));
}

// ?setHeight@W3DDisplay@@UAEXI@Z
void W3DDisplay::setHeight(unsigned int height)
{
	Display::setHeight(height);
	m_2DRender->Set_Coordinate_Range(RectClass(0, 0, (float)getWidth(), (float)getHeight()));
}

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

// ?setGamma@W3DDisplay@@UAEXMMM_N@Z
void W3DDisplay::setGamma(float gamma, float bright, float contrast, bool calibrate)
{
	if (m_windowed)
		return;

	W3DRadarResetGuard lock;
	DX8Wrapper::Set_Gamma(gamma, bright, contrast, calibrate, false);
}
