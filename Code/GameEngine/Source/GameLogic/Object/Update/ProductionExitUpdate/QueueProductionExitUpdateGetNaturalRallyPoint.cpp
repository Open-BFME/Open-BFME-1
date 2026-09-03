// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Retail 0x002D08D0, 342 bytes: QueueProductionExitUpdate::getNaturalRallyPoint.
// Instruction-stream twin of Default 0x002D0030. ExitInterface this
// (module+0x20): moduleData at [this-0x1C], object at [this-0x18].

#include "vector3.h"
#include "matrix3d.h"

#define PATHFIND_CELL_SIZE_F 10.0f

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

class QueueProductionExitUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Coord3D m_unitCreatePoint;
	Coord3D m_naturalRallyPoint;
};

class QueueProductionExitUpdate
{
public:
	virtual bool getNaturalRallyPoint(Coord3D &rallyPoint, bool offset) const;
};

bool QueueProductionExitUpdate::getNaturalRallyPoint(Coord3D &rallyPoint, bool offset) const
{
	const QueueProductionExitUpdateModuleData *data =
		*reinterpret_cast<const QueueProductionExitUpdateModuleData *const *>(
			reinterpret_cast<const char *>(this) - 0x1C);

	Vector3 p;
	p.X = data->m_naturalRallyPoint.x;
	p.Y = data->m_naturalRallyPoint.y;
	p.Z = data->m_naturalRallyPoint.z;

	if (offset)
	{
		Vector3 extra = p;
		extra.Normalize();
		extra *= (2 * PATHFIND_CELL_SIZE_F);
		p += extra;
	}

	const Object *obj = *reinterpret_cast<Object *const *>(
		reinterpret_cast<const char *>(this) - 0x18);
	const Matrix3D *transform = obj->getTransformMatrix();
	transform->Transform_Vector(*transform, p, &p);

	rallyPoint.x = p.X;
	rallyPoint.y = p.Y;
	rallyPoint.z = p.Z;
	return true;
}
