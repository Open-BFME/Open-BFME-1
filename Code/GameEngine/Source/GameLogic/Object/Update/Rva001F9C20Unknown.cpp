// Retail 0x001F9C20 is a three-slot interface method at vtable 0x010A3950.
// Slot 1 reaches this body through ILT 0x0002B2EC.
// The retail image does not name the owning class, so this source keeps the
// class and method names address-derived.

struct Rva001F9C20GameLogic
{
	unsigned char m_pad00[0x6a];
	char m_busy;
};

extern Rva001F9C20GameLogic *TheGameLogic;
extern void j_00026044(void);

struct Rva001F9C20Thing
{
	unsigned char m_pad00[0xc4];
	char m_flagC4;
};

struct Rva001F9C20Base
{
	__forceinline Rva001F9C20Thing *thing(void)
	{
		return m_thing;
	}

	__forceinline char flag(void)
	{
		return m_flag3c;
	}

	__forceinline void invoke(void)
	{
		typedef void (Rva001F9C20Base::*Method)(void);
		union
		{
			void (*raw)(void);
			Method member;
		} call;
		call.raw = j_00026044;
		(this->*call.member)();
	}

	int m_pad00;
	Rva001F9C20Thing *m_thing;
	unsigned char m_pad08[0x34];
	char m_flag3c;
};

class Rva001F9C20Unknown
{
public:
	void invoke(int unused);

private:
	unsigned char m_pad00[0x31];
	char m_flag31;
};

// ?invoke@Rva001F9C20Unknown@@QAEXH@Z
void Rva001F9C20Unknown::invoke(int unused)
{
	if (TheGameLogic->m_busy != 0)
		return;

	Rva001F9C20Base *base =
		(Rva001F9C20Base *)((char *)this - 0xc);
	if (*((char *)base + 0x3d) != 0)
		return;
	if (base->thing()->m_flagC4 != 0 || base->flag() != 0)
		base->invoke();
}
