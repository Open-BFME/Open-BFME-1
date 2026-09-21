// ?bfmeGetPercentReady0026AAC0@SpecialPowerModule@@UBEMXZ
// partial score=0.74 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail 0x0026AAC0 (195B).
//
// ICF-shared getPercentReady()-slot override (vtable slot 2, +0x08 -- the
// same slot the landed SpecialPowerModule_getPercentReady_Thunk.cpp / isReady
// / getReadyFrame siblings use): tools/vtable_lookup.py --target 0x0026AAC0
// lists five distinct installed vtables all landing on this one body at
// slot+0x8, so it cannot be attributed to a single derived class name.
// Reached through the SAME subobject adjustor as the landed isReady
// (0x0026AA20) and getReadyFrame (0x0026ABC0) siblings: object at this-0x1c,
// module data at this-0x20 (not the this-0xc/this-8 pair the primary
// SpecialPowerModule::getPercentReady override at 0x00268A90 uses -- MSVC
// does not bake the same adjustor into every override of the same
// interface). Unlike that primary override, this one has no BFME
// m_bfmeForcedZero gate: it is the plain isReady/pausedPercent/template-null
// /shortcut-power/reload-time formula only. getReloadTime() is the trivial
// getFO()->m_reloadTime inline accessor (SpecialPower.h line 117), and the
// override-chain resolution reuses the exact two-level-unroll-then-recurse
// shape already proven byte-exact in SpecialPowerModule_getReadyFrame_Thunk.cpp.

class Overridable
{
public:
	Overridable *friend_getFinalOverride(void)
	{
		if (m_next)
			return m_next->m_next ? m_next->m_next->friend_getFinalOverride() : m_next;
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	bool isShortcutPower(void) const;			///< pinned at 0x00268920
	unsigned int getReloadTime(void) const
	{
		SpecialPowerTemplate *self = const_cast<SpecialPowerTemplate *>(this);
		return ((const SpecialPowerTemplate *)self->friend_getFinalOverride())->m_reloadTime;
	}

private:
	unsigned char m_unreconstructed_08[0x18 - 0x08];
	unsigned int m_reloadTime;					// +0x18
};

class Player
{
public:
	unsigned int getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *);
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) const { return m_frame; }

private:
	char m_pad[0x3c];
	unsigned int m_frame;						// +0x3c
};

extern GameLogic *TheGameLogic;

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

class SpecialPowerModuleData
{
public:
	char m_pad[8];
	SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08
};

// This override runs on the SpecialPowerModuleInterface subobject, same as
// the landed isReady/getReadyFrame siblings: object at this-0x1c, module
// data at this-0x20. The filler virtuals below exist only to hold their
// vtable slots open (isReady at +0x4, getSpecialPowerTemplate at +0x18);
// nothing in this TU calls or defines them beyond that.
class SpecialPowerModule
{
public:
	virtual void unused00(void) const;
	virtual bool isReady(void) const;
	virtual float bfmeGetPercentReady0026AAC0(void) const;	// retail slot 2 (+0x08), this override
	virtual void unused03(void) const;
	virtual void unused04(void) const;
	virtual void unused05(void) const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;	// retail slot 6 (+0x18)

private:
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return *(const SpecialPowerModuleData *const *)((const char *)this - 0x20);
	}

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this - 0x1c);
	}

	unsigned int m_availableOnFrame;			// +0x04
	int m_pausedCount;							// +0x08
	unsigned int m_pausedOnFrame;				// +0x0c
	float m_pausedPercent;						// +0x10
};

float SpecialPowerModule::bfmeGetPercentReady0026AAC0() const
{
	if (isReady())
		return g_bfmeDefaultBU;

	if (m_pausedCount > 0)
		return m_pausedPercent;

	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();
	if (modData->m_specialPowerTemplate == 0)
		return BfmeZeroRange;

	unsigned int readyFrame = m_availableOnFrame;

	Object *obj = getObject();
	if (obj)
	{
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			if (modData->m_specialPowerTemplate->isShortcutPower())
				readyFrame = player->getOrStartSpecialPowerReadyFrame(getSpecialPowerTemplate());
		}
	}

	float percent = g_bfmeDefaultBU - ((readyFrame - TheGameLogic->getFrame()) / (float)modData->m_specialPowerTemplate->getReloadTime());

	return percent;
}
