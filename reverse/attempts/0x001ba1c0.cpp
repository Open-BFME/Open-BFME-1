// ?behavior@Rva001BA1C0Handler@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.16 date=2026-09-19
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc
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

Bool rva1b4020(int value);

#pragma comment(linker, "/alternatename:?rva1b4020@@YA_NH@Z=?j_000182f5@@YAXXZ")

template <unsigned NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, int index);
	unsigned m_bits[NUMBITS / 32];
};

#pragma comment(linker, "/alternatename:??0?$BitFlags@$0MA@@@QAE@W4BogusInitType@0@H@Z=?j_00008d0f@@YAXXZ")

#define KINDOFMASK_NONE (*(const BitFlags<192> *)0x012ED8B8)

struct VptrZeroBlock24
{
	unsigned m_dword00;
	unsigned m_dword04;
	unsigned m_dword08;
	unsigned m_dword0c;
	unsigned m_dword10;
	unsigned m_dword14;
};

class Rva01083B5CFilter
{
	virtual Bool allow(Object *)
	{
		return false;
	}

public:
	Rva01083B5CFilter() : next(0) {}
	virtual ~Rva01083B5CFilter() {}
	virtual int getPlayerMask();

	Rva01083B5CFilter *link(Rva01083B5CFilter *filter)
	{
		next = filter;
		return this;
	}

	Rva01083B5CFilter *next;
};

class Rva000C3DD0VptrZeroBlockObject : public Rva01083B5CFilter
{
public:
	Rva000C3DD0VptrZeroBlockObject(const VptrZeroBlock24 &first,
		const VptrZeroBlock24 &second);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

#pragma comment(linker, "/alternatename:??0Rva000C3DD0VptrZeroBlockObject@@QAE@ABUVptrZeroBlock24@@0@Z=?j_000382fd@@YAXXZ")

class Rva01083B5CRelationship : public Rva01083B5CFilter
{
public:
	Rva01083B5CRelationship(Object *subject, int relationFlags,
		Bool relationMatch)
		: m_object(subject), m_flags(relationFlags), m_match(relationMatch)
	{
	}

	Object *m_object;
	int m_flags;
	Bool m_match;
};

/* This is the concrete 0x1083b5c filter head witness. */
struct Rva01083B5CFilterStorage
{
	void *vtable;
	void *next;
	Object *object;
	int flags;
	Bool match;
};

class BfmeI1166
{
public:
	BfmeI1166(int tag, unsigned first, unsigned second);

