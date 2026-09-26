// ?onDamage@FlammableUpdate@@UAEXPAVDamageInfo@@@Z
// partial score=0.47 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// FlammableUpdate::onDamage, BFME retail 0x002940D0 (346 bytes). Identity is
// proven by the caller thunk (a FlammableUpdate module method), the
// tryToIgnite call (0x00293990, pinned ILT 0x000322D6), and the BFMEDamageInfo
// constructor call (0x0000ED430, pinned ILT 0x0002C9D5) -- see the earlier
// attempt notes in reverse/re_attempts.log for 0x002940D0. BFME extends the
// Zero Hour body (still present, unmatched, in FlammableUpdate.cpp) with an
// isUnderwater guard, a damage-type==DAMAGE_FLAME-only check (no
// DAMAGE_PARTICLE_BEAM branch survives in retail), a cached last-damage-source
// id, and a contained-object splash path reached through a previously
// unmodelled Object field at +0x1FC.
//
// onDamage is reached through a secondary vtable (DamageModuleInterface in
// the upstream header); retail bakes the this-adjustment directly into this
// one body rather than emitting a separate thunk, so every FlammableUpdate
// field below is read through `this` at the SAME adjusted value MSVC uses in
// the disassembly (this-0x1c is the module data slot, this-0x18 the object
// slot), matching the ReflectDamage::onDamage convention already landed in
// ReflectDamage_onDamage.cpp.
//
// STATUS: partial, not byte-exact. Structure/identity/field layout below is
// fully proven against the disassembly (8+ probe iterations); the remaining
// residue is (a) a persistent edi/esi register-allocation swap (retail:
// edi=this, esi=me; ours: the opposite, no matter the declaration order tried)
// and (b) retail keeps two physically separate epilogues (the splash-loop
// success return at +0x137 and the shared bail-out epilogue at +0x151) while
// our shape collapses to one shared epilogue (ours is 332B vs retail's 346B).
// See reverse/re_attempts.log for the full note.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { DAMAGE_FLAME = 6 };
enum { DEATH_BURNED = 3 };

extern const Real BfmeZeroRange;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
// BFME view: only the fields this body reads.
class DamageInfo
{
public:
	unsigned char m_unreconstructed_00[8];
	Int m_sourceObject;					// +0x08
	unsigned char m_unreconstructed_0c[4];
	Int m_damageType;					// +0x10
	unsigned char m_unreconstructed_14[0x50 - 0x14];
	Real m_actualDamageDealt;			// +0x50
	Real m_actualDamageClipped;			// +0x54
};

// Local temporary BFME builds to splash flame damage into contained objects;
// same "in" shape as DamageInfo, constructed via the pinned ctor.
class BFMEDamageInfo
{
public:
	BFMEDamageInfo();
	unsigned char m_unreconstructed_00[8];
	Int m_sourceObject;					// +0x08
	unsigned char m_unreconstructed_0c[4];
	Int m_damageType;					// +0x10
	unsigned char m_unreconstructed_14[4];
	Int m_deathType;					// +0x18
	Real m_amount;						// +0x1c
	unsigned char m_unreconstructed_20[0x5c - 0x20];	// full retail DamageInfo size is 0x5c
};

// FlammableUpdateModuleData, extended past the Zero Hour tail (which ends at
// +0x20, m_flameDamageExpirationDelay) with a BFME-only splash-enable flag.
class FlammableUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x14];
	Int m_aflameDamageAmount;			// +0x14
	unsigned char m_unreconstructed_18[4];
	Real m_flameDamageLimitData;			// +0x1c
	UnsignedInt m_flameDamageExpirationDelay;	// +0x20
	unsigned char m_unreconstructed_24[0x34 - 0x24];
	unsigned char m_splashEnabled;			// +0x34, BFME-only
};

// The interface found at Object+0x1FC. Only two slots are proven: a
// two-argument notifier at +0x74 and a zero-argument list accessor at
// +0x104. Address-derived name; no owning class recovered.
class Rva002940D0Field1FCTarget
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02(); virtual void _pad03();
	virtual void _pad04(); virtual void _pad05(); virtual void _pad06(); virtual void _pad07();
	virtual void _pad08(); virtual void _pad09(); virtual void _pad0a(); virtual void _pad0b();
	virtual void _pad0c(); virtual void _pad0d(); virtual void _pad0e(); virtual void _pad0f();
	virtual void _pad10(); virtual void _pad11(); virtual void _pad12(); virtual void _pad13();
	virtual void _pad14(); virtual void _pad15(); virtual void _pad16(); virtual void _pad17();
	virtual void _pad18(); virtual void _pad19(); virtual void _pad1a(); virtual void _pad1b();
	virtual void _pad1c();
	virtual void notify(Int code);					// slot 0x74 (29)
	virtual void _pad1e(); virtual void _pad1f(); virtual void _pad20(); virtual void _pad21();
	virtual void _pad22(); virtual void _pad23(); virtual void _pad24(); virtual void _pad25();
	virtual void _pad26(); virtual void _pad27(); virtual void _pad28(); virtual void _pad29();
	virtual void _pad2a(); virtual void _pad2b(); virtual void _pad2c(); virtual void _pad2d();
	virtual void _pad2e(); virtual void _pad2f(); virtual void _pad30(); virtual void _pad31();
	virtual void _pad32(); virtual void _pad33(); virtual void _pad34(); virtual void _pad35();
	virtual void _pad36(); virtual void _pad37(); virtual void _pad38(); virtual void _pad39();
	virtual void _pad3a(); virtual void _pad3b(); virtual void _pad3c(); virtual void _pad3d();
	virtual void _pad3e(); virtual void _pad3f(); virtual void _pad40();
	virtual void *getContainedList();				// slot 0x104 (65)
};

