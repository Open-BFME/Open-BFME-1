// cl: /DNDEBUG /MD /EHsc
// stlport
//
// RadarUpdate::update, retail 0x002A0450 -- the sibling of RadarUpdate::extendRadar
// (0x002A03E0, RadarUpdate_extendRadar.cpp) in the same dump, and the body the ZH
// twin at inputs/reference/.../GameLogic/Object/Update/RadarUpdate.cpp writes as three
// early returns plus one clearAndSet.
//
// The retail entry is the update-interface subobject at complete-object +0x10, so
// m_object sits at this-0x08 and the two fields this body touches are at this+0x10
// and this+0x14, i.e. complete +0x20 and +0x24.  Witnesses for those two slots:
// extendRadar (0x002A03E0) writes ONLY [esi+0x20] (the extend-done frame) and
// byte [esi+0x25]; the +0x24 flag is witnessed instead by the constructor
// ??0RadarUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x002A01E0, which zeroes
// +0x25, then +0x20, then +0x24 -- the same order as the ZH ctor's
// m_radarActive / m_extendDoneFrame / m_extendComplete -- so +0x24 is the
// extend-complete flag and +0x25 is the separate radar-active byte.  That is why
// this view stays a narrow interface class with signed displacements rather than
// inventing the whole module hierarchy, the same convention FireWeaponUpdate.cpp
// and GloriousChargeUpdateUpdate.cpp use.
//
// The model-condition set is a 320-bit set at Object+0x110, not a single dword:
// this body's own callee ?notifyModelConditionChanged@Object@@QAEXXZ (0x001BE1C0)
// passes `lea eax,[esi+0x110]` as the flags reference, and the landed
// Rva0018E210TurretAngleConditions.cpp / Rva0025EF90ChargeApplication.cpp model the
// same field as _STL::bitset<320> there.  Retail's +0x118 is therefore word 2 of
// that set, so the two bits this body touches -- word-2 bit 10 (cleared,
// and 0xFFFFFBFF) and word-2 bit 11 (set, or 0x800) -- are global indices
// 32*2+10 = 74 and 32*2+11 = 75.  Those VALUES come from this body's own word and
// masks; the LABELS are the ZH twin's, whose update() calls
// clearAndSetModelConditionState(MODELCONDITION_RADAR_EXTENDING,
// MODELCONDITION_RADAR_UPGRADED) at exactly this point.
//
// Object::clearAndSetModelConditionState has to be expanded AT the call for the
// bytes: the call boundary is what puts the update in a block with two
// predecessors, so VC7.1 cannot carry the guard's load or the first store into it
// and re-reads +0x118 and stores it twice.  Writing the same statements straight
// into update() instead lets the CSE through and lands 81 bytes.  /Ob2 declines to
// inline the two-test form on its own, hence __forceinline.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// Global bit indices into the 320-bit set at Object+0x110, derived from this
// body's word 2 (+0x118) and its 0x400 / 0x800 masks -- NOT from the ZH enum,
// whose ordinals differ.  The ZH twin supplies only the labels.
enum ModelConditionFlagType
{
	MODELCONDITION_RADAR_EXTENDING = 74,
	MODELCONDITION_RADAR_UPGRADED = 75
};

template <Int NUMBITS>
class BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }
	void reset(Int bit) { m_bits.reset(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;
typedef char RadarUpdateModelConditionFlagsSizeCheck[
	(sizeof(ModelConditionFlags) == 40) ? 1 : -1];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	__forceinline void clearAndSetModelConditionState(ModelConditionFlagType clr,
		ModelConditionFlagType set)
	{
		if (m_modelConditionFlags.test(clr) || !m_modelConditionFlags.test(set))
		{
			m_modelConditionFlags.reset(clr);
			m_modelConditionFlags.set(set);
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_unreconstructed000[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_bfmeHeadYO[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h
class RadarUpdate
{
public:
	virtual UpdateSleepTime update();

private:
	Object *getObject() const { return *(Object **)((char *)this - 8); }

	unsigned char m_interface004[0x10 - 4];
	UnsignedInt m_extendDoneFrame;
	Bool m_extendComplete;
};

// ?update@RadarUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RadarUpdate::update()
{
	// if no extend frame nothing to do
	if (m_extendDoneFrame == 0)
		return UPDATE_SLEEP_NONE;

	// check to see if our extension is already done
	if (m_extendComplete == true)
		return UPDATE_SLEEP_NONE;

	// see if it's time to stop the extension
	if (TheGameLogic->getFrame() > m_extendDoneFrame)
	{
		m_extendComplete = true;
		m_extendDoneFrame = 0;

		// remove the extending condition and set the extended condition
		getObject()->clearAndSetModelConditionState(MODELCONDITION_RADAR_EXTENDING,
			MODELCONDITION_RADAR_UPGRADED);
	}

	return UPDATE_SLEEP_NONE;
}
