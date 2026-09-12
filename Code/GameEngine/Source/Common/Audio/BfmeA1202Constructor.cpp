// cl: /DNDEBUG /MD /EHsc

// Retail 0x000B0D10: BfmeA1202's default constructor.
// The vtable at 0x010818CC, the matched copy constructor at 0x000B5B10, the
// destructor at 0x000B0DF0, and BfmeThingCIA::bfmeInitCIA at 0x000B5450
// identify this body as BfmeA1202's constructor.
// This TU keeps the byte layout local so MSVC preserves the retail stores.

struct Two
{
	volatile int value;

	__forceinline void set()
	{
		value = 2;
	}
};

struct One
{
	volatile float value;

	__forceinline void set()
	{
		value = 1.0f;
	}
};

class BfmeA1202
{
public:
	BfmeA1202();

private:
	volatile int m_vft;
	volatile int m_zero;
	volatile int m_08;
	volatile int m_0c;
	volatile int m_10;
	volatile int m_14;
	volatile int m_18;
	volatile int m_1c;
	volatile int m_20;
	One m_24;
	volatile int m_28;
	volatile int m_2c;
	volatile int m_30;
	Two m_34;
	volatile int m_38;
	volatile int m_3c;
	volatile int m_40;
	volatile int m_44;
	volatile int m_48;
	volatile int m_4c;
	volatile int m_50;
	volatile int m_54;
	volatile int m_58;
	volatile int m_5c;
	volatile int m_60;
	volatile int m_64;
	volatile int m_68;
	volatile int m_6c;
	volatile int m_70;
	volatile int m_74;
	volatile int m_78;
	One m_7c;
	One m_80;
	Two m_84;
	volatile int m_88;
	volatile int m_8c;
	volatile int m_90;
	volatile int m_94;
};

BfmeA1202::BfmeA1202()
{
	m_zero = 0;
	m_vft = 0x010818CC;
	m_08 = 0;
	m_0c = 0;
	m_10 = 0x42c80000;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_28 = 0;
	m_2c = 0;
	m_30 = 0x19;
	m_34.set();
	m_38 = 0;
	m_3c = 0;
	m_24.set();
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4c = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_70 = 0;
	m_74 = 0x42c80000;
	m_78 = 0x447a0000;
	m_7c.set();
	m_80.set();
	m_84.set();
	m_88 = -1;
	m_8c = 0;
	m_90 = 0;
	m_94 = 0;
}
