// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Include
// Retail 0x001BA1C0 (1615 B, ret 8): the BFME form of Zero Hour's
// Locomotor::handleBehaviorZ (GameLogic/Object/Locomotor.cpp). The switch on
// the template's behavior-Z field at +0x6C keeps ZH's cases: sea level
// (isUnderwater/getLayerHeight), fixed surface-relative height
// (getSurfaceHtAtPt), ground-and-buildings (KINDOF 7 kind filter and
// getMaxHeightAbovePosition), highest-layer smoothing
// (getHighestLayerForDestination) and the surface/absolute lift cases. BFME
// works on the locomotor's saved transform (+0x64) instead of the object and
// adds a swimming case 0 and a case 8. locoUpdate_maintainCurrentPosition
// calls it with m_maintainPos through ILT 0x0000FEBB, under the opaque name
// the callers already use. OVERRIDE<T> resolves through the inline recursive
// Overridable::getFinalOverride, as Zero Hour's Override.h spells it.
#include "../../../Include/Common/ScalarTypes.h"





#include "Lib/Coord3D.h"

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags() {}
	BitFlags(BogusInitType, int index);
	UnsignedInt test(int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
	void set(int bit) { m_bits[bit >> 5] |= (1u << (bit & 31)); }
	void clear(int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
	UnsignedInt m_bits[NUMBITS / 32];
};

typedef BitFlags<320> ModelConditionFlags;
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class BfmeI1166 : public BitFlags<320>
{
public:
	BfmeI1166(int tag, unsigned first, unsigned second);
};

#define BFME_HAVE_MODELCONDITIONFLAGS
#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS \
	int getLayer() const; \
	void notifyModelConditionChanged(); \
	void clearModelConditionFlags(const BitFlags<320> &flags); \
	void bfmeClearYG(const BitFlags<320> &flags); \
	UnsignedInt isDisabledHeld() const { return m_disabledMask & 8; } \
	Coord3D *getPos178() { return (Coord3D *)(m_unmodelled138 + 0x40); } \
	Bool &hasPos178() { return *(Bool *)(m_unmodelled138 + 0x4e); } \
	const Coord3D *getPositionX() { return hasPos178() ? getPos178() : &m_cachedPos; } \
	void setPos178(const Coord3D &pos) { hasPos178() = true; *getPos178() = pos; } \
	__forceinline void setModelConditionState(int bit) { if (!m_modelConditionFlags.test(bit)) { m_modelConditionFlags.set(bit); notifyModelConditionChanged(); } } \
	__forceinline void clearModelConditionState(int bit) { if (m_modelConditionFlags.test(bit)) { m_modelConditionFlags.clear(bit); notifyModelConditionChanged(); } } \
	__forceinline void clearAndSetModelConditionState(int clr, int set) { if (m_modelConditionFlags.test(clr) || !m_modelConditionFlags.test(set)) { m_modelConditionFlags.clear(clr); m_modelConditionFlags.set(set); notifyModelConditionChanged(); } }
#include "object.h"
#undef OBJECT_TU_MEMBERS

class BFMESelectionStatusBits
{
public:
	Bool test(unsigned bit) const;
};

class BfmeVec3CN
{
public:
	BfmeVec3CN() {}
	BfmeVec3CN(const BfmeVec3CN &other) { x = other.x; y = other.y; z = other.z; }
	Real x;
	Real y;
	Real z;
};

class BfmeVec3EP
{
public:
	BfmeVec3EP() {}
	BfmeVec3EP(const BfmeVec3EP &other) { x = other.x; y = other.y; z = other.z; }
	Real x;
	Real y;
	Real z;
};

class Gen_001B4A20
{
public:
	BfmeVec3CN bfmeGetScale() const;
};

class Gen_001C1D60
{
public:
	BfmeVec3EP bfmeGetRow() const;
};

class Rva001B49E0Owner
{
public:
	void setPosition(const Coord3D *position);
};

class Rva001B95B0HeightState
{
public:
	Real update(Object *obj, const Coord3D *goalPos, Real surfaceHt);
};

Bool rva1b4020(int layer);

#include "../../../Include/Common/Enums/PathfindLayerEnum.h"

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, int layer, Coord3D *normal = 0, Bool clip = true) const;
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0);

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges = false);
};
extern TerrainLogic *TheTerrainLogic;

