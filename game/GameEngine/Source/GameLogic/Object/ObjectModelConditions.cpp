// cl: /DNDEBUG /MD /EHsc

// The four Object bodies that drive model conditions:
//
//   notifyModelConditionChanged    0x001BE1C0  push the current flags at the Drawable
//   replaceModelConditionFlags     0x001C4830  swap the whole mask, notify on change
//   setFiringConditionForCurrentWeapon 0x001CC820  set the firing bit for the current slot
//
// They sat in separate files, and the three disagreed about how wide
// ModelConditionFlags is: 0x24 bytes, `UnsignedInt m_bits[10]`, and
// `BitFlags<320>`.  Retail says 40 bytes, three separate ways:
//
//   replaceModelConditionFlags copies it with `rep movsd` at ecx = 0x0A, twice
//   setFiringConditionForCurrentWeapon reserves 0x28 bytes for one returned by value
//   the static clear-mask table it indexes has a 40-byte stride (esi*5, then *8)
//
// So the 0x24 in notifyModelConditionChanged was a guess -- that body only takes
// the field's address and never copies it, so nothing in it could have said
// otherwise -- and it pushed everything after +0x110 four bytes too early.  One
// 40-byte declaration here, and the members after it are placed from their own
// evidence rather than from the end of a pad.
//
// The 40 bytes still go under two decorated spellings, and both are load-bearing,
// so both stay:
//
//   VModelConditionFlags@@   the != body (0x00035CA1) and Drawable's
//                            replaceModelConditionState (0x0001343F); it is also
//                            inside replaceModelConditionFlags' OWN row name
//   V?$BitFlags@$0BEA@@      WeaponSet::getModelConditionForWeaponSlot
//                            (0x0004ADC7) and Object::clearAndSetModelConditionFlags
//                            (0x000095ED)
//
// Folding them into one type by deriving ModelConditionFlags from BitFlags<320>
// was tried and rejected on the bytes: the derivation makes ModelConditionFlags
// non-POD, and setFiringConditionForCurrentWeapon then builds the returned mask in
// a temporary and copies it (`sub esp,0x50` and a second rep movsd) where retail
// builds it in place (`sub esp,0x28`).  So the two spellings are declared side by
// side, both 40 bytes, and this comment is what ties them together.
//
// Drawable::replaceModelConditionState was itself spelled two ways -- (flags,
// UnsignedInt, UnsignedInt) in one file and (flags, Bool, UnsignedInt) in the
// other.  targets/game/reverse/symbols.csv pins both, and the Bool spelling is the one on the
// ILT at 0x0001343F that both bodies actually call, so that is the one kept.
//
// The Object layout the four settle between them:
//
//   +0x080  m_drawable
//   +0x110  m_modelConditionFlags (40 bytes, so it ends at +0x138)
//   +0x204  m_ai
//   +0x27C  m_curWeaponSlot
//
// A fourth body, bfmeApplySpecialModelCondition (0x001C1FB0), was merged here
// first and then moved out to ObjectContainedByChain.cpp. Its name fits this
// file; its bytes do not. It never reads the condition flags at +0x110 -- it
// walks m_containedBy at +0x214 to the outermost object and calls a helper at
// +0x1F8 -- and it shares both of those fields, and both of their contested
// names, with Object::forceEmotion. Grouping by what a body touches put it
// there.
//
// Object::setSingleModelCondition (0x000F2150) is NOT here even though the name
// fits.  That body reserves 0x0C bytes and zeroes three dwords, so whatever it
// builds is 96 bits wide, not 320, and it is compiled with /Gy /O2 /Ob1 rather
// than this line.  One of the two is misnamed and settling that is an identity
// question, not a merge.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DrawModule.h
class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

private:
	UnsignedInt m_bits[10];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		Bool forceReplace, UnsignedInt value);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void friend_notifyStateMachineChanged(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON = 1,
	TERTIARY_WEAPON = 2,
	QUATERNARY_WEAPON = 3,
	WEAPONSLOT_COUNT = 5
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
enum WeaponSetConditionType
{
	WSF_INVALID = -1,
	WSF_NONE = 0,
	WSF_FIRING = 1,
	WSF_BETWEEN = 2,
	WSF_RELOADING = 3,
	WSF_UNUSED = 4,
	WSF_PREATTACK = 5,
	WSF_COUNT = 6
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponSet
{
public:
	static BitFlags<320> getModelConditionForWeaponSlot(
		WeaponSlotType slot, WeaponSetConditionType condition);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged(void);
	void replaceModelConditionFlags(const ModelConditionFlags &flags, Bool forceReplace);
	void setFiringConditionForCurrentWeapon() const;

	void clearAndSetModelConditionFlags(const BitFlags<320> &clear, const BitFlags<320> &set);

private:
	unsigned char m_unmodelled000[0x80];
	Drawable *m_drawable;					// +0x080
	unsigned char m_unmodelled084[0x110 - 0x84];
	ModelConditionFlags m_modelConditionFlags;		// +0x110, 40 bytes
	unsigned char m_unmodelled138[0x204 - 0x138];
	AIUpdateInterface *m_ai;				// +0x204
	unsigned char m_unmodelled208[0x27c - 0x208];
	WeaponSlotType m_curWeaponSlot;				// +0x27C
};

// The per-slot clear mask, one 40-byte entry per weapon slot, at 0x012EF648.
static const BitFlags<320> s_allWeaponFireFlags[WEAPONSLOT_COUNT] = {};

// ?notifyModelConditionChanged@Object@@QAEXXZ
//
// Two guarded calls and nothing else, guarded independently: no drawable does not
// stop the AI being told.  The AI call is virtual by its decorated name but
// reached DIRECTLY here, so it is written by qualified name; left to dispatch it
// becomes `jmp [edx]' and four bytes longer.
void Object::notifyModelConditionChanged(void)
{
	if (m_drawable)
		m_drawable->replaceModelConditionState(m_modelConditionFlags, false, 0);

	if (m_ai)
		m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
}

// ?replaceModelConditionFlags@Object@@QAEXABVModelConditionFlags@@_N@Z
//
// Snapshot all ten dwords, replace all ten, then notify the Drawable when the
// value changed or the caller explicitly forces a refresh.
void Object::replaceModelConditionFlags(const ModelConditionFlags &flags,
	Bool forceReplace)
{
	ModelConditionFlags oldFlags = m_modelConditionFlags;
	m_modelConditionFlags = flags;

	if (oldFlags != m_modelConditionFlags || forceReplace)
	{
		if (m_drawable)
		{
			m_drawable->replaceModelConditionState(m_modelConditionFlags,
				forceReplace, 0);
		}
	}
}

// ?setFiringConditionForCurrentWeapon@Object@@QBEXXZ
//
// BFME's WeaponSet returns ten dwords here, not the three-dword mask the ZH
// sources in Object.cpp use.
void Object::setFiringConditionForCurrentWeapon() const
{
	Object *self = (Object *)this;
	if (m_drawable != 0)
	{
		WeaponSlotType slot = m_curWeaponSlot;
		BitFlags<320> flags = WeaponSet::getModelConditionForWeaponSlot(slot, WSF_FIRING);
		self->clearAndSetModelConditionFlags(s_allWeaponFireFlags[slot], flags);
	}
}
