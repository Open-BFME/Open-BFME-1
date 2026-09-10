// ?getAimPosition@WeaponTemplate@@QAEPAUCoord3D@@PAU2@PBVObject@@1H@Z
// partial score=0.52 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// BFME WeaponTemplate::getAimPosition, retail RVA 0x001E65C0 (444 bytes).
// The caller at Weapon::bfmeGetLOSVictimPos supplies the hidden Coord3D
// return buffer, source object, victim object, and weapon slot.  BFME's
// preferred-target-bone accessor returns its one-pointer AsciiString into the
// stack slot later reused for the local string; the accessor body is the
// existing 0x001E2640 ICF body (ILT 0x00022B3D), whose +0x80 source offset is
// the matched WeaponTemplate layout's PreferredTargetBone field.

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

template <typename T>
class StringBase
{
	friend class BFMERetailAsciiString;

	private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	T *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other)
	{
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

	Bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)((const char *)m_data + 4) != 0;
	}

private:
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

class WeaponTemplate
{
public:
	BFMERetailAsciiString getPreferredTargetBone() const;
	Coord3D *getAimPosition(Coord3D *result, const Object *source,
		const Object *victim, Int weaponSlot);

private:
	char m_padding[0x80];
	BFMERetailAsciiString m_preferredTargetBone;
};

// ?getAimPosition@WeaponTemplate@@QAEPAUCoord3D@@PAU2@PBVObject@@1H@Z
Coord3D *WeaponTemplate::getAimPosition(Coord3D *result,
	const Object *source, const Object *victim, Int weaponSlot)
{
	Coord3D local = { 0.0f, 0.0f, 0.0f };
	if (victim == 0)
	{
		result->x = local.x;
		result->y = local.y;
		result->z = local.z;
		return result;
	}

	BFMERetailAsciiString preferredTargetBone = getPreferredTargetBone();
	if (preferredTargetBone.isNotEmpty() &&
		victim->getSingleLogicalBonePosition(preferredTargetBone.str(),
			&local, 0))
	{
		result->y = local.y;
		result->z = local.z;
	}
	else
	{
		if (weaponSlot != 0)
		{
			Int seed = GetGameLogicRandomValue(0, 0xBC614E, g_bfmeFmt1041,
				0x62D);
			victim->getWorldspaceBestContactPoint(&local,
				(const Coord3D *)((const char *)source + 0x38), 0, 3, seed, 0);
		}
		else
		{
			const Coord3D *victimPosition =
				(const Coord3D *)((const char *)victim + 0x38);
			local.x = victimPosition->x;
			local.y = victimPosition->y;
			local.z = victimPosition->z;
		}

		float zDelta = ((const BfmeBoundaryGeometry3D *)
			((const char *)victim + 0xAC))->bfmeZDeltaToCenter();

		if (victim->isKindOf((KindOfType)7) &&
			!source->isKindOf((KindOfType)11) &&
			!source->testStatus(0x54) && victim->testStatus(0x54))
		{
			float aimHeight = TheWritableGlobalData->m_bfmeAimHeight;
			if (aimHeight < zDelta)
				aimHeight = zDelta;
			local.z += aimHeight;
		}
		else
		{
			local.z += zDelta;
		}

		result->y = local.y;
		result->z = local.z;
	}

	result->x = local.x;
	return result;
}
