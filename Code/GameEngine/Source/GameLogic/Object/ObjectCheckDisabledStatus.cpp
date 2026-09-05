// BFME 1.03 Object::checkDisabledStatus at RVA 0x001C5780.

enum DisabledType
{
	DISABLED_DEFAULT,
	DISABLED_HACKED,
	DISABLED_EMP,
	DISABLED_HELD,
	DISABLED_PARALYZED,
	DISABLED_UNMANNED,
	DISABLED_UNDERPOWERED,
	DISABLED_FREEFALL,
	DISABLED_SUBDUED,
	DISABLED_SCRIPT_DISABLED,
	DISABLED_SCRIPT_UNDERPOWERED,
	DISABLED_COUNT
};

class DisabledMask
{
public:
	bool test(int bit) const { return (m_bits & (1U << (bit & 31))) != 0; }
	void set(int bit, bool value)
	{
		if (value)
			m_bits |= 1U << (bit & 31);
		else
			m_bits &= ~(1U << (bit & 31));
	}

private:
	unsigned int m_bits;
};

class GameLogic
{
private:
	unsigned char m_beforeFrame[0x3C];

public:
	unsigned int m_frame;
	unsigned int getFrame(void) const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void checkDisabledStatus(void);
	bool clearDisabled(DisabledType type);
	bool isDisabledByType(DisabledType type) const
	{
		return m_disabledMask.test(type);
	}

private:
	unsigned char m_beforeDisabledMask[0x1A4];
	DisabledMask m_disabledMask;
	unsigned int m_disabledTillFrame[DISABLED_COUNT];
};

void Object::checkDisabledStatus(void)
{
	unsigned int now = TheGameLogic->getFrame();
	for (int i = 0; i < DISABLED_COUNT; ++i)
	{
		DisabledType type = (DisabledType)i;
		if (isDisabledByType(type) && now >= m_disabledTillFrame[i])
		{
			clearDisabled(type);
			m_disabledMask.set(type, false);
		}
	}
}
