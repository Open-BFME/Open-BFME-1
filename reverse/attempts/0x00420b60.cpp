// ?calcPhysicsXformThrust@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// partial score=0.988 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc
// stlport
//
// Drawable::calcPhysicsXformThrust, retail 0x00420B60, 1743 bytes (ret 8 at
// +0x6CC, int3 padding after). Identity: the matched calcPhysicsXform
// dispatcher (0x004213F0) sends appearance 4 (LOCO_THRUST in the ZH enum,
// jump-table slot 3) through ILT 0x00027651 to this body.
//
// BFME replaced Zero Hour's scud wobble with a terrain-following body: the
// four footprint corners come from a draw-module interface (slot 41, +0xA4)
// or, failing that, from GeometryInfo::get2DBounds (ledger Rva0087E370::method)
// rotated by the cached angle; four getLayerHeight samples give a pitch spring
// (atan2 of rear-front height over the midpoint distance) and an overlap-Z
// spring. Offsets: Drawable+0x44 cached angle, +0xFC object, +0x138 locoInfo,
// +0x150 draw modules; LocomotorTemplate fields from name_oracle.
//
// STATE: 1743/1743, 21 non-relocation bytes, all of them two scheduling
// spots where retail loads the corner-vector begin one x87 op later (corner
// 0 x at +0x25E, corner 3 y at +0x2A8). Registers and frame agree with
// retail. What got them there, each measured:
//   * ZH-shaped inline Overridable::getFinalOverride (zero -> esi);
//   * the front/rear midpoints as two Coord2D locals (frame 0x50 -> 0x4C,
//     rear.y spills into the dead get2DBounds center as retail does; with
//     that the this/locomotor/cursor registers flip to retail's too);
//   * the geometry reference taken into a local before the get2DBounds call
//     (retail loads the object before the argument addresses);
//   * heights summed low index first.
// Operand-order respellings of the corner products do not move the two
// scheduling spots.

#include <vector>

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl sqrt(double);

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &);
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

namespace _STL
{
template <>
class vector<Coord3D, allocator<Coord3D> > : public _Vector_base<Coord3D, allocator<Coord3D> >
{
public:
	vector() : _Vector_base<Coord3D, allocator<Coord3D> >(allocator<Coord3D>()) {}

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	Coord3D &operator[](unsigned int index)
	{
		return _M_start[index];
	}

	void resize(unsigned int newSize, Coord3D value = Coord3D());
};
}

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

class TerrainLogic
{
public:
	virtual void _pad00( void );
	virtual void _pad04( void );
	virtual void _pad08( void );
	virtual void _pad0C( void );
	virtual void _pad10( void );
	virtual void _pad14( void );
	virtual void _pad18( void );
	// +0x1C
	virtual Real getLayerHeight( Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal = 0, Bool clip = true ) const;
};

extern TerrainLogic *TheTerrainLogic;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0x84 - 0x08];
	Real m_accelPitchLimit;			// +0x84
	Real m_decelPitchLimit;			// +0x88
	Real m_pitchStiffness;			// +0x8c
	Real m_rollStiffness;			// +0x90
	Real m_pitchDamping;			// +0x94
	Real m_rollDamping;				// +0x98
	unsigned char m_unreconstructed_09C[0xb4 - 0x9c];
	Real m_uniformAxialDamping;		// +0xb4
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const T *m_overridable;
};

class Locomotor
{
public:
	Real getAccelPitchLimit() const { return m_template->m_accelPitchLimit; }
	Real getPitchStiffness() const { return m_template->m_pitchStiffness; }
	Real getRollStiffness() const { return m_template->m_rollStiffness; }
	Real getPitchDamping() const { return m_template->m_pitchDamping; }
	Real getRollDamping() const { return m_template->m_rollDamping; }
	Real getUniformAxialDamping() const { return m_template->m_uniformAxialDamping; }

	void *m_vtbl;
	OVERRIDE<LocomotorTemplate> m_template;		// +0x04
};

class DrawableLocoInfo
{
public:
	DrawableLocoInfo() throw();
	virtual ~DrawableLocoInfo();

	Real m_pitch;						// +0x04
	Real m_pitchRate;					// +0x08
	Real m_roll;						// +0x0c
	Real m_rollRate;					// +0x10
	Real m_yaw;							// +0x14
	Real m_accelerationPitch;			// +0x18
	Real m_accelerationPitchRate;		// +0x1c
	Real m_accelerationRoll;			// +0x20
	Real m_accelerationRollRate;		// +0x24
	Real m_overlapZVel;					// +0x28
	Real m_overlapZ;					// +0x2c
	unsigned char m_unreconstructed_030[0x58 - 0x30];
};

