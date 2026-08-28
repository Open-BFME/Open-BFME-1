// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?setWidth@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// BFME's W3DView has two additional View vtable entries before getHeight and
// carries its 3D camera at +0x104.  The ordinary W3DView.cpp is compiled
// against the Zero Hour headers, where those two facts are different.  This
// focused lift keeps the retail layout local while retaining the source
// operation order.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "wwmath.h"
#include "vector2.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class ViewportClass
{
public:
	ViewportClass(void) : Min(0, 0), Max(1, 1) {}
	ViewportClass(const Vector2 &min, const Vector2 &max) : Min(min), Max(max) {}
	ViewportClass(const ViewportClass &viewport) : Min(viewport.Min), Max(viewport.Max) {}

	Vector2 Min;
	Vector2 Max;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass
{
public:
	void Set_Aspect_Ratio(float widthToHeight);
	void Set_View_Plane(float horizontalFov, float verticalFov);

	void Get_Viewport(Vector2 &setMin, Vector2 &setMax) const
	{
		setMin = Viewport.Min;
		setMax = Viewport.Max;
	}

	void Set_Viewport(const Vector2 &min, const Vector2 &max)
	{
		Viewport.Min = min;
		Viewport.Max = max;
		FrustumValid = false;
	}

	private:
	virtual void vtableAnchor();
	unsigned char m_padding04[0xCC - 0x04];
	ViewportClass Viewport;
	unsigned char m_paddingDC[0x100 - 0xDC];
	bool FrustumValid;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual UnsignedInt getWidth() = 0;
};

extern Display *TheDisplay;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	virtual void d00() = 0;
	virtual void d01() = 0;
	virtual void d02() = 0;
	virtual void d03() = 0;
	virtual void d04() = 0;
	virtual void d05() = 0;
	virtual void d06() = 0;
	virtual void d07() = 0;
	virtual void d08() = 0;
	virtual void d09() = 0;
	virtual void d10() = 0;
	virtual void d11() = 0;
	virtual void d12() = 0;
	virtual void d13() = 0;
	virtual void d14() = 0;
	virtual void d15() = 0;
	virtual void d16() = 0;
	virtual Int getHeight() = 0;
	virtual void setWidth(Int width);

private:
	unsigned char m_padding04[0x14];
	Int m_width;
	unsigned char m_padding1C[0x04];
	Int m_originX;
	unsigned char m_padding24[0x104 - 0x24];
	CameraClass *m_3DCamera;
};

// ?setWidth@W3DView@@UAEXH@Z
void W3DView::setWidth(Int width)
{
	m_width = width;

	Vector2 vMin, vMax;
	m_3DCamera->Set_Aspect_Ratio((Real)width / (Real)getHeight());
	m_3DCamera->Get_Viewport(vMin, vMax);
	vMax.X = (Real)(m_originX + width) / (Real)TheDisplay->getWidth();
	m_3DCamera->Set_Viewport(vMin, vMax);
	m_3DCamera->Set_View_Plane((Real)width / (Real)TheDisplay->getWidth() * DEG_TO_RADF(50.0f), -1);
}
