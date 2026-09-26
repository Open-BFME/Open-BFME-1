// ?bfmeStepBZ@BfmeOwnBZ@@QAEDXZ
// partial score=0.32 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline

// Open-BFME5: BfmeOwnBZ::bfmeStepBZ, retail 0x002579D0, 529 bytes.
//
// Identity: BfmeConv1762.cpp (landed) declares BfmeOwnBZ::bfmeRunBZ, which
// calls bfmeStepBZ() as a forward-declared member (no body) and is the sole
// caller (thunk ?j_00039257@@YAXXZ -> this exact RVA). The __FILE__ literal
// pulled through GetGameLogicRandomValueReal resolves to
// F:\bfme\Code\gameengine\Source\GameLogic\Object\Update\ArrowStormUpdate.cpp
// at lines 0xd9/0xda, confirming the class backs ArrowStormUpdate's per-frame
// arrow-volley stepper; no retained ArrowStormUpdate.cpp source survives, so
// this body is reconstructed straight from the retail bytes.
//
// Shape: this+0xec/+0xf0 is a small one-slot cache (a pending object id and
// an index) that resets to empty once this+0xf0 catches up with
// cfg+0x25c. If the cache is empty, bfmeStepBZ walks the intrusive circular
// list at this+0xe8 (BfmeListBZ, same class as bfmeRunBZ's empty check),
// popping and freeing nodes (12-byte __node_alloc chunks) until it finds one
// whose id resolves to a live Object with bit0 of +0x344 clear. With a
// resolved object it fires the configured weapon straight at it; otherwise,
// if cfg->m_bfmeFlagBZ allows it, it fires the weapon at a jittered
// position (cfg+0x258 is the jitter radius) with height sampled from
// TheTerrainLogic; if the flag forbids it, this step is a no-op success.
// Firing at a target also advances this+0xf0 (the list-cache index); firing
// at a position only advances the overall step counter, this+0xf4. Return
// is (this+0xf4 + 1) >= cfg->0x264 -- the "we're done" boundary bfmeRunBZ
// reads back as m_bfmeDoneBZ.

class Object;
class AsciiString;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
// stlport
#include <hash_map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class WeaponTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(AsciiString) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, Object *target);
};

extern WeaponStore *TheWeaponStore;

#include "StringInline.h"

typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	__forceinline Object *findObjectByIDInline(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objectMap.find(id);
		if (it == m_objectMap.end())
			return 0;

		return (*it).second;
	}

private:
	unsigned char m_pad00[0xb0];
	ObjectPtrHash m_objectMap;
};

extern GameLogic *TheBfmeGameLogic;

// Only vtable slot 6 (offset 0x18) is exercised: a ground-height sample
// taking (x, y, target) and returning a float. The other slots are unproven
// placeholders that keep the vtable shape wide enough to reach slot 6.
class Rva002579D0TerrainLogic
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual float vf6(float x, float y, Object *target);
};

extern Rva002579D0TerrainLogic *TheTerrainLogic;

extern "C" float __cdecl GetGameLogicRandomValueReal(float low, float high, char *file, int line);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object/Update/ArrowStormUpdate.h
class BfmeListBZ
{
public:
	BfmeListBZ *m_bfmeNextBZ;	// +0x0
	BfmeListBZ *m_bfmePrevBZ;	// +0x4
	int m_bfmeIdBZ;		// +0x8
};

class BfmeCfgBZ
{
public:
	unsigned char m_bfmeHeadBZ[0x254];
	AsciiString m_bfmeWeaponNameBZ;	// +0x254
	float m_bfmeJitterBZ;			// +0x258
	int m_field25c;				// +0x25c
	int m_bfmeCountBZ;				// +0x260
	int m_field264;				// +0x264
	char m_bfmeFlagBZ;				// +0x268
};

class BfmeOwnBZ
{
public:
	char bfmeStepBZ();

	unsigned char m_bfmeHeadBZ[4];		// +0x0
	BfmeCfgBZ *m_bfmeCfgBZ;			// +0x4
	Object *m_bfmeSourceBZ;			// +0x8
	unsigned char m_pad0c[0xb0 - 0xc];
	float m_bfmePosXBZ;			// +0xb0
	float m_bfmePosYBZ;			// +0xb4
	unsigned char m_padb8[0xe8 - 0xb8];
	BfmeListBZ *m_bfmeListBZ;		// +0xe8
	int m_bfmeCachedIdBZ;			// +0xec
	int m_bfmeIndexBZ;			// +0xf0
	int m_bfmeStepCountBZ;			// +0xf4
	char m_bfmeDoneBZ;			// +0xf8
};

// ?bfmeStepBZ@BfmeOwnBZ@@QAEDXZ
char BfmeOwnBZ::bfmeStepBZ()
{
	register BfmeCfgBZ *cfg = m_bfmeCfgBZ;
	Object *source = m_bfmeSourceBZ;

	if (m_bfmeIndexBZ >= cfg->m_field25c)
	{
		m_bfmeCachedIdBZ = 0;
		m_bfmeIndexBZ = 0;
	}

	Object *target = 0;
	int id = m_bfmeCachedIdBZ;
	if (id != 0)
	{
		target = TheBfmeGameLogic->findObjectByID(id);
		if (target != 0)
			goto fireWeapon;
	}

	for (;;)
	{
		BfmeListBZ *head = m_bfmeListBZ;
		if (head->m_bfmeNextBZ == head)
		{
			target = 0;
			break;
		}

		BfmeListBZ *node = head->m_bfmeNextBZ;
		id = node->m_bfmeIdBZ;
		m_bfmeCachedIdBZ = id;
		m_bfmeIndexBZ = 0;
		target = 0;

		BfmeListBZ *next = node->m_bfmeNextBZ;
		BfmeListBZ *prev = node->m_bfmePrevBZ;
		prev->m_bfmeNextBZ = next;
		next->m_bfmePrevBZ = prev;
		_STL::__node_alloc<false, 0>::deallocate(node, 0xc);

		id = m_bfmeCachedIdBZ;
		if (id == 0)
			continue;

		target = TheBfmeGameLogic->findObjectByIDInline(id);
		if (target == 0)
			continue;

		if (*(unsigned char *)((char *)target + 0x344) & 1)
		{
			target = 0;
			continue;
		}

		break;
	}

fireWeapon:
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(cfg->m_bfmeWeaponNameBZ);

		if (target != 0)
		{
			TheWeaponStore->createAndFireTempWeapon(wt, source, target);
		}
		else
		{
			if (!cfg->m_bfmeFlagBZ)
			{
				return 1;
			}

			float jx = GetGameLogicRandomValueReal(
				m_bfmePosXBZ - cfg->m_bfmeJitterBZ,
				m_bfmePosXBZ + cfg->m_bfmeJitterBZ,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\ArrowStormUpdate.cpp", 0xd9);
			float jy = GetGameLogicRandomValueReal(
				m_bfmePosYBZ - cfg->m_bfmeJitterBZ,
				m_bfmePosYBZ + cfg->m_bfmeJitterBZ,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\ArrowStormUpdate.cpp", 0xda);

			Coord3D pos;
			pos.x = jx;
			pos.y = jy;
			pos.z = TheTerrainLogic->vf6(jx, jy, target);

			TheWeaponStore->createAndFireTempWeapon(wt, source, &pos);

			++m_bfmeStepCountBZ;
			return (char)(m_bfmeStepCountBZ >= cfg->m_field264);
		}
	}

	++m_bfmeIndexBZ;
	++m_bfmeStepCountBZ;
	return (char)(m_bfmeStepCountBZ >= cfg->m_field264);
}
