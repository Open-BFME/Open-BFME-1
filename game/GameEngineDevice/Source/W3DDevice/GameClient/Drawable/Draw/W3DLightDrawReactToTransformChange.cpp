// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// W3DLightDraw::reactToTransformChange, retail RVA 0x00758AC0.

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "matrix3d.h"

struct BfmeAsciiStringData
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};

class AsciiString
{
public:
	BfmeAsciiStringData *data;

	__forceinline bool isEmpty() const
	{
		return data == 0 || data->length == 0;
	}

	__forceinline const char *str() const
	{
		return data ? data->text : (const char *)0x0107388B;
	}
};

class W3DLightDrawModuleData
{
private:
	char padding[0x44];

public:
	AsciiString boneName;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	bool getCurrentWorldspaceClientBonePositions(const char *boneName,
		Matrix3D &transform) const;
};

class W3DDynamicLight
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
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void Set_Transform(const Matrix3D &transform);
};

class W3DLightDraw
{
public:
	virtual void reactToTransformChange(const Matrix3D *oldMtx,
		const Coord3D *oldPos, float oldAngle);

	W3DLightDrawModuleData *m_moduleData;
	Drawable *m_drawable;
	W3DDynamicLight *m_light;
};

#pragma comment(linker, "/alternatename:?getCurrentWorldspaceClientBonePositions@Drawable@@QBE_NPBDAAVMatrix3D@@@Z=?j_0003ec11@@YAXXZ")

void W3DLightDraw::reactToTransformChange(const Matrix3D *, const Coord3D *, float)
{
	if (m_light)
	{
		Matrix3D transform = *m_drawable->getTransformMatrix();
		if (!m_moduleData->boneName.isEmpty())
		{
			Matrix3D boneTransform;
			const char *boneName = m_moduleData->boneName.str();
			Drawable *draw = m_drawable;
			if (draw->getCurrentWorldspaceClientBonePositions(boneName, boneTransform))
				transform = boneTransform;
		}
		m_light->Set_Transform(transform);
	}
}