class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40();
	// slot 41, +0xa4: fills a point list; identity not recovered
	virtual Bool rva00420B60Slot41(VecCoord3D &points, Bool flag);
};

class DrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38();
	virtual ObjectDrawInterface *getObjectDrawInterface();	// slot 39, +0x9c
};

// ?method@Rva0087E370@@QBEXABUCoord3D@@MAAURegion2D@@@Z
class Rva0087E370
{
public:
	void method(const Coord3D &geomCenter, Real angle, Region2D &bounds) const;
};

// ?bfmeScale@Gen_001BEC20@@QBEHXZ
class Gen_001BEC20
{
public:
	int bfmeScale(void) const;
};

class PhysicsBehavior;

class Object
{
public:
	const Rva0087E370 &getGeometryInfo() const { return *(const Rva0087E370 *)&m_geometryInfo; }
	PhysicsBehavior *getPhysics() const { return m_physics; }
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((const Gen_001BEC20 *)this)->bfmeScale(); }

	unsigned char m_unreconstructed_000[0xac];
	unsigned char m_geometryInfo[0x204 - 0xac];	// +0xac
	void *m_ai;									// +0x204
	PhysicsBehavior *m_physics;					// +0x208
};

// ?get@BFMERopeDrawableGetPositionShim@@QBEPBUCoord3D@@XZ
class BFMERopeDrawableGetPositionShim
{
public:
	const Coord3D *get() const;
};

class Drawable
{
public:
	struct PhysicsXformInfo
	{
		Real m_totalPitch;
		Real m_totalRoll;
		Real m_totalYaw;
		Real m_totalZ;
	};

	Object *getObject() const { return m_object; }
	const Coord3D *getPosition() const { return ((const BFMERopeDrawableGetPositionShim *)this)->get(); }
	Real getOrientation() const { return m_cachedAngle; }
	DrawModule **getDrawModules() const { return m_drawModules; }

protected:
	void calcPhysicsXformThrust( const Locomotor *locomotor, PhysicsXformInfo &info );

private:
	unsigned char m_unreconstructed_000[0x44];
	Real m_cachedAngle;							// +0x44
	unsigned char m_unreconstructed_048[0xfc - 0x48];
	Object *m_object;							// +0xfc
	unsigned char m_unreconstructed_100[0x138 - 0x100];
	DrawableLocoInfo *m_locoInfo;				// +0x138
	unsigned char m_unreconstructed_13C[0x150 - 0x13c];
	DrawModule **m_drawModules;					// +0x150
};

