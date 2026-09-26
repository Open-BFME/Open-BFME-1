// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME: MetaImpactNugget vtable slot 6, retail 0x002DD680, 762 bytes.
//
// Identity: vtable 0x010CEFA4 (installed by the ctor at 0x002DDBE0, which
// parseMetaImpactNugget 0x001E5F00 allocates) slot 6 is ILT 0x0004082C, the
// only reference to that thunk and its only caller. Slot 13 is the landed
// MetaImpactNugget::execute. parseMetaImpactNugget runs the INI callback
// 0x002DD2B0 whose FieldParse table 0x00CCEE68 names +0x5C ShockWaveRadius and
// +0x60 ShockWaveArc (and +0x78 HeroResist, the field execute tests).
// The method's own name is not proven, so it keeps the address. Slot 1
// (0x002DD5B0, still a dump) is the per-object filter, likewise unnamed.

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "Lib/trig.h"

// BfmeWideResult descriptor: vector start/end/capacity, cursor at +0x0c and
// reference count at +0x10; entries are eight bytes (see
// AutoFindHealingUpdateScanClosestTarget.cpp).
struct ShockWaveEntry
{
	Object *object;
	unsigned int unknown04;
};
struct ShockWaveResultData
{
	std::vector<ShockWaveEntry> entries;
	ShockWaveEntry *current;
	int references;
};
struct BfmeWideResult
{
	ShockWaveResultData *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
	{
		if (--m_value->references == 0)
			delete m_value;
	}
	Object *next()
	{
		if (m_value->current == m_value->entries.end())
			return 0;
		return (m_value->current++)->object;
	}
};
class BfmeWideForwardA
{
public:
	BfmeWideResult bfmeForwardWideA(int, int, int, int);
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class MetaImpactNugget
{
public:
	virtual ~MetaImpactNugget();
	virtual Bool rva002DD5B0(Weapon *weapon, Object *victim);
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void rva002DD680(Weapon *weapon, const Coord3D *pos);
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void execute(Weapon *weapon, Object *victim);

	unsigned char m_pad04[0x5C - 4];
	Real m_shockWaveRadius;
	Real m_shockWaveArc;
};

void MetaImpactNugget::rva002DD680(Weapon *weapon, const Coord3D *pos)
{
	if (!weapon)
		return;
	if (!pos)
		return;

	Real radius = m_shockWaveRadius;
	if (radius < 1.0f)
		radius = 1.0f;

	BfmeWideResult iter = ((BfmeWideForwardA *)ThePartitionManager)->
		bfmeForwardWideA((int)pos, *(int *)&radius, 3, 0);
	while (Object *obj = iter.next()) {
		if (!rva002DD5B0(weapon, obj))
			continue;
		if (m_shockWaveArc < PI) {
			Coord3D delta;
			delta.set(obj->getPosition());
			delta.sub(pos);
			// +0x08 is the id MetaImpactNugget::execute also hands to findObjectByID.
			Object *source = TheGameLogic->findObjectByID(*(const Int *)((const char *)weapon + 8));
			if (!source)
				continue;
			Coord3D away;
			away.set(pos);
			away.sub(source->getPosition());
			Vector3 facing(away.x, away.y, away.z);
			if (away.length() == 0.0f)
				facing = source->getTransformMatrix()->Get_X_Vector();
			Vector3 toTarget(delta.x, delta.y, delta.z);
			facing.Normalize();
			toTarget.Normalize();
			if (Vector3::Dot_Product(toTarget, facing) < Cos(m_shockWaveArc))
				continue;
		}
		execute(weapon, obj);
	}
}
