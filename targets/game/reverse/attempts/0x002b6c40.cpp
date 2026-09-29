// ?findGoodBuildOrRepairPosition@DozerAIUpdate@@SA_NPBVObject@@0AAUCoord3D@@@Z
// partial score=0.9573 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// DozerAIUpdate::findGoodBuildOrRepairPosition, retail RVA 0x002B6C40 (445
// bytes); real C++ body replacing the naked __emit lift that stood there.
//
// IDENTITY: the only callers are the two call sites inside
// DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget (retail 0x002B8890,
// already byte-matched by the sibling TU), which reach this body through that
// function's incremental-link thunk. Retail parks the incoming ECX in EBP and
// hands it straight to AIUpdateInterface::findNearestLabeledContactPointOnTarget
// (0x00272800, __thiscall) with no vtable load and no this-pointer adjustment,
// so the helper is a __thiscall member of the DozerAIUpdate slice whose
// AIUpdateInterface base sits at offset 0 -- not the Zero Hour public static
// helper the lift spelled. The /alternatename below binds the retail static
// name to the member, the same trade the AndTarget body makes.
//
// The Zero Hour twin ends in ThePartitionManager->findPositionAround; BFME1
// drops that global load (0x001AF610 reloads TheTerrainLogic itself, so ECX is
// dead there), probes a labeled contact point on the target first, and takes
// the findPositionAround RESULT as the verdict where the twin discards it.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
};

class WWMath { public: static float __fastcall Inv_Sqrt(float a); };

struct Vector3
{
	float X, Y, Z;
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline void Normalize()
	{
		float len2 = X * X + Y * Y + Z * Z;
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
};
__forceinline Vector3 operator*(const Vector3 &v, float s) { return Vector3(v.X * s, v.Y * s, v.Z * s); }

class Object;
class AIUpdateInterface
{
public:
	bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *result,
		const Coord3D *workingPosition, bool skipCollideTest);
};

class GeometryInfo { public: float majorRadius; float getMajorRadius() const { return majorRadius; } };

class Object
{
public:
	void *m_vtable;
	unsigned char m_unmodelled08[0x34];
	Coord3D m_position;
	unsigned char m_unmodelled44[0x78];
	GeometryInfo m_geometry;
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometry; }
	bool isUsingAirborneLocomotor() const;
};

// retail 0x001AF610: free __cdecl, three stack arguments cleaned by the call
// site, verdict in al. No receiver: it reloads TheTerrainLogic itself.
struct FindPositionOptions;
bool findPositionAround(const Coord3D *workingPosition, const FindPositionOptions *options, Coord3D *result);

struct FindPositionOptions
{
	unsigned flags;
	Real minRadius, maxRadius, startAngle, maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
	FindPositionOptions() : flags(0), minRadius(0.0f), maxRadius(0.0f), startAngle(-99999.9f),
		maxZDelta(1e10f), ignoreObject(0), sourceToPathToDest(0), relationshipObject(0) {}
};

class Rva002B8890DozerAIUpdate : public AIUpdateInterface
{
public:
	bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
};

#pragma comment(linker, "/alternatename:?findGoodBuildOrRepairPosition@Rva002B8890DozerAIUpdate@@QAE_NPBVObject@@0AAUCoord3D@@@Z=?findGoodBuildOrRepairPosition@DozerAIUpdate@@SA_NPBVObject@@0AAUCoord3D@@@Z")

// ?findGoodBuildOrRepairPosition@DozerAIUpdate@@SA_NPBVObject@@0AAUCoord3D@@@Z
bool Rva002B8890DozerAIUpdate::findGoodBuildOrRepairPosition(const Object *me,
	const Object *target, Coord3D &positionOut)
{
	// The place we go to build or repair is the closest spot from us to them
	Coord3D ourPosition = *me->getPosition();
	Coord3D theirPosition = *target->getPosition();

	Coord3D bestPosition = theirPosition;	// This answer is the best, as it includes findPositionAround
	Coord3D workingPosition = theirPosition;	// But if findPositionAround fails, we need to say something.

	Vector3 offset(ourPosition.x - theirPosition.x,
		ourPosition.y - theirPosition.y,
		ourPosition.z - theirPosition.z);
	offset.Normalize();
	// This scaler makes FindPositionAround bias towards our side
	offset = offset * (target->getGeometryInfo().getMajorRadius() / 2);

	workingPosition.x += offset.X;
	workingPosition.y += offset.Y;
	workingPosition.z += offset.Z;

	// this is a little cheesy... the idea is that we can only choose a location that is pretty close
	// in z to the desired one. this prevents us from choosing a space at the bottom of a cliff when
	// the space we want is at the top of the cliff. ideally we should do a funky terrain-zone compare
	// but that isn't well-exposed... (srj)
	const Real MAX_Z_DELTA = 10.0f;

	FindPositionOptions fpOptions;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 100.0f;
	fpOptions.sourceToPathToDest = me;	// This makes it find a place for Whom can get to.
	if (!me->isUsingAirborneLocomotor())
		fpOptions.maxZDelta = MAX_Z_DELTA;
	if (me->isUsingAirborneLocomotor())
		fpOptions.ignoreObject = target;	// Flyers can ignore stuff, so they can approach right over the target if they want.

	Bool spotFound = findNearestLabeledContactPointOnTarget((Object *)target, &bestPosition, &workingPosition, false);
	if (!spotFound)
		spotFound = findPositionAround(&workingPosition, &fpOptions, &bestPosition);

	positionOut = spotFound ? bestPosition : workingPosition;

	return spotFound;
}
