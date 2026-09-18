// ?behavior@Rva001BA1C0Handler@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.15 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// BFME body at 0x001BA1C0.  The matched movement dispatcher at 0x001BC820
// passes Object* and const Coord3D* through ILT 0x0000FEBB; the raw callee
// returns Bool with ret 8.  The handler reads the LocomotorTemplate behavior-Z
// field at +0x6c and updates the BFME Object position at +0x178.

typedef bool Bool;
typedef float Real;

class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva002E8370Entry
{
	Object *object;
	unsigned unknown04;
};

struct Rva002E8370ResultData
{
	Rva002E8370Entry *begin;
	Rva002E8370Entry *end;
	Rva002E8370Entry *capacity;
	Rva002E8370Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva002E8370ResultData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &other);
	~BfmeWideResult();

	Object *next(Object *&object)
	{
		if (value->current == value->end)
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

#pragma comment(linker, "/alternatename:??1BfmeWideResult@@QAE@XZ=?j_0002c471@@YAXXZ")

#define ThePartitionManager (*(BfmeWideForwardC **)0x012ED5B8)

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class Rva001B95B0Owner
{
public:
	Real rva001b95b0(Object *object, const Coord3D *goalPos,
		Real surfaceHeight);
};

#pragma comment(linker, "/alternatename:?rva001b95b0@Rva001B95B0Owner@@QAEMPAVObject@@PBUCoord3D@@M@Z=?j_0001712f@@YAXXZ")

struct Rva01083B5CFilter
{
	void *vtable;
	Rva01083B5CFilter *next;
};

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x64];
	int m_behaviorZ;
};

// The first retail call returns the saved transform translation by hidden
// pointer.  These are the already matched views for that concrete contract.
class BfmeVec3CN
{
public:
	BfmeVec3CN(void)
	{
	}

	BfmeVec3CN(const BfmeVec3CN &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
	}

	Real m_bfmeX;
	Real m_bfmeY;
	Real m_bfmeZ;
};

class Gen_001B4A20
{
public:
	BfmeVec3CN bfmeGetScale(void) const;

private:
	int m_bfmeHead[28];
	Real m_bfmeScaleX;
	int m_bfmeGapA[3];
	Real m_bfmeScaleY;
	int m_bfmeGapB[3];
	Real m_bfmeScaleZ;
};

class Rva001B49E0Owner
{
public:
	void setPosition(const Coord3D *position);

private:
	char m_bfmePad000[0x70];
	Real m_bfmeRow0;
	char m_bfmePad074[0x0c];
	Real m_bfmeRow1;
	char m_bfmePad084[0x0c];
	Real m_bfmeRow2;
};

class BFMESelectionStatusBits
{
public:
	Bool test(unsigned mask) const;
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
	virtual Real getLayerHeight(Real x, Real y, int layer,
		Coord3D *normal, Bool clip) const = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ,
		Real *terrainZ) = 0;
};

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define BfmeZeroRange (*(const Real *)0x01075350)

class Object
{
public:
	int getLayer() const;
	void notifyModelConditionChanged();

	char m_pad000[0x38];
	Coord3D m_field038;
	char m_pad044[0xd8];
	char m_pad11c[4];
	char m_pad120[0x0c];
	unsigned m_field12c;
	char m_pad130[0x48];
	Coord3D m_field178;
	char m_pad184[2];
	unsigned char m_byte186;
	char m_pad187[0x1d];
	unsigned char m_byte1a4;
	char m_pad1a5[0x19f];
	unsigned m_field344;
};

class Locomotor
{
public:
	Real getSurfaceHtAtPt(Real x, Real y);
};

class Rva001BA1C0Handler
{
public:
	Bool behavior(Object *object, const Coord3D *goalPos);

	// The target's receiver is the Locomotor layout whose saved transform is
	// the proven +0x64 translation-column view above.
	__forceinline void applyHeight(Coord3D *position)
	{
		((Rva001B49E0Owner *)this)->setPosition(position);
	}

	void *m_vtable;
	LocomotorTemplate *m_template;
	char m_pad008[0x38];
	unsigned m_flags;
	Real m_preferredHeight;
	char m_pad048[4];
	Real m_heightDamping;
};

