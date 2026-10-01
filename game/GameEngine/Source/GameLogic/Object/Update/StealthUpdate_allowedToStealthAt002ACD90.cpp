// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// StealthUpdate stealth-eligibility test at a position, retail 0x002ACD90
// (693 B, ret 8).
//
// Owner: StealthUpdate. The body reads the module data at +4 (stealth level
// +0x0C, stealth speed +0x1C, innate stealth +0x51 per name_oracle) and the
// object at +8, sits between the StealthUpdate destructor (0x002ACD50) and
// calcStealthedStatusForPlayer (0x002AD150), and recurses through ILT
// 0x0001B04A on the StealthUpdate it finds with findModule("StealthUpdate").
// The matched voice translator Rva005A8A10 (CommandXlatVoice.cpp) calls it
// twice with two positions. Zero Hour's allowedToStealth(Object *) takes one
// object and has no positional tests, so the name keeps the address.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};
#define BFME_HAVE_COORD3D

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON,
	TERTIARY_WEAPON
};

class Module;
class UpgradeTemplate;

class Weapon
{
public:
	UnsignedInt getLastShotFrame() const { return m_lastShotFrame; }

private:
	unsigned char m_unmodelled00[0x2C];
	UnsignedInt m_lastShotFrame;							///< +0x2C
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

class StealthUpdate;

#define OBJECT_TU_MEMBERS \
	Bool bfmeHasActiveOrRecentlyActiveWeapon() const; \
	Real bfmeGetNonnegativePreferredLocomotorHeight() const; \
	Bool hasUpgrade(const UpgradeTemplate *upgradeT) const; \
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; } \
	const WeaponSet &getWeaponSet() const { return *(const WeaponSet *)((const char *)this + 0x264); } \
	friend class StealthUpdate; \
protected: \
	Module *findModule(NameKeyType key) const; \
public:
#include "GameLogic/Object/object.h"

// 0x001CB0C0, matched under an address-derived owner; called on the stealth
// object with 0 it returns the object whose StealthUpdate decides for it.
struct RvaC4390First;
class RvaC4390Second
{
public:
	RvaC4390First *resolve(Int value);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class TerrainLogic
{
public:
	Coord3D *queryPointAt001A62D0(const Coord3D *pos, Real radius, bool a, bool b);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva00367E30Logic
{
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_unmodelled00[0x3C];
	UnsignedInt m_frame;									///< +0x3C
};
// Retail's game-logic singleton (GameLogic *TheGameLogic, defined once in
// GameLogic.cpp).  This TU reads it through its own Rva00367E30Logic view.
class GameLogic;
extern GameLogic *TheGameLogic;
static inline Rva00367E30Logic *localTheGameLogic(void) { return (Rva00367E30Logic *)TheGameLogic; }

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType k, Int idx1);					///< 0x000C4B00 (ILT 0x00008D0F)

private:
	UnsignedInt m_bits[NUMBITS / 32];
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);			///< 0x009F2AE0

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);				///< 0x000C3DD0 (ILT 0x000382FD)
	virtual Bool allow(Object *obj);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

// Member-less root filter, vtable 0x01083B80 (Rva0025ED50ChargeTargets.cpp).
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *obj);
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, Real maxDist,
		DistanceCalculationType dc, PartitionFilter *filter);
};
extern PartitionManager *ThePartitionManager;

class StealthUpdateModuleData
{
public:
	unsigned char m_unmodelled00[0x0C];
	UnsignedInt m_stealthLevel;								///< +0x0C
	unsigned char m_unmodelled10[0x0C];
	Real m_stealthSpeed;									///< +0x1C
	unsigned char m_unmodelled20[0x31];
	Bool m_innateStealth;									///< +0x51
	unsigned char m_unmodelled52[0x12];
	_STL::vector<AsciiString> m_strings64;					///< +0x64 upgrade names
};

class StealthUpdate
{
public:
	Bool allowedToStealthAt002ACD90(const Coord3D *pos, const Coord3D *containerPos) const;

	Object *getObject() const { return m_object; }
	const StealthUpdateModuleData *getStealthUpdateModuleData() const { return m_moduleData; }

private:
	void *m_vtable;
	StealthUpdateModuleData *m_moduleData;					///< +0x04
	Object *m_object;										///< +0x08
};

enum
{
	KIND_5D = 0x5D
};

// ?allowedToStealthAt002ACD90@StealthUpdate@@QBE_NPBUCoord3D@@0@Z
Bool StealthUpdate::allowedToStealthAt002ACD90(const Coord3D *pos, const Coord3D *containerPos) const
{
	Object *self = getObject();
	UnsignedInt flags = getStealthUpdateModuleData()->m_stealthLevel;

	if (!(self->m_status[0] & 0x40000))
		return false;

	if (!getStealthUpdateModuleData()->m_innateStealth && !(self->m_status[0] & 0x8000))
		return false;

	if ((flags & 0x40) && (self->m_modelConditionFlags[6] & 0x800))
		return false;

	if ((flags & 1) && self->bfmeHasActiveOrRecentlyActiveWeapon())
		return false;

	if ((flags & 4) && (self->m_status[0] & 0x1000000))
		return false;

	UnsignedInt weaponFlags = flags & 0x38;
	if (weaponFlags && self->bfmeHasActiveOrRecentlyActiveWeapon())
	{
		if (weaponFlags == 0x38)
			return false;

		Weapon *weapon;
		UnsignedInt lastFrame = localTheGameLogic()->getFrame() - 1;

		if (flags & 8)
		{
			weapon = self->getWeaponSet().getWeaponInWeaponSlot(PRIMARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return false;
		}

		if (flags & 0x10)
		{
			weapon = self->getWeaponSet().getWeaponInWeaponSlot(SECONDARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return false;
		}

		if (flags & 0x20)
		{
			weapon = self->getWeaponSet().getWeaponInWeaponSlot(TERTIARY_WEAPON);
			if (weapon && weapon->getLastShotFrame() >= lastFrame)
				return false;
		}
	}

	if ((flags & 2) && self->bfmeGetNonnegativePreferredLocomotorHeight() > getStealthUpdateModuleData()->m_stealthSpeed)
		return false;

	if (self->m_scriptStatus & 8)
		return false;

	if (flags & 0x80)
	{
		Object *nearby = ThePartitionManager->getClosestObject(pos, 50.0f, FROM_CENTER_2D,
			Rva0025ED50RootFilter().link(&PartitionFilterAcceptByKindOf(
				KindOfMaskType(KindOfMaskType::kInit, KIND_5D), KINDOFMASK_NONE)));
		if (!nearby || nearby->isEffectivelyDead())
		{
			if (!TheTerrainLogic->queryPointAt001A62D0(pos, 50.0f, true, false))
			{
				const StealthUpdateModuleData *data = getStealthUpdateModuleData();
				if (data->m_strings64.size() == 0)
					return false;
				for (const AsciiString *it = data->m_strings64.begin(); it != data->m_strings64.end(); ++it)
				{
					if (!self->hasUpgrade(TheUpgradeCenter->findUpgrade(*it)))
						return false;
				}
			}
		}
	}

	if (flags & 0x100)
	{
		Object *container = (Object *)((RvaC4390Second *)self)->resolve(0);
		if (!container)
			return false;

		static NameKeyType key = TheNameKeyGenerator->nameToKey("StealthUpdate");
		const StealthUpdate *stealth = (const StealthUpdate *)container->findModule(key);
		if (!stealth)
			return false;

		if (!stealth->allowedToStealthAt002ACD90(containerPos, containerPos))
			return false;
	}

	return true;
}
