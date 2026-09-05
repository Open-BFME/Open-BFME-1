// cl: /DNDEBUG /MD /EHsc
// Open-BFME: byte-exact clean C++ for the scaled special-power recharge at
// 0x00268BA0.  It is the near twin of ?startPowerRecharge@SpecialPowerModule@@UAEXXZ
// (0x0026AE00, Code/GameEngine/Source/Common/promoted__startPowerRecharge_SpecialPowerModule_UAEXXZ_0026AE00.cpp),
// with two differences: the module-data and Object links sit at -0xC/-0x8
// instead of -0x20/-0x1c, and the reload time is scaled by the owner's
// attribute modifier before it is added to the current frame.
// The owning class is not identified, so the body keeps an Rva-prefixed name.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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
	bool isSharedNSync(void) const
	{
		SpecialPowerTemplate *self = const_cast<SpecialPowerTemplate *>(this);
		return ((const SpecialPowerTemplate *)self->friend_getFinalOverride())->m_sharedNSync;
	}

	unsigned int getReloadTime(void) const;

private:
	unsigned char m_unreconstructed_08[0x10d];
	bool m_sharedNSync;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void resetOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;
	bool getAttributeModifierMultiplier(int which, float *out) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) const { return *(const unsigned int *)((const char *)this + 0x3c); }
};

extern GameLogic *TheGameLogic;

// The retail method runs on the special-power subobject; the module-data and
// Object links belong to the enclosing module and sit just before it.
class Rva00268BA0ScaledPowerRecharge
{
public:
	virtual void unused00(void) const;
	virtual void unused01(void) const;
	virtual void unused02(void) const;
	virtual void unused03(void) const;
	virtual void unused04(void) const;
	virtual void unused05(void) const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;

	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return *(const SpecialPowerModuleData **)((const char *)this - 0xc);
	}

	Object *getObject(void) const
	{
		return *(Object **)((const char *)this - 0x8);
	}

	virtual void startPowerRecharge(void);

private:
	unsigned int m_availableOnFrame;
	unsigned char m_unreconstructed_08[0xc];
	bool m_rechargePending;
};

// ?startPowerRecharge@Rva00268BA0ScaledPowerRecharge@@UAEXXZ
void Rva00268BA0ScaledPowerRecharge::startPowerRecharge(void)
{
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	if (modData->m_specialPowerTemplate == 0)
		return;

	Object *obj = getObject();
	if (!obj)
		return;

	Player *player = obj->getControllingPlayer();
	if (!player)
		return;

	if (modData->m_specialPowerTemplate->isSharedNSync())
	{
		player->resetOrStartSpecialPowerReadyFrame(modData->m_specialPowerTemplate);
	}
	else
	{
		float scalar = 1.0f;
		obj->getAttributeModifierMultiplier(11, &scalar);
		m_availableOnFrame = (int)(TheGameLogic->getFrame() + getSpecialPowerTemplate()->getReloadTime() * scalar);
	}

	m_rechargePending = false;
}
