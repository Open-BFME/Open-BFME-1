// ?behavior@Rva001BA1C0Handler@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.15 date=2026-09-10
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// BFME body at 0x001BA1C0.  The matched movement dispatcher at 0x001BC820
// passes Object* and const Coord3D* through ILT 0x0000FEBB; the raw callee
// returns Bool with ret 8.  The handler reads the LocomotorTemplate behavior-Z
// field at +0x6c and updates the BFME Object position at +0x178.

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
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
	Coord3D m_position;
	char m_pad044[0xe8];
	unsigned m_status12c;
	char m_pad130[0x48];
	Coord3D m_position178;
	char m_pad184[2];
	unsigned char m_status186;
	char m_pad187[0x1d];
	unsigned char m_disabledMask;
	char m_pad1a5[0x19f];
	unsigned m_status344;
};

class Rva001BA1C0Handler
{
public:
	Bool behavior(Object *object, const Coord3D *goalPos);

	// These declarations are the typed views of the concrete retail calls in
	// this body.  Their ILT RVAs are pinned in reverse/symbols.csv.
	void prepareBehavior();
	void applyHeight(Coord3D *position);
	Real getSurfaceHeight(Real x, Real y);
	Real calculateHeight(Object *object, const Coord3D *goalPos,
		Real surfaceHeight);
	void refreshObjectState(Object *object);

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
	prepareBehavior();

	Bool requiresConstantCalling = true;
	LocomotorTemplate *locomotorTemplate = m_template;
	if (locomotorTemplate != 0 && locomotorTemplate->m_nextOverride != 0)
		locomotorTemplate = (LocomotorTemplate *)
			locomotorTemplate->getFinalOverride();

	int behaviorZ = locomotorTemplate->m_behaviorZ;
	switch (behaviorZ)
	{
	case 0:
		requiresConstantCalling = false;
		break;

	case 1:
		if ((object->m_disabledMask & 0x90) == 0)
		{
			Coord3D position = object->m_position178;
			Real waterHeight;
			Real terrainHeight;
			if (TheTerrainLogic->isUnderwater(position.x, position.y,
				&waterHeight, &terrainHeight))
				position.z = waterHeight;
			else
				position.z = TheTerrainLogic->getLayerHeight(position.x,
					position.y, object->getLayer(), 0, true);
			object->m_position178 = position;
		}
		break;

	case 2:
		{
			Coord3D position = object->m_position178;
			Real surfaceHeight = TheTerrainLogic->getGroundHeight(
				position.x, position.y, 0);
			position.z = m_preferredHeight + surfaceHeight;
			applyHeight(&position);
		}
		break;

	case 3:
	case 4:
		{
			Coord3D position = object->m_position178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 3)
				surfaceHeight = getSurfaceHeight(position.x, position.y);
			position.z = m_preferredHeight + surfaceHeight;
			applyHeight(&position);
		}
		break;

	case 5:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_position178;
			int layer = object->getLayer();
			if (layer == 1)
				position.z = TheTerrainLogic->getGroundHeight(
					position.x, position.y, 0);
			Real desiredHeight = m_preferredHeight + position.z;
			Real delta = desiredHeight - object->m_position178.z;
			delta *= m_heightDamping;
			position.z = object->m_position178.z + delta;
			if (position.z != object->m_position178.z)
				applyHeight(&position);
		}
		break;

	case 6:
	case 7:
	case 8:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_position178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 6)
				surfaceHeight = getSurfaceHeight(position.x, position.y);
			Real desiredHeight = m_preferredHeight + surfaceHeight;
			if ((m_flags & 8) != 0)
				desiredHeight = goalPos->z;
			Real delta = (desiredHeight - position.z) * m_heightDamping;
			position.z += delta;
			if (position.z != object->m_position178.z)
				applyHeight(&position);
		}
		break;
	}

	return requiresConstantCalling;
}
