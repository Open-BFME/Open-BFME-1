// cl: /DNDEBUG /MD /EHsc
// readable body of ?startPowerRecharge@SpecialPowerModule@@UAEXXZ: Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp
// Open-BFME5: byte-exact clean C++ implementation of the retail recharge start.

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) const { return *(const unsigned int *)((const char *)this + 0x3c); }
};

extern GameLogic *TheGameLogic;

// The retail method runs on the SpecialPowerModule subobject.  The BFME
// module-data and Object links are immediately before that subobject, while
// the ZH header puts them at different positive offsets.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule
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
		return *(const SpecialPowerModuleData **)((const char *)this - 0x20);
	}

	Object *getObject(void) const
	{
		return *(Object **)((const char *)this - 0x1c);
	}

	virtual void startPowerRecharge(void);

private:
	unsigned int m_availableOnFrame;
};

// ?startPowerRecharge@SpecialPowerModule@@UAEXXZ
void SpecialPowerModule::startPowerRecharge(void)
{
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	if (modData->m_specialPowerTemplate == 0)
		return;

	Object *obj = getObject();
	if (!obj)
		return;

	Player *player = getObject()->getControllingPlayer();
	if (!player)
		return;

	if (modData->m_specialPowerTemplate->isSharedNSync())
	{
		player->resetOrStartSpecialPowerReadyFrame(modData->m_specialPowerTemplate);
	}
	else
	{
		m_availableOnFrame = TheGameLogic->getFrame() + getSpecialPowerTemplate()->getReloadTime();
	}
}
