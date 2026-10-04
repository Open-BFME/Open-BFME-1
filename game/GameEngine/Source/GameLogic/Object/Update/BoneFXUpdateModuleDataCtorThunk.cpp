// cl: /DNDEBUG /MD /EHsc
// BoneFXUpdateModuleData default constructor at 0x00288340 (225 B), ported
// from Zero Hour's BoneFXUpdate.cpp. Upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
//
// BFME keeps Zero Hour's member order but its DamageTypeFlags is one dword,
// so the three flag/array pairs sit at +0x08/+0x0C, +0x48C/+0x490 and
// +0x910/+0x914 (field_names.csv agrees on all six). The ZH headers'
// wider flags would move every array, hence this TU-local layout.
//
// Evidence: the one vtable store (0x010BC940) is BoneFXUpdateModuleData's:
// slot 0 routes through ILT 0x0004919D to the matched
// ??_GBoneFXUpdateModuleData@@UAEPAXI@Z at 0x00288460. Each array is built by
// `eh vector constructor iterator` (0x24-byte elements, 0x20 of them) with its
// own element ctor/dtor pair, which retail emits just ahead of this body:
// m_fxList 0x00288280/0x002882A0, m_OCL 0x002882B0/0x002882D0,
// m_particleSystem 0x002882E0/0x00288300 (via ILT 0x1E15/0x4788E,
// 0x402EB/0x7617, 0x316B0/0x271C9). Each dtor tail-jumps to AsciiString's
// release, matching the leading BoneLocInfo::boneName.

typedef int Int;
typedef bool Bool;
typedef unsigned int DamageTypeFlags;

class FXList;
class ObjectCreationList;
class ParticleSystemTemplate;

enum { BODYDAMAGETYPE_COUNT = 4 };
enum { BONE_FX_MAX_BONES = 8 };

struct BaseBoneListInfo
{
	BaseBoneListInfo();
	~BaseBoneListInfo();

	unsigned char m_locInfoAndDelays[0x1c];	// BoneLocInfo, GameClientRandomVariable, GameLogicRandomVariable
	Bool onlyOnce;
};

struct BoneFXListInfo : public BaseBoneListInfo
{
	const FXList *fx;
};

struct BoneOCLInfo : public BaseBoneListInfo
{
	const ObjectCreationList *ocl;
};

struct BoneParticleSystemInfo : public BaseBoneListInfo
{
	const ParticleSystemTemplate *particleSysTemplate;
};

class __declspec(novtable) S4Base009A1A40
{
public:
	S4Base009A1A40() {}
	virtual ~S4Base009A1A40();
private:
	Int m_moduleTagNameKey;
};

class BoneFXUpdateModuleData : public S4Base009A1A40
{
public:
	BoneFXUpdateModuleData();
	virtual ~BoneFXUpdateModuleData();

	DamageTypeFlags m_damageFXTypes;
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	DamageTypeFlags m_damageOCLTypes;
	BoneOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	DamageTypeFlags m_damageParticleTypes;
	BoneParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
};

// ??0BoneFXUpdateModuleData@@QAE@XZ
BoneFXUpdateModuleData::BoneFXUpdateModuleData()
{
	Int i, j;
	for (i = 0; i < BODYDAMAGETYPE_COUNT; ++i) {
		for (j = 0; j < BONE_FX_MAX_BONES; ++j) {
			m_fxList[i][j].fx = 0;
			m_fxList[i][j].onlyOnce = true;
			m_OCL[i][j].ocl = 0;
			m_OCL[i][j].onlyOnce = true;
			m_particleSystem[i][j].particleSysTemplate = 0;
			m_particleSystem[i][j].onlyOnce = true;
		}
	}

	// ZH: DAMAGE_TYPE_FLAGS_NONE then flip(), i.e. every damage type.
	m_damageFXTypes = 0xffffffff;
	m_damageOCLTypes = 0xffffffff;
	m_damageParticleTypes = 0xffffffff;
}