	unsigned m_bits[10];
};

#pragma comment(linker, "/alternatename:??0BfmeI1166@@QAE@HII@Z=?j_00004048@@YAXXZ")

class Rva001B6E60VectorOwner
{
public:
	void insert(BfmeI1166 *value);
};

#pragma comment(linker, "/alternatename:?insert@Rva001B6E60VectorOwner@@QAEXPAVBfmeI1166@@@Z=?j_0000b95b@@YAXXZ")

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPAV1@XZ=?j_000022bb@@YAXXZ")

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

#pragma comment(linker, "/alternatename:?bfmeGetScale@Gen_001B4A20@@QBE?AVBfmeVec3CN@@XZ=?j_0000290a@@YAXXZ")

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

#pragma comment(linker, "/alternatename:?setPosition@Rva001B49E0Owner@@QAEXPBUCoord3D@@@Z=?j_0000c1b7@@YAXXZ")

class BFMESelectionStatusBits
{
public:
	Bool test(unsigned mask) const;
};

#pragma comment(linker, "/alternatename:?test@BFMESelectionStatusBits@@QBE_NI@Z=?j_0003ab20@@YAXXZ")

class TerrainLogic
{
public:
	int getHighestLayerForDestination(const Coord3D *position, Bool clip);

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

#pragma comment(linker, "/alternatename:?getHighestLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PBUCoord3D@@_N@Z=?j_00006091@@YAXXZ")

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define BfmeZeroRange (*(const Real *)0x01075350)

class Object
{
public:
	int getLayer() const;
	void bfmeClearYG(const BitFlags<320> &flags);
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

#pragma comment(linker, "/alternatename:?getLayer@Object@@QBEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

#pragma comment(linker, "/alternatename:?bfmeClearYG@Object@@QAEXABV?$BitFlags@$0BEA@@@@Z=?j_0001a9dd@@YAXXZ")

class Rva0003B9FDVec3
{
public:
	Real x;
	Real y;
	Real z;
};

class Rva001C1D60Owner
{
public:
	Rva0003B9FDVec3 rva0003b9fd() const;
};

#pragma comment(linker, "/alternatename:?rva0003b9fd@Rva001C1D60Owner@@QBE?AVRva0003B9FDVec3@@XZ=?j_0003b9fd@@YAXXZ")

class Rva0017E000AIPathData
{
public:
	char m_pad000[0x9c];
	Real m_heightThreshold;
};

class Rva0017E000AI
{
public:
	char m_pad000[0x14];
	Rva0017E000AIPathData *m_pathData;
};

#define TheAI (*(Rva0017E000AI **)0x012EF214)
#define g_bfmeScaleBK (*(const Real *)0x01075C70)
#define g_bfmeK1253 (*(const Real *)0x0107533C)

class Rva00367E30Logic
{
public:
	char m_pad000[0x3c];
	int m_frame;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)
#define g_bfmeHeightTolerance (*(const Real *)0x010977E0)

class Locomotor
{
public:
	Real getSurfaceHtAtPt(Real x, Real y);
};

#pragma comment(linker, "/alternatename:?getSurfaceHtAtPt@Locomotor@@QAEMMM@Z=?j_0001d840@@YAXXZ")

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
	LocomotorTemplate *locomotorTemplate = m_template;
	if (locomotorTemplate != 0 && locomotorTemplate->m_nextOverride != 0)
		locomotorTemplate = (LocomotorTemplate *)
			locomotorTemplate->getFinalOverride();

	int behaviorZ = locomotorTemplate->m_behaviorZ;
	switch (behaviorZ)
	{
	case 8:
		{
			Coord3D position;
			position.x = savedScale.m_bfmeX;
			position.y = savedScale.m_bfmeY;
			position.z = goalPos->z;
			object->m_byte186 = 1;
			object->m_field178 = position;
		}
		requiresConstantCalling = false;
		break;

	case 0:
		if ((object->m_byte1a4 & 8) == 0 &&
			!((BFMESelectionStatusBits *)object)->test(0x90))
		{
			Coord3D position;
			position.x = savedScale.m_bfmeX;
			position.y = savedScale.m_bfmeY;
			int layer = object->getLayer();
			Real waterHeight;
			Real terrainHeight;
			requiresConstantCalling = false;
			if (layer == 1 && TheTerrainLogic->isUnderwater(
				position.x, position.y, &waterHeight, &terrainHeight))
			{
				Rva0017E000AI *ai = TheAI;
				if (ai != 0 && ai->m_pathData != 0 &&
					(position.z - terrainHeight) <
					ai->m_pathData->m_heightThreshold * g_bfmeScaleBK)
				{
					requiresConstantCalling = true;
				}
				else
				{
					position.z = waterHeight;
				}
			}
			else
			{
				Coord3D normal;
				position.z = TheTerrainLogic->getLayerHeight(
					position.x, position.y, layer, &normal, true);
			}
			applyHeight(&position);

			if (!requiresConstantCalling)
			{
				BfmeI1166 flags(0, 0xe4, 0xe5);
				((Rva001B6E60VectorOwner *)object)->insert(&flags);
			}
			else if (TheBfmeGameLogic != 0 &&
				TheBfmeGameLogic->m_frame > 5 && layer != 0x10 &&
				rva1b4020(layer) &&
				(terrainHeight - position.z) < g_bfmeHeightTolerance)
			{
				BfmeI1166 flags(0, 0xe4, 0xe5);
				object->bfmeClearYG(
					*reinterpret_cast<const BitFlags<320> *>(&flags));
				requiresConstantCalling = false;
			}
			else
			{
				unsigned status = object->m_field12c;
				if ((status & 0x20) == 0)
				{
					if ((status & 0x10) == 0)
					{
						object->m_field12c = (status & ~0x20) | 0x10;
						object->notifyModelConditionChanged();
					}
				}
			}
		}
		break;

	case 1:
		if ((object->m_byte1a4 & 8) == 0)
		{
			Coord3D position;
			position.x = savedScale.m_bfmeX;
			position.y = savedScale.m_bfmeY;
			Real waterHeight;
			Real terrainHeight;
			if (TheTerrainLogic->isUnderwater(position.x, position.y,
				&waterHeight, &terrainHeight))
				position.z = waterHeight;
			else
			{
				Coord3D normal;
				position.z = TheTerrainLogic->getLayerHeight(position.x,
					position.y, object->getLayer(), &normal, true);
			}
			applyHeight(&position);
		}
		break;

	case 4:
	case 5:
		{
			Coord3D position = object->m_field178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 4)
				surfaceHeight = ((Locomotor *)this)->getSurfaceHtAtPt(
					position.x, position.y);
			position.z = m_preferredHeight + surfaceHeight;
			applyHeight(&position);
		}
		break;