class Object
{
public:
	virtual void _oslot00(); virtual void _oslot04(); virtual void _oslot08(); virtual void _oslot0c();
	virtual void _oslot10(); virtual void _oslot14(); virtual void _oslot18(); virtual void _oslot1c();
	virtual void _oslot20(); virtual void _oslot24(); virtual void _oslot28(); virtual void _oslot2c();
	virtual void _oslot30();
	virtual void attemptDamage(BFMEDamageInfo *damageInfo);	// slot 0x34

	unsigned char m_unreconstructed_04[0x38 - 0x04];
	Real m_posX;						// +0x38
	Real m_posY;						// +0x3c
	unsigned char m_unreconstructed_40[0x74 - 0x40];
	Int m_id;						// +0x74
	unsigned char m_unreconstructed_78[0x90 - 0x78];
	UnsignedInt m_statusBits90;			// +0x90
	unsigned char m_unreconstructed_94[0x1fc - 0x94];
	Rva002940D0Field1FCTarget *m_field1fc;	// +0x1fc, BFME-only, unmodelled elsewhere
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// BFME's TerrainLogic vtable carries extra slots ahead of getLayerHeight and
// isUnderwater (see TerrainLogic_addBridgeToLogic.cpp and
// TerrainLogicIsUnderwater.cpp notes); slot 19 (0x4c) is verified directly
// against the retail vtable, which reads to the landed isUnderwater body at
// 0x001A3970.
class TerrainLogic
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02(); virtual void _pad03();
	virtual void _pad04(); virtual void _pad05(); virtual void _pad06(); virtual void _pad07();
	virtual void _pad08(); virtual void _pad09(); virtual void _pad0a(); virtual void _pad0b();
	virtual void _pad0c(); virtual void _pad0d(); virtual void _pad0e(); virtual void _pad0f();
	virtual void _pad10(); virtual void _pad11(); virtual void _pad12();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ);	// slot 19 (0x4c)
};

extern TerrainLogic *TheTerrainLogic;

// TheBfmeGameLogic exposes the current frame as a plain data member at +0x3c.
class Rva00367E30Logic
{
public:
	unsigned char m_unreconstructed_00[0x3c];
	UnsignedInt m_frame;					// +0x3c
};

extern Rva00367E30Logic *TheBfmeGameLogic;

// Object's doubly-linked contained list, STL-node-shaped (next, prev, value).
struct Rva002940D0Node
{
	Rva002940D0Node *m_next;			// +0x00
	void *m_prev;					// +0x04
	Object *m_value;				// +0x08
};

// The list accessor's return value: a pointer to the sentinel node's own
// storage slot (one dereference reaches the sentinel; the sentinel's own
// +0x00 is its circular "next").
struct Rva002940D0ListRoot
{
	Rva002940D0Node *m_sentinel;
};

class FlammableUpdate
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	void tryToIgnite();
};

// ?onDamage@FlammableUpdate@@UAEXPAVDamageInfo@@@Z
void FlammableUpdate::onDamage(DamageInfo *damageInfo)
{
	char *self = (char *)this;

	if (damageInfo->m_actualDamageClipped > BfmeZeroRange)
		*(Int *)(self + 0x28) = damageInfo->m_sourceObject;

	Object *me = *(Object **)(self - 0x18);

	Bool underwater = TheTerrainLogic->isUnderwater(me->m_posX, me->m_posY, 0, 0);

	if (damageInfo->m_damageType != DAMAGE_FLAME)
		goto epilogue;

	if (underwater)
		goto epilogue;

	{
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	FlammableUpdateModuleData *data = *(FlammableUpdateModuleData **)(self - 0x1c);

	if ((Int)(now - data->m_flameDamageExpirationDelay) > (Int)*(UnsignedInt *)(self + 0x1c))
		*(Real *)(self + 0x18) = data->m_flameDamageLimitData;

	*(UnsignedInt *)(self + 0x1c) = now;

	if ((me->m_statusBits90 & 0xC00) != 0)
		goto epilogue;

	Real limit = *(Real *)(self + 0x18) - damageInfo->m_actualDamageDealt;
	*(Real *)(self + 0x18) = limit;

	if (!(limit <= BfmeZeroRange))
		goto epilogue;

	((FlammableUpdate *)(self - 0x20))->tryToIgnite();

	data = *(FlammableUpdateModuleData **)(self - 0x1c);
	if (data->m_splashEnabled)
	{
		Rva002940D0Field1FCTarget *field1fc = me->m_field1fc;
		if (field1fc)
		{
			BFMEDamageInfo info;

			Int half = data->m_aflameDamageAmount / 2;
			Real amount = (half >= 1) ? (Real)half : 1.0f;

			info.m_sourceObject = me->m_id;
			info.m_amount = amount;
			info.m_damageType = DAMAGE_FLAME;
			info.m_deathType = DEATH_BURNED;

			Rva002940D0ListRoot *list =
				(Rva002940D0ListRoot *)field1fc->getContainedList();
			if (list)
			{
				Rva002940D0Node *sentinel = list->m_sentinel;
				Rva002940D0Node *node = sentinel->m_next;
				while (node != sentinel)
				{
					Object *contained = node->m_value;
					node = node->m_next;
					if (contained)
						contained->attemptDamage(&info);
				}
			}
			return;
		}
	}

	{
	Rva002940D0Field1FCTarget *field1fc = me->m_field1fc;
	if (field1fc)
		field1fc->notify(2);
	}
	}

epilogue:
	;
}
