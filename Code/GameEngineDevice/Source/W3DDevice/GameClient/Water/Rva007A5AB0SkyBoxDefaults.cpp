// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stringbaseascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Anonymous 192-byte body at 0x007A5AB0: puts the sky box back to its
// defaults (position 0,0,0, scale 1, rotation 0, texture "DefaultSky").  No
// named caller, vtable slot or Zero Hour twin names it, so the address token
// stays.  The owner, the +0x250 sky box pointer, slot +0x58 and the three
// setters are the ones parseSkyBoxSettings007A5BA0 (the next body, 0x007A5BA0)
// drives in WaterRenderObjReadSkyBoxSettings.cpp.

#include "ascii_string.h"

struct Vector3
{
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

#define SKYBOX_SLOT(n) virtual void slot##n();

class SkyBoxRenderObject
{
public:
	SKYBOX_SLOT(0) SKYBOX_SLOT(1) SKYBOX_SLOT(2) SKYBOX_SLOT(3)
	SKYBOX_SLOT(4) SKYBOX_SLOT(5) SKYBOX_SLOT(6) SKYBOX_SLOT(7)
	SKYBOX_SLOT(8) SKYBOX_SLOT(9) SKYBOX_SLOT(10) SKYBOX_SLOT(11)
	SKYBOX_SLOT(12) SKYBOX_SLOT(13) SKYBOX_SLOT(14) SKYBOX_SLOT(15)
	SKYBOX_SLOT(16) SKYBOX_SLOT(17) SKYBOX_SLOT(18) SKYBOX_SLOT(19)
	SKYBOX_SLOT(20) SKYBOX_SLOT(21)
	virtual void setPosition(const Vector3 &position);
};

#undef SKYBOX_SLOT

class WaterSkyBoxSettingsOwner
{
public:
	void setSkyBoxScale(const float *scale);
	void setSkyBoxRotation007A15A0(const float *rotation);
	void setSkyBoxTexture007A58C0(const AsciiString *texture);

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *m_skyBox;
};

extern WaterSkyBoxSettingsOwner *TheWaterRenderObj;

// Each local sits in its own block: VC7.1 then lets scale and rotation share
// one frame slot, which is the 0x14-byte frame retail allocates.
void dup_007A5AB0()
{
	if (TheWaterRenderObj->m_skyBox != 0) {
		TheWaterRenderObj->m_skyBox->setPosition(Vector3(0.0f, 0.0f, 0.0f));
	}
	{
		float scale = 1.0f;
		TheWaterRenderObj->setSkyBoxScale(&scale);
	}
	{
		float rotation = 0.0f;
		TheWaterRenderObj->setSkyBoxRotation007A15A0(&rotation);
	}
	{
		AsciiString texture("DefaultSky");
		TheWaterRenderObj->setSkyBoxTexture007A58C0(&texture);
	}
}
