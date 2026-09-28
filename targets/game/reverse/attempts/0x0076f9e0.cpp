// ?validate@Rva0076F9E0Owner@@QBEXPAURva0076F9E0Names@@@Z
// partial score=0.77 date=2026-09-28
// ?validate@Rva0076F9E0Owner@@QBEXPAURva0076F9E0Names@@@Z -- retail 0x0076F9E0, 1603 bytes (banked, not matched).
//
// Zero Hour twin: ModelConditionInfo::validateWeaponBarrelInfo (W3DModelDraw.cpp),
// written as that source reads, with BFME's differences taken from the
// disassembly: the four bone-name arrays and the recoil/muzzle-flash flags live
// in the object the caller (0x00774AA0) passes as the one stack argument; the
// outer test is fx-or-launch-bone only; the unadorned fallback looks up only the
// launch bone (inlined findPristineBone) and the fx bone (the out-of-line body at
// 0x00769260).
//
// Levers, in the order they moved it (probe non-reloc diffs):
//   1245 (old stash) -> 1081: WWMath Vector4/Matrix3D copy ctor + member-wise
//     operator=, a WeaponBarrelInfo ctor that zeroes only the three bone ints,
//     the out-of-line STLport _Construct retail calls.
//   1081 -> 361: give _Construct a VISIBLE (noinline) body.  With every callee
//     that receives &info visible and non-retaining, MSVC keeps info.m_fxBone in
//     ebx across the sprintf/nameToKey/find calls and prevFxBone in memory,
//     exactly as retail.
// Remaining (361): the fallback's ternary `plbName.isEmpty() ? 0 :
// findPristineBone(NAMEKEY(plbName), 0)` gives the inlined key parameter its own
// $T slot (frame 0x1A4, retail 0x1A0 reuses the loop's key slot at esp+0x18);
// the if-statement spellings fix the frame but reorder the key/wslot slots and
// the fallback's branch layout (414-452 diffs).
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <stdio.h>
#include <vector>

typedef int Int;
typedef bool Bool;

class Vector4
{
public:
	Vector4(void) {}
	Vector4(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	void Make_Identity(void)
	{
		Row[0].X = 1.0f; Row[0].Y = 0.0f; Row[0].Z = 0.0f; Row[0].W = 0.0f;
		Row[1].X = 0.0f; Row[1].Y = 1.0f; Row[1].Z = 0.0f; Row[1].W = 0.0f;
		Row[2].X = 0.0f; Row[2].Y = 0.0f; Row[2].Z = 1.0f; Row[2].W = 0.0f;
	}

	Matrix3D(void) {}
	Matrix3D(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }
	Matrix3D &operator=(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; return *this; }
	Vector4 Row[3];
};

struct Rva0076F9E0AsciiData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

struct Rva0076F9E0AsciiString
{
	Rva0076F9E0AsciiData *m_data;

	bool isEmpty(void) const { return m_data == 0 || m_data->m_length == 0; }
	const char *str(void) const { return m_data ? reinterpret_cast<const char *>(m_data) + 8 : ""; }
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const Rva0076F9E0AsciiString &name) { return nameToKey(name.str()); }
};

extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

extern void setFPMode(void);

struct Rva0075B660Logic
{
	char m_pad00[0x6b];
	bool m_flag;
};

struct Rva0075B660State
{
	char m_pad00[0x54];
	bool m_flag;
};

extern Rva0075B660Logic *TheBfmeGameLogic;
extern Rva0075B660State *TheGameState;

inline Bool isValidTimeToCalcLogicStuff()
{
	return (TheBfmeGameLogic && TheBfmeGameLogic->m_flag) || (TheGameState && TheGameState->m_flag);
}

enum { WEAPONSLOT_COUNT = 4 };

// The caller's object: four per-slot bone-name arrays and the per-slot
// recoil/muzzle-flash flags this body sets.
struct Rva0076F9E0Names
{
	char m_pad00[0x4c];
	Rva0076F9E0AsciiString m_weaponFireFXBoneName[WEAPONSLOT_COUNT];			///< +0x4C
	Rva0076F9E0AsciiString m_weaponRecoilBoneName[WEAPONSLOT_COUNT];			///< +0x5C
	Rva0076F9E0AsciiString m_weaponMuzzleFlashName[WEAPONSLOT_COUNT];			///< +0x6C
	Rva0076F9E0AsciiString m_weaponProjectileLaunchBoneName[WEAPONSLOT_COUNT];	///< +0x7C
	char m_pad8c[0x120 - 0x8c];
	Bool m_hasRecoilBonesOrMuzzleFlashes[WEAPONSLOT_COUNT];					///< +0x120
};

struct ModelConditionInfo
{
	struct WeaponBarrelInfo
	{
		Int m_recoilBone;
		Int m_fxBone;
		Int m_muzzleFlashBone;
		Matrix3D m_projectileOffsetMtx;

		WeaponBarrelInfo() : m_recoilBone(0), m_fxBone(0), m_muzzleFlashBone(0) {}
		void clear()
		{
			m_recoilBone = 0;
			m_fxBone = 0;
			m_muzzleFlashBone = 0;
			m_projectileOffsetMtx.Make_Identity();
		}
	};
};

namespace _STL
{
	template<> __declspec(noinline) void _Construct<ModelConditionInfo::WeaponBarrelInfo, ModelConditionInfo::WeaponBarrelInfo>(ModelConditionInfo::WeaponBarrelInfo *p, const ModelConditionInfo::WeaponBarrelInfo &value)
	{
		new (p) ModelConditionInfo::WeaponBarrelInfo(value);
	}
}

