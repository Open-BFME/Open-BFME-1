// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x002CFF10, 150 bytes: DefaultProductionExitUpdate::getExitPosition.
// Primary vtable 0x010CB614 slot 11. getObject at [this+8], moduleData at
// [this+4], unitCreatePoint at md+8. Object transform at +8. SupplyCenter
// twin at 0x002D24C0 is byte-identical.

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
};

class DefaultProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Coord3D m_unitCreatePoint;
};

class DefaultProductionExitUpdate
{
public:
	virtual bool getExitPosition(Coord3D &exitPosition) const;

private:
	const DefaultProductionExitUpdateModuleData *m_moduleData;
	Object *m_object;
};

bool DefaultProductionExitUpdate::getExitPosition(Coord3D &exitPosition) const
{
	const Object *obj = m_object;
	if (!obj)
		return false;

	const Matrix3D *transform = obj->getTransformMatrix();
	const DefaultProductionExitUpdateModuleData *md = m_moduleData;

	Vector3 loc;
	loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
	transform->Transform_Vector(*transform, loc, &loc);

	exitPosition.x = loc.X;
	exitPosition.y = loc.Y;
	exitPosition.z = loc.Z;
	return true;
}
