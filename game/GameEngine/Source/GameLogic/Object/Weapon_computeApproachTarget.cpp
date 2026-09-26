// cl: /DNDEBUG /MD /EHsc
// ?computeApproachTarget@Weapon@@QBE_NPBVObject@@0PBUCoord3D@@MAAU3@@Z
// Retail 0x001E43D0 (1042 bytes, ret 0x14). Zero Hour's Weapon::computeApproachTarget
// (inputs/reference/.../GameLogic/Object/Weapon.cpp) as BFME changed it:
//  - the direction comes from two Object helpers (0x001E3E40 on the target,
//    0x001E2560 on the source) where Zero Hour asked ThePartitionManager->getVectorTo;
//  - the too-close branch keeps dir.z and the sphere radii (no ATTACK_RANGE_IS_2D) and
//    refines the range up to ten times through the height-adjusted
//    Weapon::getAttackRange(source, heightDifference) at 0x001E2A70;
//  - the far branch has no contact-weapon early-out, scales the range by 0.9 and
//    shrinks it (again at most ten times) while the height-adjusted range at the
//    approach point stays short of it.
// Identity: ret 0x14 matches Zero Hour's five-argument signature, and the body
// keeps its structure (minimum-range retreat with the airborne 180-degree guard,
// the 0.001 FUDGE early-out returning true, the aircraft
// Pathfinder::adjustTargetDestination tail).

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl atan2(double, double);
#pragma intrinsic(sqrt, fabs, atan2)
extern "C" float __cdecl cosf(float);
extern "C" float __cdecl sinf(float);

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PI 3.14159265359f

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	// BFME's Coord3D copies field-wise (see Object_rva001E2560.cpp).
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}

	Real x, y, z;

	Real length( void ) const { return (Real)sqrt( x*x + y*y + z*z ); }
	void normalize( void );							///< retail 0x000FB930
	void zero( void ) { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
private:
	char m_unreconstructed_00[0x14];
	Real m_boundingSphereRadius;					///< Object+0xC0
};

class AIUpdateInterface
{
public:
	Bool isAircraftThatAdjustsDestination( void ) const;	///< retail 0x00271450
};

class Weapon;
class Object;

class Pathfinder
{
public:
	Bool adjustTargetDestination( const Object *obj, const Object *target,
		const Coord3D *targetPos, const Weapon *weapon, Coord3D *dest );	///< retail 0x003F2DB0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder( void ) { return m_pathfinder; }
private:
	char m_unreconstructed_00[0xc];
	Pathfinder *m_pathfinder;						///< TheAI+0x0C
};
extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	Real getHeightAboveTerrain() const;				///< retail 0x00131B00
	Bool isAboveTerrain() const { return getHeightAboveTerrain() > 0.0f; }
private:
	char m_unreconstructed_00[0x38];
	Coord3D m_cachedPos;							///< +0x38
	Real m_cachedAngle;								///< +0x44
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Coord3D rva001E3E40( const Object *other ) const;	///< retail 0x001E3E40
	Coord3D rva001E2560( const Coord3D *pos ) const;	///< retail 0x001E2560
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_unreconstructed_48[0xac - 0x48];
	GeometryInfo m_geometryInfo;					///< +0xAC
	char m_unreconstructed_c4[0x204 - 0xc4];
	AIUpdateInterface *m_ai;						///< +0x204
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	Real getMinimumAttackRange() const
	{
		// RATIONALIZE_ATTACK_RANGE: undersize by 1/4 of a pathfind cell
		const Real UNDERSIZE = 10.0f*0.25f;
		Real r = m_minimumAttackRange - UNDERSIZE;
		if (r < 0.0f) r = 0.0f;
		return r;
	}
private:
	char m_unreconstructed_00[0x18];
	Real m_minimumAttackRange;						///< +0x18
};

class Weapon
{
public:
	Bool computeApproachTarget(const Object *source, const Object *target, const Coord3D *pos, Real angleOffset, Coord3D& approachTargetPos) const;
	Real getAttackRange(const Object *source, Real heightDifference) const;	///< retail 0x001E2A70
private:
	char m_unreconstructed_00[4];					///< the vtable pointer
	const WeaponTemplate *m_template;				///< +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo, hi;
};

// upstream layout: inputs/reference/shims/sweep/GameLogic/TerrainLogic.h (getExtent at
// vtable +0x20 in BFME, as the matched clipToTerrainExtent reads it)
class TerrainLogic
{
public:
	virtual void unreconstructed_slot00( void );
	virtual void unreconstructed_slot04( void );
	virtual void unreconstructed_slot08( void );
	virtual void unreconstructed_slot0c( void );
	virtual void unreconstructed_slot10( void );
	virtual void unreconstructed_slot14( void );
	virtual void unreconstructed_slot18( void );
	virtual void unreconstructed_slot1c( void );
	virtual void getExtent( Region3D *extent ) const;
};
extern TerrainLogic *TheTerrainLogic;

#define PATHFIND_CELL_SIZE_F 10.0f

