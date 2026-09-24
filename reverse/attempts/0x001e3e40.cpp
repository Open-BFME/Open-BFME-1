// ?computeBoundaryVector2D@Object@@QBE?AUCoord3D@@PBV1@@Z
// partial score=0.96 date=2026-09-04
// ?computeBoundaryVector2D@Object@@QBE?AUCoord3D@@PBV1@@Z
// partial score=0.96 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	Coord3D() {}
	Coord3D(float zValue, float yValue, float xValue) : x(xValue), y(yValue), z(zValue) {}

	float x;
	float y;
	float z;
};

extern volatile const float BfmeZeroRange;

class Object
{
public:
	Coord3D computeBoundaryVector2D(const Object *other) const;
	Coord3D bfmeGo941G(const Object *other) const;

private:
	char m_fields[0xbc];
	float m_boundingCircleRadius;
};

Coord3D Object::computeBoundaryVector2D(const Object *other) const
{
	Coord3D delta = bfmeGo941G(other);

	float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
	float combinedRadius = other->m_boundingCircleRadius + m_boundingCircleRadius;
	if (distance <= combinedRadius)
	{ return Coord3D(BfmeZeroRange, BfmeZeroRange, BfmeZeroRange); }

	_ReadWriteBarrier();
	volatile float scale = (distance - combinedRadius) / distance;
	return Coord3D(delta.z * scale, delta.y * scale, delta.x * scale);
}
