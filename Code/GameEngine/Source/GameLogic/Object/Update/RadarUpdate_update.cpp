// cl: /DNDEBUG /MD /EHsc
//
// RadarUpdate::update, retail 0x002A0450 -- the sibling of RadarUpdate::extendRadar
// (0x002A03E0, RadarUpdate_extendRadar.cpp) in the same dump, and the body the ZH
// twin at reference/.../GameLogic/Object/Update/RadarUpdate.cpp writes as three
// early returns plus one clearAndSet.
//
// The retail entry is the update-interface subobject at complete-object +0x10, so
// m_object sits at this-0x08 and the two fields extendRadar writes -- the
// extend-done frame at complete +0x20 and the complete flag at +0x24 -- are at
// this+0x10 and this+0x14.  That is why this view stays a narrow interface class
// with signed displacements rather than inventing the whole module hierarchy, the
// same convention FireWeaponUpdate.cpp and GloriousChargeUpdateUpdate.cpp use.
//
// BFME keeps the model-condition set in ONE dword at Object+0x118 (extendRadar
// proves it: it ORs bit 10 there), so Object::clearAndSetModelConditionState
// collapses to a guard plus an AND and an OR.  It has to be expanded AT the call
// for the bytes: the call boundary is what puts the update in a block with two
// predecessors, so VC7.1 cannot carry the guard's load or the first store into it
// and re-reads +0x118 and stores it twice.  Writing the same statements straight
// into update() instead lets the CSE through and lands 81 bytes.  /Ob2 declines to
// inline the two-test form on its own, hence __forceinline.

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ModelConditionFlagType
{
	MODELCONDITION_RADAR_EXTENDING = 10,
	MODELCONDITION_RADAR_UPGRADED = 11
};

class ModelConditionFlags
{
public:
	Bool test(ModelConditionFlagType condition) const
	{
		return (m_bits & (1u << condition)) != 0;
	}

	void set(ModelConditionFlagType condition)
	{
		m_bits |= 1u << condition;
	}

	void clear(ModelConditionFlagType condition)
	{
		m_bits &= ~(1u << condition);
	}

private:
	UnsignedInt m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	__forceinline void clearAndSetModelConditionState(ModelConditionFlagType clr,
		ModelConditionFlagType set)
	{
		if (m_modelConditionFlags.test(clr) || !m_modelConditionFlags.test(set))
		{
			m_modelConditionFlags.clear(clr);
			m_modelConditionFlags.set(set);
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_unreconstructed000[0x118];
	ModelConditionFlags m_modelConditionFlags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h
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