// STLport map<NameKeyType, PristineBoneInfo> node: value at +0x10, the matrix
// at +0x14 and the bone index at +0x44.
struct Rva00769260Node
{
	char m_pad00[0x14];
	Matrix3D m_mtx;
	Int m_boneIndex;
};

struct Rva00769260Iterator
{
	Rva00769260Node *m_node;
};

class Rva00769260Tree
{
public:
	Rva00769260Iterator find(void *const &key);
	Rva00769260Node *end() const { return m_header; }
	Rva00769260Node *m_header;
};

// The out-of-line findPristineBone body (matched at 0x00769260).
class Rva00769260Owner
{
public:
	void *lookup(void *key, int *value);
};

class Rva0076F9E0Owner
{
public:
	void validate(Rva0076F9E0Names *names) const;

private:
	enum { PRISTINE_BONES_VALID = 0x01, BARRELS_VALID = 0x08 };

	const Matrix3D *findPristineBone(NameKeyType boneName, Int *boneIndex) const
	{
		if (!(m_validStuff & PRISTINE_BONES_VALID))
		{
			if (boneIndex)
				*boneIndex = 0;
			return 0;
		}
		if (boneName == NAMEKEY_INVALID)
		{
			if (boneIndex)
				*boneIndex = 0;
			return 0;
		}
		Rva00769260Iterator it = m_pristineBones.find(reinterpret_cast<void *const &>(boneName));
		if (it.m_node != m_pristineBones.end())
		{
			if (boneIndex)
				*boneIndex = it.m_node->m_boneIndex;
			return &it.m_node->m_mtx;
		}
		else
		{
			if (boneIndex)
				*boneIndex = 0;
			return 0;
		}
	}

	char m_pad00[0x70];
	mutable Rva00769260Tree m_pristineBones;									///< +0x70
	char m_pad74[8];
	mutable _STL::vector<ModelConditionInfo::WeaponBarrelInfo> m_weaponBarrelInfoVec[WEAPONSLOT_COUNT];	///< +0x7C
	mutable unsigned char m_validStuff;											///< +0xAC
};

void Rva0076F9E0Owner::validate(Rva0076F9E0Names *names) const
{
	if (m_validStuff & BARRELS_VALID)
		return;

	if (TheBfmeGameLogic == 0 || !TheBfmeGameLogic->m_flag)
	{
		if (TheGameState == 0 || !TheGameState->m_flag)
			return;
	}

	setFPMode();

	for (int wslot = 0; wslot < WEAPONSLOT_COUNT; ++wslot)
	{
		m_weaponBarrelInfoVec[wslot].clear();

		const Rva0076F9E0AsciiString &fxBoneName = names->m_weaponFireFXBoneName[wslot];
		const Rva0076F9E0AsciiString &recoilBoneName = names->m_weaponRecoilBoneName[wslot];
		const Rva0076F9E0AsciiString &mfName = names->m_weaponMuzzleFlashName[wslot];
		const Rva0076F9E0AsciiString &plbName = names->m_weaponProjectileLaunchBoneName[wslot];

		if (!fxBoneName.isEmpty() || !plbName.isEmpty())
		{
			Int prevFxBone = 0;
			char buffer[256];
			for (Int i = 1; i <= 99; ++i)
			{
				ModelConditionInfo::WeaponBarrelInfo info;
				info.m_projectileOffsetMtx.Make_Identity();

				if (!recoilBoneName.isEmpty())
				{
					sprintf(buffer, "%s%02d", recoilBoneName.str(), i);
					findPristineBone(NAMEKEY(buffer), &info.m_recoilBone);
				}
				if (!mfName.isEmpty())
				{
					sprintf(buffer, "%s%02d", mfName.str(), i);
					findPristineBone(NAMEKEY(buffer), &info.m_muzzleFlashBone);
				}
				if (!fxBoneName.isEmpty())
				{
					sprintf(buffer, "%s%02d", fxBoneName.str(), i);
					findPristineBone(NAMEKEY(buffer), &info.m_fxBone);
					if (info.m_fxBone == 0 && info.m_muzzleFlashBone != 0)
						info.m_fxBone = prevFxBone;
				}

				Int plbBoneIndex = 0;
				if (!plbName.isEmpty())
				{
					sprintf(buffer, "%s%02d", plbName.str(), i);
					const Matrix3D *mtx = findPristineBone(NAMEKEY(buffer), &plbBoneIndex);
					if (mtx != 0)
						info.m_projectileOffsetMtx = *mtx;
				}

				if (info.m_fxBone == 0 && info.m_recoilBone == 0 && info.m_muzzleFlashBone == 0 && plbBoneIndex == 0)
					break;

				m_weaponBarrelInfoVec[wslot].push_back(info);

				if (info.m_recoilBone != 0 || info.m_muzzleFlashBone != 0)
					names->m_hasRecoilBonesOrMuzzleFlashes[wslot] = true;

				prevFxBone = info.m_fxBone;
			}

			if (m_weaponBarrelInfoVec[wslot].empty())
			{
				ModelConditionInfo::WeaponBarrelInfo info;

				const Matrix3D *plbMtx = plbName.isEmpty() ? 0 : findPristineBone(NAMEKEY(plbName), 0);
				if (plbMtx != 0)
					info.m_projectileOffsetMtx = *plbMtx;
				else
					info.m_projectileOffsetMtx.Make_Identity();

				if (!fxBoneName.isEmpty())
					reinterpret_cast<Rva00769260Owner *>(const_cast<Rva0076F9E0Owner *>(this))->lookup(
						reinterpret_cast<void *>(NAMEKEY(fxBoneName)), &info.m_fxBone);

				if (info.m_fxBone != 0 || plbMtx != 0)
					m_weaponBarrelInfoVec[wslot].push_back(info);
			}
		}
	}
	m_validStuff |= BARRELS_VALID;
}