Bool Rva001BA1C0Handler::behavior(Object *object, const Coord3D *goalPos)
{
	register Bool requiresConstantCalling = true;
	BfmeVec3CN savedScale =
		((Gen_001B4A20 *)this)->bfmeGetScale();
	// The retail frame reserves the observed temporary/filter area before the
	// first dispatch.  It is intentionally uninitialised; the live branches
	// below use only the witnessed subobjects in it.
	char framePad[0xa8];
	LocomotorTemplate *locomotorTemplate = m_template;
	if (locomotorTemplate != 0 && locomotorTemplate->m_nextOverride != 0)
		locomotorTemplate = (LocomotorTemplate *)
			locomotorTemplate->getFinalOverride();

	int behaviorZ = locomotorTemplate->m_behaviorZ;
	switch (behaviorZ)
	{
	case 0:
		{
			Coord3D position;
			position.x = savedScale.m_bfmeX;
			position.y = savedScale.m_bfmeY;
			position.z = goalPos->z;
			object->m_field178 = position;
			object->m_byte186 = 1;
		}
		requiresConstantCalling = false;
		break;

	case 1:
		if ((object->m_byte1a4 & 8) == 0 &&
			!((BFMESelectionStatusBits *)object)->test(0x90))
		{
			Coord3D position;
			position.x = savedScale.m_bfmeX;
			position.y = savedScale.m_bfmeY;
			int layer = object->getLayer();
			Real waterHeight;
			Real terrainHeight;
			if (TheTerrainLogic->isUnderwater(position.x, position.y,
				&waterHeight, &terrainHeight))
				position.z = waterHeight;
			else
				position.z = TheTerrainLogic->getLayerHeight(position.x,
					position.y, layer, 0, true);
			applyHeight(&position);
		}
		break;

	case 2:
		{
			Coord3D position = object->m_field178;
			Real surfaceHeight = TheTerrainLogic->getGroundHeight(
				position.x, position.y, 0);
			position.z = m_preferredHeight + surfaceHeight;
			applyHeight(&position);
		}
		break;

	case 3:
	case 4:
		{
			Coord3D position = object->m_field178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 3)
				surfaceHeight = ((Locomotor *)this)->getSurfaceHtAtPt(
					position.x, position.y);
			position.z = m_preferredHeight + surfaceHeight;
			applyHeight(&position);
		}
		break;

	case 5:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			int layer = object->getLayer();
			if (layer == 1)
				position.z = TheTerrainLogic->getGroundHeight(
					position.x, position.y, 0);
			Real desiredHeight = m_preferredHeight + position.z;
			Real delta = desiredHeight - object->m_field178.z;
			delta *= m_heightDamping;
			position.z = object->m_field178.z + delta;
			if (position.z != object->m_field178.z)
				applyHeight(&position);
		}
		break;

	case 6:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			Rva01083B5CFilter *filter =
				(Rva01083B5CFilter *)(framePad + 0x40);
			BfmeWideResult iterator =
				((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
					(int)&position, 0x3f800000, 1, (int)filter, 0);
			filter->vtable = (void *)0x01083B5C;
			filter->next = 0;

			Real highestHeight = BfmeZeroRange;
			Object *candidate;
			while (iterator.next(candidate))
			{
				Real candidateHeight =
					((GeometryInfo *)((char *)candidate + 0xac))
						->getMaxHeightAbovePosition();
				if (candidateHeight > highestHeight)
					highestHeight = candidateHeight;
			}
			position.z = m_preferredHeight + highestHeight;
			applyHeight(&position);
		}
		break;

	case 7:
	case 8:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 6)
				surfaceHeight = ((Locomotor *)this)->getSurfaceHtAtPt(
					position.x, position.y);
			Real desiredHeight = m_preferredHeight + surfaceHeight;
			if ((m_flags & 8) != 0)
				desiredHeight = goalPos->z;
			Real delta = (desiredHeight - position.z) * m_heightDamping;
			position.z += delta;
			if (position.z != object->m_field178.z)
				applyHeight(&position);
		}
		break;
	}

	return requiresConstantCalling;
}
