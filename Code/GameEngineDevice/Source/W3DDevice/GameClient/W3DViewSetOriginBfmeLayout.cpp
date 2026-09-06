// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?setOrigin@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// Same BFME layout as the landed sibling twin
// Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetWidthBfmeLayout.cpp
// (0x0073DD00 setWidth): W3DView carries m_3DCamera at +0x104 and Display's
// vtable has 11 extra slots before getWidth/getHeight. This body additionally
// needs Display::getHeight right after getWidth (retail +0x30), and the
// View-inherited setWidth/setHeight slots at +0x38/+0x40 (matching the
// BFMERetailTacticalViewVTable comment in Display.cpp). Kept as an
// independent TU rather than editing either landed file.

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
	virtual UnsignedInt getWidth() = 0;			///< +0x2c
	virtual UnsignedInt getHeight() = 0;			///< +0x30
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
	virtual void setWidth(Int width);			///< +0x38
	virtual void d15() = 0;					///< +0x3c (getWidth, unused here)
	virtual void setHeight(Int height);			///< +0x40

	virtual void setOrigin(Int x, Int y);

private:
	unsigned char m_padding04[0x14];
	Int m_width;
	Int m_height;
	Int m_originX;
	Int m_originY;
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

// ?setOrigin@W3DView@@UAEXHH@Z
void W3DView::setOrigin( Int x, Int y)
{
	m_originX = x;
	m_originY = y;

	Vector2 vMin,vMax;

 	m_3DCamera->Get_Viewport(vMin,vMax);
 	vMin.X=(Real)x/(Real)TheDisplay->getWidth();
	vMin.Y=(Real)y/(Real)TheDisplay->getHeight();
 	m_3DCamera->Set_Viewport(vMin,vMax);

	// bottom-right border was also moved my this call, so force an update of extents.
	setWidth(m_width);
	setHeight(m_height);
}
