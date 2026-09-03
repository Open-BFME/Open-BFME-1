// cl: /DNDEBUG /MD /EHsc
// Twin of ?getReadyFrame@SpecialPowerModule@@UBEIXZ @0x0026ABC0 with the
// compact iface layout (Object at this-8) used by getPercentReady @0x00268A90
// and isReady @0x00269340.

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

// Compact SpecialPower iface: Object at -8 (primary size 0x10).
class Rva00268E90Owner
{
public:
	virtual void unused00() const; virtual void unused01() const;
	virtual void unused02() const; virtual void unused03() const;
	virtual void unused04() const; virtual void unused05() const;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate(void) const;
	virtual unsigned int getReadyFrame(void) const;

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this - 8);
	}

private:
	unsigned int m_availableOnFrame;		// +0x04
	int m_pausedCount;						// +0x08
	unsigned int m_pausedOnFrame;			// +0x0c
};

// ?getReadyFrame@Rva00268E90Owner@@UBEIXZ
unsigned int Rva00268E90Owner::getReadyFrame(void) const
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