// ?calcPhysicsXformThrust@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
void Drawable::calcPhysicsXformThrust( const Locomotor *locomotor, PhysicsXformInfo &info )
{
	if (m_locoInfo == NULL)
		m_locoInfo = new DrawableLocoInfo;

	const Real ACCEL_PITCH_LIMIT = locomotor->getAccelPitchLimit();
	const Real PITCH_STIFFNESS = locomotor->getPitchStiffness();
	const Real ROLL_STIFFNESS = locomotor->getRollStiffness();
	const Real PITCH_DAMPING = locomotor->getPitchDamping();
	const Real ROLL_DAMPING = locomotor->getRollDamping();
	const Real UNIFORM_AXIAL_DAMPING = locomotor->getUniformAxialDamping();

	Object *obj = getObject();
	if (obj == NULL || obj->getPhysics() == NULL)
		return;

	const Coord3D *pos = getPosition();
	Real angle = getOrientation();

	VecCoord3D corners;
	Bool found = false;
	for (DrawModule **dm = getDrawModules(); !found && *dm; ++dm)
	{
		ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
		if (di && di->rva00420B60Slot41(corners, false))
		{
			if (corners.size() >= 4)
				found = true;
		}
	}

	if (!found)
	{
		Region2D bounds;
		Coord3D center;
		center.x = 0.0f;
		center.y = 0.0f;
		center.z = 0.0f;
		const Rva0087E370 &geom = obj->getGeometryInfo();
		geom.method(center, 0.0f, bounds);
		corners.resize(4);

		Real s = sinf(angle);
		Real c = cosf(angle);

		corners[1].x = bounds.hi.x * c - bounds.hi.y * s;
		corners[1].y = bounds.hi.y * c + bounds.hi.x * s;
		corners[1].z = pos->z;
		corners[0].x = bounds.lo.x * c - bounds.hi.y * s;
		corners[0].y = bounds.hi.y * c + bounds.lo.x * s;
		corners[0].z = pos->z;
		corners[3].x = bounds.hi.x * c - bounds.lo.y * s;
		corners[3].y = bounds.lo.y * c + bounds.hi.x * s;
		corners[3].z = pos->z;
		corners[2].x = bounds.lo.x * c - bounds.lo.y * s;
		corners[2].y = bounds.lo.y * c + bounds.lo.x * s;
		corners[2].z = pos->z;
	}

	Real frontHeight;
	Real rearHeight;
	{
		Real heights[4];
		for (Int i = 0; i < 4; ++i)
		{
			if (i != 0 && corners[i].x == corners[i - 1].x && corners[i].y == corners[i - 1].y)
				heights[i] = heights[i - 1];
			else
				heights[i] = TheTerrainLogic->getLayerHeight(corners[i].x, corners[i].y, obj->getLayer());
		}

		frontHeight = (heights[0] + heights[1]) * 0.5f;
		rearHeight = (heights[2] + heights[3]) * 0.5f;
	}
	Coord2D front;
	Coord2D rear;
	front.x = (corners[1].x + corners[0].x) * 0.5f;
	front.y = (corners[1].y + corners[0].y) * 0.5f;
	rear.x = (corners[3].x + corners[2].x) * 0.5f;
	rear.y = (corners[3].y + corners[2].y) * 0.5f;
	Real dx = front.x - rear.x;
	Real dy = front.y - rear.y;
	Real dist = sqrt(dy * dy + dx * dx);
	Real pitch = atan2(rearHeight - frontHeight, dist);

	m_locoInfo->m_pitchRate += ((-PITCH_STIFFNESS * (m_locoInfo->m_pitch - pitch)) + (-PITCH_DAMPING * m_locoInfo->m_pitchRate));
	if (m_locoInfo->m_pitchRate > 0.0f)
		m_locoInfo->m_pitchRate *= 0.5f;

	m_locoInfo->m_pitch += UNIFORM_AXIAL_DAMPING * m_locoInfo->m_pitchRate;
	m_locoInfo->m_roll += UNIFORM_AXIAL_DAMPING * m_locoInfo->m_rollRate;

	m_locoInfo->m_accelerationPitchRate += ((-PITCH_STIFFNESS * m_locoInfo->m_accelerationPitch) + (-PITCH_DAMPING * m_locoInfo->m_accelerationPitchRate));
	m_locoInfo->m_accelerationPitch += m_locoInfo->m_accelerationPitchRate;

	m_locoInfo->m_accelerationRollRate += ((-ROLL_STIFFNESS * m_locoInfo->m_accelerationRoll) + (-ROLL_DAMPING * m_locoInfo->m_accelerationRollRate));
	m_locoInfo->m_accelerationRoll += m_locoInfo->m_accelerationRollRate;

	info.m_totalPitch = m_locoInfo->m_accelerationPitch + m_locoInfo->m_pitch;
	info.m_totalRoll = m_locoInfo->m_accelerationRoll + m_locoInfo->m_roll;

	if (m_locoInfo->m_accelerationPitch > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationPitch < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationPitch = -ACCEL_PITCH_LIMIT;

	if (m_locoInfo->m_accelerationRoll > ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = ACCEL_PITCH_LIMIT;
	else if (m_locoInfo->m_accelerationRoll < -ACCEL_PITCH_LIMIT)
		m_locoInfo->m_accelerationRoll = -ACCEL_PITCH_LIMIT;

	Real oldZ = m_locoInfo->m_overlapZ;
	Real targetZ = (rearHeight + frontHeight) * 0.5f - pos->z;
	m_locoInfo->m_overlapZ += m_locoInfo->m_overlapZVel;
	if ((oldZ <= targetZ && targetZ <= m_locoInfo->m_overlapZ) ||
		(oldZ >= targetZ && targetZ >= m_locoInfo->m_overlapZ))
	{
		m_locoInfo->m_overlapZ = targetZ;
		m_locoInfo->m_overlapZVel = 0.0f;
	}
	else if ((m_locoInfo->m_overlapZ < targetZ && m_locoInfo->m_overlapZVel < 0.0f) ||
		(m_locoInfo->m_overlapZ > targetZ && m_locoInfo->m_overlapZVel > 0.0f))
	{
		m_locoInfo->m_overlapZ -= m_locoInfo->m_overlapZVel;
		m_locoInfo->m_overlapZVel = 0.0f;
	}
	else if (m_locoInfo->m_overlapZ < targetZ)
		m_locoInfo->m_overlapZVel += 1.5f;
	else
		m_locoInfo->m_overlapZVel -= 0.5f;

	info.m_totalZ = m_locoInfo->m_overlapZ;
}