struct AIData
{
	UnsignedByte m_pad[0x9c];
	Real m_heightThreshold;
};

class AI
{
public:
	UnsignedByte m_pad[0x14];
	AIData *m_aiData;
};
extern AI *TheAI;

class GameLogic
{
public:
	UnsignedByte m_pad[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	UnsignedByte m_pad[0x1ac];
	Real m_gravity;
};
extern GlobalData *TheWritableGlobalData;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual int getPlayerMask();
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);
};

struct BfmeWideEntry
{
	Object *object;
	UnsignedInt unknown04;
};

struct BfmeWideData
{
	BfmeWideEntry *begin;
	BfmeWideEntry *end;
	BfmeWideEntry *capacity;
	BfmeWideEntry *current;
	int references;
};

struct BfmeWideResult
{
	BfmeWideData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &other);
	~BfmeWideResult();
	Object *next()
	{
		BfmeWideEntry *end = value->end;
		if (value->current == end)
			return 0;
		return (value->current++)->object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int pos, int range, int calc, int filters, int order);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vtable;
	Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	UnsignedByte m_pad008[0x6c - 0x08];
	int m_behaviorZ;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_obj)
			return 0;
		return (T *)m_obj->getFinalOverride();
	}
	T *m_obj;
};

class Rva001BA1C0Handler;

class Locomotor
{
	friend class Rva001BA1C0Handler;
protected:
	Real getSurfaceHtAtPt(Real x, Real y);
};

class Rva001BA1C0Handler
{
public:
	Bool behavior(void *object, const Coord3D *goalPos);

	Bool getFlag(int f) const { return ((m_flags >> f) & 1) != 0; }

	void *m_vtable;
	OVERRIDE<LocomotorTemplate> m_template;
	UnsignedByte m_pad008[0x40 - 0x08];
	UnsignedInt m_flags;
	Real m_preferredHeight;
	Real m_pad48;
	Real m_preferredHeightDamping;
};

