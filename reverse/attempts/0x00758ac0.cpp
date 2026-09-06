// ?reactToTransformChange@W3DLightDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /G6 /EHsc /I../../../../../../Libraries/Source/WWVegas/WWMath /I../../../../../../Libraries/Source/WWVegas/WWLib /I../../../../../../Libraries/Source/WWVegas
// BFME W3DLightDraw transform notification.  The light follows the named
// client bone when one is configured, otherwise this callback is inert.

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

	W3DLightDrawModuleData *moduleData;
	Drawable *drawable;
	W3DDynamicLight *light;
};

#pragma comment(linker, "/alternatename:?getCurrentWorldspaceClientBonePositions@Drawable@@QBE_NPBDAAVMatrix3D@@@Z=?j_0003ec11@@YAXXZ")

// ?reactToTransformChange@W3DLightDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z
void W3DLightDraw::reactToTransformChange(const Matrix3D *, const Coord3D *, float)
{
	if (light)
	{
		Matrix3D transform = *drawable->getTransformMatrix();
		if (!moduleData->boneName.isEmpty())
		{
			Matrix3D boneTransform;
			if (drawable->getCurrentWorldspaceClientBonePositions(
				moduleData->boneName.str(), boneTransform))
			{
				transform = Matrix3D(boneTransform);
				light->Set_Transform(transform);
			}
		}
	}
}
