// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

extern bool ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1,
	ICoord2D *c2, IRegion2D *clipRegion);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
class RectClass
{
public:
	RectClass(float left, float top, float right, float bottom) :
		Left(left), Top(top), Right(right), Bottom(bottom) {}

	float Left;
	float Top;
	float Right;
	float Bottom;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void Add_Outline(const RectClass &rect, float width, UnsignedInt color);
	void disableTexturing() { m_texturingEnabled = 0; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_render2D;
	IRegion2D m_clipRegion;
	unsigned char m_clippingEnabled;

public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45();
	virtual void drawLine(float startX, float startY, float endX, float endY,
		float lineWidth, UnsignedInt lineColor);
	virtual void drawOpenRect(float startX, float startY, float width, float height,
		float lineWidth, UnsignedInt lineColor);
};

// ?drawOpenRect@W3DDisplay@@UAEXMMMMMK@Z
void W3DDisplay::drawOpenRect(float startX, float startY, float width, float height,
	float lineWidth, UnsignedInt lineColor)
{
	if (m_clippingEnabled) {
		ICoord2D start, end, returnStart, returnEnd;
		start.x = static_cast<int>(startX);
		start.y = static_cast<int>(startY);
		end.x = start.x;
		end.y = static_cast<int>(start.y + height);
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLine(static_cast<float>(returnStart.x), static_cast<float>(returnStart.y),
				static_cast<float>(returnEnd.x), static_cast<float>(returnEnd.y), lineWidth, lineColor);

		end.x = static_cast<int>(start.x + width);
		end.y = start.y;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLine(static_cast<float>(returnStart.x), static_cast<float>(returnStart.y),
				static_cast<float>(returnEnd.x), static_cast<float>(returnEnd.y), lineWidth, lineColor);

		start.x = static_cast<int>(startX + width);
		start.y = static_cast<int>(startY);
		end.x = start.x;
		end.y = static_cast<int>(start.y + height);
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLine(static_cast<float>(returnStart.x), static_cast<float>(returnStart.y),
				static_cast<float>(returnEnd.x), static_cast<float>(returnEnd.y), lineWidth, lineColor);

		start.x = static_cast<int>(startX);
		start.y = static_cast<int>(startY + height);
		end.x = static_cast<int>(start.x + width);
		end.y = start.y;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLine(static_cast<float>(returnStart.x), static_cast<float>(returnStart.y),
				static_cast<float>(returnEnd.x), static_cast<float>(returnEnd.y), lineWidth, lineColor);
	} else {
		m_render2D->disableTexturing();
		m_render2D->Add_Outline(RectClass(startX, startY, startX + width, startY + height),
			lineWidth, lineColor);
	}
}