// ?behavior@Rva001BA1C0Handler@@QAE_NPAXPBUCoord3D@@@Z
Bool Rva001BA1C0Handler::behavior(void *object, const Coord3D *goalPos)
{
	Object *obj = (Object *)object;
	Bool requiresConstantCalling = true;
	BfmeVec3CN pos = ((const Gen_001B4A20 *)this)->bfmeGetScale();

	switch (m_template->m_behaviorZ)
	{
		case 8:
			pos.z = goalPos->z;
			obj->setPos178(*(Coord3D *)&pos);
			return false;

		case 0:
			if (obj->isDisabledHeld())
				break;
			if (((const BFMESelectionStatusBits *)obj)->test(0x90))
				break;
			requiresConstantCalling = false;
			{
				int layer = obj->getLayer();
				Real waterZ;
				Real groundZ;
				if (layer == 1 && TheTerrainLogic->isUnderwater(pos.x, pos.y, &waterZ, &groundZ))
				{
					if (waterZ - groundZ > TheAI->m_aiData->m_heightThreshold * 0.25f)
						requiresConstantCalling = true;
				}
				else
				{
					groundZ = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
					if (TheGameLogic->m_frame > 5 && (layer == 16 || rva1b4020(layer)) && pos.z - groundZ > 20.0f)
						groundZ = pos.z;
				}
				pos.z = groundZ;
				((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
				if (requiresConstantCalling)
				{
					if (waterZ - groundZ > TheAI->m_aiData->m_heightThreshold)
						obj->bfmeClearYG(BfmeI1166(0, 0xe5, 0xe4));
					else
						obj->clearAndSetModelConditionState(0xe5, 0xe4);
				}
				else
				{
					obj->clearModelConditionFlags(BfmeI1166(0, 0xe5, 0xe4));
				}
				requiresConstantCalling = false;
			}
			break;

		case 1:
			requiresConstantCalling = false;
			if (!obj->isDisabledHeld())
			{
				Real waterZ;
				if (TheTerrainLogic->isUnderwater(pos.x, pos.y, &waterZ))
					pos.z = waterZ;
				else
					pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, obj->getLayer());
				((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
			}
			break;

		case 4:
		case 5:
			requiresConstantCalling = true;
			{
				Bool surfaceRel = (m_template->m_behaviorZ == 4);
				Real surfaceHt = surfaceRel ? ((Locomotor *)this)->getSurfaceHtAtPt(pos.x, pos.y) : 0.0f;
				pos.z = m_preferredHeight + (surfaceRel ? surfaceHt : 0);
				((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
			}
			break;

		case 6:
			requiresConstantCalling = true;
			{
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
				Real tallestHeight = 0.0f;
				BfmeWideResult iter = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
					(int)&pos, 0x3f800000, 1,
					(int)&PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 7), KINDOFMASK_NONE), 0);
				Object *them;
				while ((them = iter.next()) != 0)
				{
					Real thisHeight = ((const GeometryInfo *)them->m_geometryInfo)->getMaxHeightAbovePosition();
					if (thisHeight > tallestHeight)
						tallestHeight = thisHeight;
				}
				pos.z = m_preferredHeight + tallestHeight;
				((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
			}
			break;

		case 7:
			requiresConstantCalling = true;
			if (m_preferredHeight != 0.0f || getFlag(3))
			{
				int layerAtDest = obj->getLayer();
				if (layerAtDest == 1)
					layerAtDest = TheTerrainLogic->getHighestLayerForDestination((const Coord3D *)&pos);
				Coord3D normal;
				Real surfaceHt = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layerAtDest, &normal, false);
				Real preferredHeight = m_preferredHeight + surfaceHt;
				if (getFlag(3))
					preferredHeight = goalPos->z;
				Real delta = preferredHeight - pos.z;
				delta *= m_preferredHeightDamping;
				preferredHeight = pos.z + delta;
				Real liftToUse = (preferredHeight - pos.z) * 0.1f;
				if (liftToUse != 0.0f)
				{
					pos.z += liftToUse;
					((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
				}
			}
			break;

		case 2:
		case 3:
			requiresConstantCalling = true;
			if (m_preferredHeight != 0.0f || getFlag(3))
			{
				Real surfaceHt = (m_template->m_behaviorZ == 2) ? ((Locomotor *)this)->getSurfaceHtAtPt(pos.x, pos.y) : 0.0f;
				Real preferredHeight = ((Rva001B95B0HeightState *)this)->update(obj, goalPos, surfaceHt) + surfaceHt;
				if (getFlag(3))
					preferredHeight = goalPos->z;
				Real liftToUse;
				if (obj->m_privateStatus & 1)
				{
					liftToUse = TheWritableGlobalData->m_gravity;
				}
				else
				{
					Real delta = preferredHeight - pos.z;
					delta *= m_preferredHeightDamping;
					preferredHeight = pos.z + delta;
					liftToUse = (preferredHeight - pos.z) * 0.1f;
				}
				if (liftToUse != 0.0f)
				{
					pos.z += liftToUse;
					((Rva001B49E0Owner *)this)->setPosition((const Coord3D *)&pos);
				}
				if (liftToUse > 0.5f)
					obj->setModelConditionState(102);
				else
					obj->clearModelConditionState(102);
			}
			break;
	}

	const Coord3D *cur = obj->getPositionX();
	Coord3D adjusted;
	adjusted.x = cur->x;
	adjusted.y = cur->y;
	BfmeVec3EP row = ((const Gen_001C1D60 *)obj)->bfmeGetRow();
	adjusted.z = pos.z * 2.0f - row.z;
	obj->setPos178(adjusted);
	return requiresConstantCalling;
}
