// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?doDamageFX@Rva0020F240Body@@IAEXPBVDamageInfo@@@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp
//
// Body at 0x0020F240 (__thiscall, RET 4, 185 bytes), reached only through ILT
// 0x00016865. It is Zero Hour's ActiveBody::doDamageFX: with a current
// DamageFX (+0xDC) it skips a repeat of the last damage type inside the
// throttle window, finds the source object, plays DamageFX::doDamageFX for
// the damage type and amount, and records the type and the next allowed frame
// from the per-type throttle time (0x00065F10 via ILT 0x000046F1). No caller
// or table proves the owning class, so it keeps the address.
//
// BFME differences: doDamageFX returns whether it played and only then are
// the type and throttle recorded; there is no damage-FX override type; after
// the FX, each ObjectCreationList record (+0xC0 vector, 12 bytes) whose type
// matches the damage info's +0x28 and whose flag is clear is created at the
// owner object.
//
// Layout: owner object +0x08, next damage-FX frame +0x38, last damage-FX type
// +0x3C, OCL records +0xC0, current DamageFX +0xDC; DamageInfo source id
// +0x08, damage type +0x14, OCL type +0x28, actual damage dealt +0x50.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int ObjectID;

#define NULL 0

#include "../../../../Include/Common/Enums/DamageType.h"

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	char m_unmodelled000[0x08];
	ObjectID m_sourceID;						// +0x08
	char m_unmodelled00c[0x14 - 0x0c];
	DamageType m_damageType;					// +0x14
	char m_unmodelled018[0x28 - 0x18];
	Int m_oclType;							// +0x28
	char m_unmodelled02c[0x50 - 0x2c];
	Real m_actualDamageDealt;					// +0x50
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }
	Object *findObjectByID(ObjectID id);
private:
	char m_unmodelled000[0x3c];
	UnsignedInt m_frame;						// +0x3C
};

extern GameLogic *TheGameLogic;

// The per-type throttle table at 0x00065F10: 64-byte entries, throttle time
// at +0x0C; the second argument (Zero Hour's source object) is unused.
class Rva00065F10Table
{
public:
	void *lookup(Int index, Int unused) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DamageFX.h
// Zero Hour's DamageFX; the ledger's DamageFX::doDamageFX decoration at
// 0x00066780 is contradicted by tools/ilt_oracle.py, so the class keeps the
// address of that body.
class Rva00066780DamageFX
{
public:
	Bool doDamageFX(DamageType t, Real damageAmount, const Object *source, const Object *victim) const;
	UnsignedInt getDamageFXThrottleTime(DamageType t, const Object *source) const
	{
		return (UnsignedInt)((const Rva00065F10Table *)this)->lookup(t, (Int)source);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationList
{
public:
	void createInternal(const Object *primaryObj, const Object *secondaryObj, UnsignedInt lifetimeFrames) const;
};

struct Rva0020F240OCLRecord
{
	const ObjectCreationList *m_ocl;
	Int m_type;
	Int m_flag;
};

class Rva0020F240Body
{
protected:
	void doDamageFX(const DamageInfo *damageInfo);

	Object *getObject() const { return m_object; }

private:
	char m_unmodelled000[0x08];
	Object *m_object;						// +0x08
	char m_unmodelled00c[0x38 - 0x0c];
	UnsignedInt m_nextDamageFXTime;					// +0x38
	DamageType m_lastDamageFXDone;					// +0x3C
	char m_unmodelled040[0xc0 - 0x40];
	_STL::vector<Rva0020F240OCLRecord> m_damageOCLs;		// +0xC0
	char m_unmodelled0cc[0xdc - 0xcc];
	const Rva00066780DamageFX *m_curDamageFX;					// +0xDC
};

void Rva0020F240Body::doDamageFX( const DamageInfo *damageInfo )
{
	const Rva00066780DamageFX *damageFX = m_curDamageFX;
	DamageType damageTypeToUse = damageInfo->m_damageType;

	if (damageFX)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (damageTypeToUse == m_lastDamageFXDone && m_nextDamageFXTime > now)
			return;
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);	// might be null, I guess
		if (damageFX->doDamageFX(damageTypeToUse, damageInfo->m_actualDamageDealt, source, getObject()))
		{
			m_lastDamageFXDone = damageTypeToUse;
			m_nextDamageFXTime = now + m_curDamageFX->getDamageFXThrottleTime(damageTypeToUse, source);
		}
	}

	for (_STL::vector<Rva0020F240OCLRecord>::const_iterator it = m_damageOCLs.begin(); it != m_damageOCLs.end(); ++it)
	{
		Rva0020F240OCLRecord record = *it;
		if (record.m_type == damageInfo->m_oclType && record.m_flag == 0 && record.m_ocl)
			record.m_ocl->createInternal(getObject(), NULL, 0);
	}
}
