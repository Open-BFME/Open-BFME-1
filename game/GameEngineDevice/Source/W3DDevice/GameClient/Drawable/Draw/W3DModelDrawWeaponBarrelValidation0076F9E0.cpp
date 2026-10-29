// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHs-c- /Iinputs/reference/shims/namekeygenerator /D_OPERATOR_NEW_DEFINED_ /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// stlport
// Retail ABI and layout: targets/game/reverse/identity_evidence/0076f9e0-visible-lookups.md

#define _STLP_NO_EXCEPTIONS 1

#include <stdio.h>
#include <vector>

typedef int Int;
typedef bool Bool;

#include "WWMath/matrix3d.h"

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

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
class GameLogic;
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic ( reinterpret_cast<Rva0075B660Logic *>( TheGameLogic ) )
extern Rva0075B660State *TheGameState;

inline Bool isValidTimeToCalcLogicStuff()
{
	return (TheBfmeGameLogic && TheBfmeGameLogic->m_flag) || (TheGameState && TheGameState->m_flag);
}

enum { WEAPONSLOT_COUNT = 4 };

// Four per-slot bone-name arrays and recoil/muzzle-flash flags in the caller's object.
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
	template<> inline __declspec(noinline) void _Construct<ModelConditionInfo::WeaponBarrelInfo, ModelConditionInfo::WeaponBarrelInfo>(ModelConditionInfo::WeaponBarrelInfo *p, const ModelConditionInfo::WeaponBarrelInfo &value)
	{
		new (p) ModelConditionInfo::WeaponBarrelInfo(value);
	}
}

// Signed key at +0x10, matrix at +0x14 and bone index at +0x44.
struct Rva00769260Node
{
	char m_pad00[4];
	Rva00769260Node *m_parent;
	Rva00769260Node *m_left;
	Rva00769260Node *m_right;
	int m_key;
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
	inline __declspec(noinline) Rva00769260Iterator find(void *const &key)
	{
		Rva00769260Node *candidate = m_header;
		Rva00769260Node *node = m_header->m_parent;
		while (node != 0)
		{
			if (node->m_key >= reinterpret_cast<int>(key))
			{
				candidate = node;
				node = node->m_left;
			}
			else
				node = node->m_right;
		}
		if (candidate == m_header || reinterpret_cast<int>(key) < candidate->m_key)
			candidate = m_header;
		Rva00769260Iterator result = {candidate};
		return result;
	}
	Rva00769260Node *end() const { return m_header; }
	Rva00769260Node *m_header;
};

// Inline definition exposes the lookup's non-retaining output writes.
class Rva00769260Owner
{
public:
	inline __declspec(noinline) void *lookup(void *key, int *value)
	{
		if ((m_flags & 1) != 0 && key != 0)
		{
			Rva00769260Iterator found = m_tree.find(key);
			if (found.m_node != m_tree.m_header)
			{
				if (value != 0)
					*value = found.m_node->m_boneIndex;
				return &found.m_node->m_mtx;
			}
		}
		if (value != 0)
			*value = 0;
		return 0;
	}
private:
	char m_pad00[0x70];
	Rva00769260Tree m_tree;
	char m_pad74[0xAC - 0x74];
	unsigned char m_flags;
};

class Rva0076F9E0Owner
{
public:
	void validate(Rva0076F9E0Names *names) const;

private:
	enum { PRISTINE_BONES_VALID = 0x01, BARRELS_VALID = 0x08 };

	// ?findPristineBone@Rva0076F9E0Owner@@ABEPBVMatrix3D@@W4NameKeyType@@PAH@Z absent-from-retail
	const Matrix3D *findPristineBone(NameKeyType boneName, Int *boneIndex) const
	{
		if (!(m_validStuff & PRISTINE_BONES_VALID))
		{
			// set it to zero, some callers rely on this
			if (boneIndex)
				*boneIndex = 0;
			return 0;
		}
		if (boneName == NAMEKEY_INVALID)
		{
			// set it to zero, some callers rely on this
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
			// set it to zero -- some callers rely on this!
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

//-------------------------------------------------------------------------------------------------
// ?validate@Rva0076F9E0Owner@@QBEXPAURva0076F9E0Names@@@Z
void Rva0076F9E0Owner::validate(Rva0076F9E0Names *names) const
{
	//DEBUG_ASSERTCRASH(isValidTimeToCalcLogicStuff(), ("calling validateWeaponBarrelInfo() from in GameClient!"));
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

// a useful tool for finding missing INI entries in the weapon-bone block
// since this class has no idea which object it refers to, it must assume that the projectilelaunchbonename
// is required if the fxBoneName is specified
// this is not always true, since some weapons have no launched projectiles, hence the caveat in the assert message
//#if defined(_DEBUG) || defined(_INTERNAL)
//    if (
//          ( m_modelName.startsWith("UV") || m_modelName.startsWith("NV") || m_modelName.startsWith("AV") ||
//            m_modelName.startsWith("uv") || m_modelName.startsWith("nv") || m_modelName.startsWith("av")
//          )
//
//          && fxBoneName.isNotEmpty()
//          
//      )
//    DEBUG_ASSERTCRASH( plbName.isNotEmpty(), ("You appear to have a missing projectilelaunchbonename. \n Promptly ignore this assert if this model is used by a non-projectile-weapon-bearing unit\nModel name = %s.", m_modelName.str()) );
//#endif

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
					// special case: if we have multiple muzzleflashes, but only one fxbone, use that fxbone for everything.
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
				// try the unadorned names
				ModelConditionInfo::WeaponBarrelInfo info;

				const Matrix3D *plbMtx = plbName.isEmpty() ? 0 : findPristineBone(NAMEKEY(plbName), 0);
				if (plbMtx != 0)
					info.m_projectileOffsetMtx = *plbMtx;
				else
					info.m_projectileOffsetMtx.Make_Identity();

				if (!fxBoneName.isEmpty())
					reinterpret_cast<Rva00769260Owner *>(const_cast<Rva0076F9E0Owner *>(this))->lookup(reinterpret_cast<void *>(NAMEKEY(fxBoneName)), &info.m_fxBone);

				if (info.m_fxBone != 0 || plbMtx != 0)
					m_weaponBarrelInfoVec[wslot].push_back(info);
			}	// if empty
		}
	}
	m_validStuff |= BARRELS_VALID;
}
