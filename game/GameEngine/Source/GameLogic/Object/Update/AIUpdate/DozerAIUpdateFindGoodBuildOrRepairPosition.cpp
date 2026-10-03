// cl: /Igame/GameEngine/Include/Precompiled /I. /Igame/GameEngine/Source/Common/System /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug
// DozerAIUpdate::findGoodBuildOrRepairPosition, RVA 0x002B6C40 (445 bytes).
// BFME uses an incoming receiver; the old static lift was an ABI error.
// Evidence: identity_evidence/002b6c40-dozer-member-and-native-vector.md

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
};

#include "vector3.h"

class Object;
class AIUpdateInterface
{
public:
	bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *result,
		const Coord3D *workingPosition, bool skipCollideTest);
};

struct Region2D;
#include "game/GameEngine/Source/Common/System/geometry.h"
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)&m_geometryInfo; } bool isUsingAirborneLocomotor() const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"
#undef THING_TU_MEMBERS
#undef OBJECT_TU_MEMBERS

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

class DozerAIUpdate : public AIUpdateInterface
{
public:
	bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
};


// ?findGoodBuildOrRepairPosition@DozerAIUpdate@@QAE_NPBVObject@@0AAUCoord3D@@@Z
bool DozerAIUpdate::findGoodBuildOrRepairPosition(const Object *me,
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
	fpOptions.sourceToPathToDest = me;
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
