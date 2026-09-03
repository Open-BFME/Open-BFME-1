// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x002D07B0, 171 bytes: QueueProductionExitUpdate::getExitPosition.
// ExitInterface this (module+0x20): object at [this-0x18], moduleData at
// [this-0x1C]. unitCreatePoint at md+8. Extra out-float is md+0x2C plus
// object+0x44. ExitInterface vtable slot immediately after
// getNaturalRallyPoint (0x002D08D0). ret 8.

#include "vector3.h"
#include "matrix3d.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Matrix3D *getTransformMatrix() const
	{
		return reinterpret_cast<const Matrix3D *>(
			reinterpret_cast<const unsigned char *>(this) + 8);
	}

	float heightAt44() const
	{
		return *reinterpret_cast<const float *>(
			reinterpret_cast<const unsigned char *>(this) + 0x44);
	}
};

class QueueProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Coord3D m_unitCreatePoint;
	unsigned char m_pad2[0x2C - 0x14];
	float m_extraZ;
};

class QueueProductionExitUpdate
{
public:
	virtual bool getExitPosition(Coord3D &exitPosition, float &outZ) const;
};

bool QueueProductionExitUpdate::getExitPosition(Coord3D &exitPosition, float &outZ) const
{
	const Object *obj = *reinterpret_cast<Object *const *>(
		reinterpret_cast<const char *>(this) - 0x18);
	if (!obj)
		return false;

	const QueueProductionExitUpdateModuleData *md =
		*reinterpret_cast<const QueueProductionExitUpdateModuleData *const *>(
			reinterpret_cast<const char *>(this) - 0x1C);

	const Matrix3D *transform = obj->getTransformMatrix();

	Vector3 loc;
	loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
	transform->Transform_Vector(*transform, loc, &loc);

	exitPosition.x = loc.X;
	exitPosition.y = loc.Y;
	exitPosition.z = loc.Z;

	const Object *objAgain = *reinterpret_cast<Object *const *>(
		reinterpret_cast<const char *>(this) - 0x18);
	outZ = md->m_extraZ + objAgain->heightAt44();
	return true;
}
