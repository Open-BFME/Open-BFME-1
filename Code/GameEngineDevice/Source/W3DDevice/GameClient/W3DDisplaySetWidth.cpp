// cl: /DNDEBUG /MD /EHsc
// readable body of ?setWidth@W3DDisplay@@UAEXI@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?setHeight@W3DDisplay@@UAEXI@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay : public Display
{
public:
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);

private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_2DRender;
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