//-------------------------------------------------------------------------------------------------
// Retail 0x001E18B0, matched from Weapon.cpp beside the readable Zero Hour
// computeApproachTarget. Retail calls it with the argument in esi and no push:
// MSVC 7.1 gives a static function whose every call it sees a private register
// convention, so this caller needs its own static copy in the same TU for the
// call site to take that shape. The ledger row stays on Weapon.cpp.
static void clipToTerrainExtent(Coord3D& approachTargetPos)
{
	Region3D bounds;
	TheTerrainLogic->getExtent(&bounds);
	if (approachTargetPos.x < bounds.lo.x+PATHFIND_CELL_SIZE_F) {	 
		approachTargetPos.x = bounds.lo.x+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y < bounds.lo.y+PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.lo.y+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.x > bounds.hi.x-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.x = bounds.hi.x-PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y > bounds.hi.y-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.hi.y-PATHFIND_CELL_SIZE_F;
	}
}

//-------------------------------------------------------------------------------------------------
Bool Weapon::computeApproachTarget(const Object *source, const Object *target, const Coord3D *pos, Real angleOffset, Coord3D& approachTargetPos) const
{
	// compute unit direction vector from us to our victim
	const Coord3D *targetPos;
	Coord3D dir;
	if (target)
	{
		targetPos = target->getPosition();
		dir = target->rva001E3E40( source );
	}
	else if (pos)
	{
		targetPos = pos;
		dir = source->rva001E2560( pos );
		// Flip the vector to get from source to pos.
		dir.x = -dir.x;
		dir.y = -dir.y;
		dir.z = -dir.z;
	}
	else
	{
		approachTargetPos.zero();
		return false;
	}

	Real dist = dir.length();
	Real minAttackRange = m_template->getMinimumAttackRange();
	if (minAttackRange > 10.0f && dist < minAttackRange)
	{
		// We aret too close, so move away from the target.
		// Recompute dir, cause if the bounding spheres touch, it will be 0.
		// BFME recomputes into a fresh vector rather than reusing dir (as Zero
		// Hour does): with dir's address never taken, MSVC hoists the three loads
		// of each helper's by-value result above the stores, as retail does.
		Coord3D srcPos = *source->getPosition();
		Coord3D awayDir;
		awayDir.x = srcPos.x-targetPos->x;
		awayDir.y = srcPos.y-targetPos->y;
		awayDir.z = srcPos.z-targetPos->z;
		awayDir.normalize();

		// if we're airborne and too close, just head for the opposite side.
		if (source->isAboveTerrain())
		{
			// Don't do a 180 degree turn.
			Real angle = atan2(-awayDir.y, -awayDir.x);
			Real relAngle = source->getOrientation()- angle;
			if (relAngle>2*PI) relAngle -= 2*PI;
			if (relAngle<-2*PI) relAngle += 2*PI;
			if ((Real)fabs(relAngle)<PI/2) {
				awayDir.x = -awayDir.x;
				awayDir.y = -awayDir.y;
				awayDir.z = -awayDir.z;
			}
		}

		if (angleOffset != 0.0f)
		{
			Real angle = atan2(awayDir.y, awayDir.x);
			angleOffset += angle;
			awayDir.x = cosf(angleOffset);
			awayDir.y = sinf(angleOffset);
		}

		// select a spot along the line between us, halfway between the min & max range.
		Real attackRange = (getAttackRange(source, targetPos->z - source->getPosition()->z) + minAttackRange)/2.0f;
		for (Int i = 0; i < 10; ++i)
		{
			if (target)
				attackRange += target->getGeometryInfo().getBoundingSphereRadius();
			attackRange += source->getGeometryInfo().getBoundingSphereRadius();
			Real range = getAttackRange(source, -(attackRange * awayDir.z));
			if (attackRange > range)
				attackRange = range;
			else
				break;
		}
		approachTargetPos.x = attackRange * awayDir.x + targetPos->x;
		approachTargetPos.y = attackRange * awayDir.y + targetPos->y;
		approachTargetPos.z = attackRange * awayDir.z + targetPos->z;
		///@todo - make sure we can get to the approach position.
		clipToTerrainExtent(approachTargetPos);
		return false;
	}

	const Real FUDGE = 0.001f;
	if (dist < FUDGE)
	{
		// we're close enough!
		approachTargetPos = *source->getPosition();
		return true;
	}

	dir.x /= dist;
	dir.y /= dist;
	dir.z /= dist;

	if (angleOffset != 0.0f)
	{
		Real angle = atan2(dir.y, dir.x);
		angleOffset += angle;
		dir.x = cosf(angleOffset);
		dir.y = sinf(angleOffset);
	}

	// select a spot along the line between us, in range of our weapon
	const Real ATTACK_RANGE_APPROACH_FUDGE = 0.9f;
	Real attackRange = getAttackRange(source, targetPos->z - source->getPosition()->z) * ATTACK_RANGE_APPROACH_FUDGE;
	if (dir.z != 0.0f)
	{
		Bool done = false;
		for (Int i = 0; !done && i < 10; ++i)
		{
			Real range = getAttackRange(source, -(attackRange * dir.z));
			if (range < attackRange)
			{
				attackRange = range * ATTACK_RANGE_APPROACH_FUDGE;
				done = false;
			}
			else
			{
				done = true;
			}
		}
	}
	approachTargetPos.x = attackRange * dir.x + targetPos->x;
	approachTargetPos.y = attackRange * dir.y + targetPos->y;
	approachTargetPos.z = attackRange * dir.z + targetPos->z;

	if (source->getAI() && source->getAI()->isAircraftThatAdjustsDestination()) {
		// Adjust the target so that we are not stacked atop another aircraft.
		TheAI->pathfinder()->adjustTargetDestination(source, target, pos, this, &approachTargetPos);
	}

	return false;
}
