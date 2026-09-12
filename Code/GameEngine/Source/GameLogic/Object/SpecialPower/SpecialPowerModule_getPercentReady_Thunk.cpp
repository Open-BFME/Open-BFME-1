// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ de-lift of the __emit MASM thunk.
//
// BFME1 diverges from the Zero Hour source here: a private flag read at
// subobject offset +0x14 forces an early zero return (there is no ZH 0.99999
// paused-at-ready path), and the isSharedNSync() gate that guards the
// shared-timer readyFrame override is replaced by isShortcutPower(). Field
// and vtable-slot positions below are read directly off the retail
// disassembly (tools/dis_retail.py 0x00268A90 210), not copied from the ZH
// header, because they differ from it: this override reaches the module
// data through this-0xc and the owning Object through this-8, not the
// this-0x20/this-0x1c pair the isReady/getReadyFrame overrides use -- MSVC
// does not bake the same adjustor into every override of the same
// interface. isShortcutPower()'s vtable slot sits one slot ahead of where
// Zero Hour's header would put getSpecialPowerTemplate, so a filler slot
// stands in for a BFME-added virtual between getPowerName and it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerTemplate
{
public:
	bool isShortcutPower(void) const;			///< pinned at 0x00268920
	unsigned int getReloadTime(void) const;	///< pinned at 0x000CD590
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;		///< retail +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) const { return *(const unsigned int *)((const char *)this + 0x3c); }
};

extern GameLogic *TheGameLogic;

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Player;
class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned int getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
//
// This override runs on the SpecialPowerModuleInterface subobject. The
// filler virtuals below exist only to hold their vtable slots open; nothing
// in this TU calls or defines them, so they need no bodies.
class SpecialPowerModule
{
public:
	virtual void unused00(void) const;					// isModuleForPower
	virtual bool isReady(void) const;					// retail slot 1 (+0x04)
	virtual float getPercentReady(void) const;			// retail slot 2 (+0x08), this override
	virtual void unused03(void) const;					// getReadyFrame
	virtual void unused04(void) const;					// getPowerName
	virtual void unused05(void) const;					// BFME-added virtual
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;	// retail slot 6 (+0x18)

private:
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return *(const SpecialPowerModuleData *const *)((const char *)this - 0xc);
	}

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this - 8);
	}

	unsigned int m_availableOnFrame;						///< +0x04
	int m_pausedCount;										///< +0x08
	unsigned int m_pausedOnFrame;							///< +0x0c
	float m_pausedPercent;									///< +0x10
	bool m_bfmeForcedZero;									///< +0x14, BFME-added; forces a zero result
};

// ?getPercentReady@SpecialPowerModule@@UBEMXZ
float SpecialPowerModule::getPercentReady() const
{
	if (m_bfmeForcedZero)
		return BfmeZeroRange;

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
