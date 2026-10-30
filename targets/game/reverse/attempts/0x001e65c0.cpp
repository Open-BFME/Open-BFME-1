// ?getAimPosition@WeaponTemplate@@QAEPAUCoord3D@@PAU2@PBVObject@@1H@Z
// partial score=0.9234 date=2026-10-30
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail RVA 0x001E65C0, 444 bytes (RET 0x10 at +0x1B9, INT3 at +0x1BC).
// Caller: matched Weapon::bfmeGetLOSVictimPos (Weapon_bfmeGetLOSVictimPos.cpp)
// supplies the result buffer, source, victim and the bool-tested 4th word, so
// the ledger's reloc-derived name and ABI are kept.
//
// Structure carried from the BFME 2 donor
// inputs/reference/open-bfme-2 Code/GameEngine/Source/GameLogic/Object/
// WeaponTemplateTargetPositions.cpp (adjustTargetPositionOnVictim, 0x002CAB3A,
// donor rev 20a0cb6173): the jitter call is an ARGUMENT of
// getWorldspaceBestContactPoint (cl pushes the trailing false first), the
// height adjustment only runs on the non-flag path, and the outer arm reads
// pos.z through a volatile cast to keep its own add path.  BFME 1 facts from
// retail: x87 (not SSE) arms `aim + z`, `zDelta + z`, `z + zDelta`; inline
// isNotEmpty (cmp word [m_data+4]); getter 0x001E2640 via ILT 0x00022B3D.
//
// Residue (34 bytes, all frame displacement): every instruction matches, but
// retail places the string in the dead victim argument slot and zDelta in
// the dead flag slot (frame 0x0C); ours gives zDelta the victim slot and the
// string a frame slot (frame 0x10).  See
// targets/game/reverse/attempt_support/20261030-getaimposition-frame-slot.md.

#include "ascii_string.h"
template <> inline bool StringBase<char>::isNotEmpty() const
{
	return m_data && m_data->length != 0;
}

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

enum KindOfType
{
	KINDOF_UNKNOWN = 0
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	Bool getSingleLogicalBonePosition(const char *boneName,
		Coord3D *position, Matrix3D *transform) const;
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *label, Int preference,
		Int seed, Bool skipCollideTest) const;
	Bool testStatus(Int status) const;
};

class BfmeBoundaryGeometry3D
{
public:
	float bfmeZDeltaToCenter() const;
};

class GlobalData
{
private:
	char m_padding[0x1274];

public:
	float m_bfmeAimHeight;
};

extern GlobalData *TheWritableGlobalData;
extern char g_bfmeFmt1041[];
extern Int GetGameLogicRandomValue(Int minimum, Int maximum,
	char *format, Int value);

class Rva001E2640Owner
{
public:
	AsciiString rva001E2640() const;
};

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *result, const Object *source,
		const Object *victim, Int weaponSlot);

private:
};

// ?getAimPosition@WeaponTemplate@@QAEPAUCoord3D@@PAU2@PBVObject@@1H@Z
Coord3D *WeaponTemplate::getAimPosition(Coord3D *result,
	const Object *source, const Object *victim, Int weaponSlot)
{
	Coord3D pos;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	if (victim == 0)
	{
		result->x = pos.x;
		result->y = pos.y;
		result->z = pos.z;
		return result;
	}
	AsciiString preferredTargetBone =
		((const Rva001E2640Owner *)this)->rva001E2640();
	if (preferredTargetBone.isNotEmpty() &&
		victim->getSingleLogicalBonePosition(preferredTargetBone.str(),
			&pos, 0))
	{
		result->x = pos.x;
		result->y = pos.y;
		result->z = pos.z;
		return result;
	}
	if ((unsigned char)weaponSlot != 0)
	{
		victim->getWorldspaceBestContactPoint(&pos,
			(const Coord3D *)((const char *)source + 0x38), 0, 3,
			GetGameLogicRandomValue(0, 0xBC614E, g_bfmeFmt1041, 0x62D), 0);
	}
	else
	{
		pos = *(const Coord3D *)((const char *)victim + 0x38);
		float zDelta = ((const BfmeBoundaryGeometry3D *)
			((const char *)victim + 0xAC))->bfmeZDeltaToCenter();

		if (victim->isKindOf((KindOfType)7) &&
			!source->isKindOf((KindOfType)11) &&
			!source->testStatus(0x54) && victim->testStatus(0x54))
		{
			if (TheWritableGlobalData->m_bfmeAimHeight < zDelta)
				pos.z = *(volatile float *)&TheWritableGlobalData->m_bfmeAimHeight + pos.z;
			else
				pos.z = zDelta + pos.z;
		}
		else
		{
			pos.z = *(volatile float *)&pos.z + zDelta;
		}
	}

	result->x = pos.x;
	result->y = pos.y;
	result->z = pos.z;
	return result;
}
