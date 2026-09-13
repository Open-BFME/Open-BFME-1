// cl: /DNDEBUG /MD /EHsc
// readable body of ?getReadyFrame@SpecialPowerModule@@UBEIXZ: Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp

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

private:
	unsigned char m_unreconstructed_08[0x10d];
	bool m_sharedNSync;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned int getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;
	bool isDisabled(void) const { return m_disabledMask != 0; }

private:
	unsigned char m_unreconstructed_00[0x1a4];
	unsigned int m_disabledMask;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unreconstructed_00[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule
{
public:
	virtual void unused00() const; virtual void unused01() const;
	virtual void unused02() const; virtual void unused03() const;
	virtual void unused04() const; virtual void unused05() const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;
	virtual unsigned int getReadyFrame(void) const;
	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this - 0x1c);
	}

private:
	unsigned int m_availableOnFrame;
	int m_pausedCount;
	unsigned int m_pausedOnFrame;
};

// ?getReadyFrame@SpecialPowerModule@@UBEIXZ
unsigned int SpecialPowerModule::getReadyFrame(void) const
{
	if (getSpecialPowerTemplate()->isSharedNSync())
	{
		const Object *object = getObject();
		if (object)
		{
			Player *player = object->getControllingPlayer();
			if (player)
				return player->getOrStartSpecialPowerReadyFrame(getSpecialPowerTemplate());
		}
	}

	if (m_pausedCount > 0 || getObject()->isDisabled())
		return m_availableOnFrame + TheGameLogic->m_frame - m_pausedOnFrame;

	return m_availableOnFrame;
}
