// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ?tossSegments@W3DRopeDraw@@AAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DRopeDraw.cpp
// readable body of ?xfer@W3DRopeDraw@@MAEXPAVXfer@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DRopeDraw.cpp
// Open-BFME5: convert the retail W3DRopeDraw destructor to clean C++.

#include <vector>

// The drawable module's root base occupies twelve bytes before W3DRopeDraw's
// secondary interface subobject.  The middle base destructor resets the
// primary vtable, then calls this root destructor through 0x0002B8C8.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	float red;
	float green;
	float blue;
};

typedef unsigned char XferVersion;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void slot0();
	virtual bool getXferMode();
	virtual void slot2();
	virtual void slot3();
	virtual bool isDraft();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();

	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void xferRGBColor(RGBColor *val);
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferReal(float *val);
};

class W3DRopeDrawRootBase
{
public:
	virtual ~W3DRopeDrawRootBase();

private:
	unsigned char m_pad[8];
};

class W3DRopeDrawDrawModule : public W3DRopeDrawRootBase
{
public:
	virtual ~W3DRopeDrawDrawModule() {}

protected:
	virtual void xfer(Xfer *xfer);
};

class W3DRopeDrawInterface
{
public:
	virtual void initRopeParms() = 0;
};

class BFME3DScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void Add_Render_Object(void *obj);
	virtual void Remove_Render_Object(void *obj);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	static BFME3DScene *m_3DScene;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/line3d.h
class Line3DClass
{
public:
	virtual void Delete_This();
	int m_numRefs;

	void Release_Ref()
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}
};

struct W3DRopeDrawSegInfo
{
	Line3DClass *line;
	Line3DClass *softLine;
	float wobbleAxisX;
	float wobbleAxisY;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
class W3DRopeDraw : public W3DRopeDrawDrawModule, public W3DRopeDrawInterface
{
public:
	virtual ~W3DRopeDraw();

protected:
	virtual void xfer(Xfer *xfer);


private:
	std::vector<W3DRopeDrawSegInfo> m_segments;
	float m_curLen;
	float m_maxLen;
	float m_width;
	RGBColor m_color;
	float m_curSpeed;
	float m_maxSpeed;
	float m_accel;
	float m_wobbleLen;
	float m_wobbleAmp;
	float m_wobbleRate;
	float m_curWobblePhase;
	float m_curZOffset;

	void tossSegments();
};

#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); (x) = 0; } }

// ?tossSegments@W3DRopeDraw@@AAEXXZ
void W3DRopeDraw::tossSegments()
{
	for (std::vector<W3DRopeDrawSegInfo>::iterator it = m_segments.begin(); it != m_segments.end(); ++it)
	{
		if (it->line)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(it->line);
			REF_PTR_RELEASE(it->line);
		}
		if (it->softLine)
		{
			W3DDisplay::m_3DScene->Remove_Render_Object(it->softLine);
			REF_PTR_RELEASE(it->softLine);
		}
	}
	m_segments.clear();
}

// ?xfer@W3DRopeDraw@@MAEXPAVXfer@@@Z
void W3DRopeDraw::xfer(Xfer *xfer)
{
	W3DRopeDrawDrawModule::xfer(xfer);

	if (!xfer->isDraft())
	{
		XferVersion version[2] = {1, 1};
		xfer->xferVersion(version);

		xfer->xferReal(&m_curLen);
		xfer->xferReal(&m_maxLen);
		xfer->xferReal(&m_width);
		xfer->xferRGBColor(&m_color);
		xfer->xferReal(&m_curSpeed);
		xfer->xferReal(&m_maxSpeed);
		xfer->xferReal(&m_accel);
		xfer->xferReal(&m_wobbleLen);
		xfer->xferReal(&m_wobbleAmp);
		xfer->xferReal(&m_wobbleRate);
		xfer->xferReal(&m_curWobblePhase);
		xfer->xferReal(&m_curZOffset);

		if (xfer->getXferMode())
			tossSegments();
	}
}



// ??1W3DRopeDraw@@UAE@XZ
W3DRopeDraw::~W3DRopeDraw()
{
	tossSegments();
}