	case 6:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			Real highestHeight = TheTerrainLogic->getGroundHeight(
				position.x, position.y, 0);
			BitFlags<192> kindOfMask(BitFlags<192>::kInit, 7);
			BfmeWideResult iterator =
				((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
					(int)&position, 0x3f800000, 1,
					(int)(Rva01083B5CRelationship(object, 4, false).link(
						&Rva000C3DD0VptrZeroBlockObject(
							*reinterpret_cast<const VptrZeroBlock24 *>(&kindOfMask),
							*reinterpret_cast<const VptrZeroBlock24 *>(
								&KINDOFMASK_NONE)))), 0);

			Object *candidate;
			while (iterator.next(candidate))
			{
				if (candidate != 0)
				{
					Real candidateHeight =
						((GeometryInfo *)((char *)candidate + 0xac))
							->getMaxHeightAbovePosition();
					if (candidateHeight > highestHeight)
						highestHeight = candidateHeight;
				}
			}
			position.z = m_preferredHeight + highestHeight;
			applyHeight(&position);
		}
		break;

	case 7:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			int layer = object->getLayer();
			if (layer == 1)
				layer = TheTerrainLogic->getHighestLayerForDestination(
					&position, false);
			Coord3D normal;
			Real surfaceHeight = TheTerrainLogic->getLayerHeight(
				position.x, position.y, layer, &normal, false);
			Real desiredHeight = m_preferredHeight + surfaceHeight;
			if ((m_flags & 8) != 0)
				desiredHeight = goalPos->z;
			Real delta = (desiredHeight - position.z) * m_heightDamping;
			position.z += delta;
			if (position.z != object->m_field178.z)
				applyHeight(&position);
		}
		break;

	case 2:
	case 3:
		if (m_preferredHeight != BfmeZeroRange || (m_flags & 8) != 0)
		{
			Coord3D position = object->m_field178;
			Real surfaceHeight = 0.0f;
			if (behaviorZ == 2)
				surfaceHeight = ((Locomotor *)this)->getSurfaceHtAtPt(
					position.x, position.y);
			Real desiredHeight = m_preferredHeight + surfaceHeight;
			if ((m_flags & 8) != 0)
				desiredHeight = goalPos->z;
			Real delta = (desiredHeight - position.z) * m_heightDamping;
			position.z += delta;
			Real lift = ((Rva001B95B0Owner *)this)->rva001b95b0(
				object, goalPos, surfaceHeight);
			position.z += lift;
			if (position.z != object->m_field178.z)
			{
				applyHeight(&position);
				object->notifyModelConditionChanged();
			}
		}
		break;
	}

	return requiresConstantCalling;
}
