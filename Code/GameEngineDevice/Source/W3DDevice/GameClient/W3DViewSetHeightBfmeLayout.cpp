// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?setHeight@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp
//
// Same BFME layout as the landed sibling twins
// Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetWidthBfmeLayout.cpp (setWidth, 0x0073DD00)
// and W3DViewSetOriginBfmeLayout.cpp (setOrigin, 0x0073DE40): W3DView carries
// m_3DCamera at +0x104, View's own getWidth at vtable +0x3c, and Display's
// getWidth/getHeight at +0x2c/+0x30. Kept as an independent TU rather than
// editing the other landed W3DView twins.

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
	virtual void d14() = 0;				///< +0x38 (setWidth, unused here)
	virtual Int getWidth() = 0;			///< +0x3c

	virtual void setHeight(Int height);

private:
	unsigned char m_padding04[0x14];
	Int m_width;
	Int m_height;
	Int m_originX;
	Int m_originY;
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

// ?setHeight@W3DView@@UAEXH@Z
void W3DView::setHeight(Int height)
{
	m_height = height;

	Vector2 vMin,vMax;
	m_3DCamera->Set_Aspect_Ratio((Real)getWidth()/(Real)height);
 	m_3DCamera->Get_Viewport(vMin,vMax);
 	vMax.Y=(Real)(m_originY+height)/(Real)TheDisplay->getHeight();
 	m_3DCamera->Set_Viewport(vMin,vMax);
}
