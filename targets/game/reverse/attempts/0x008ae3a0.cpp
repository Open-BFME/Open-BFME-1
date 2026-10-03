// ?aptHelper008AE3A0@@YAPAVAptValue@@PAXHH@Z
// partial score=0.9819 date=2026-10-03
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class AptValue
{
public:
	int toInteger() const;
};

class BfmeF1034
{
public:
	int bfmeGo1034F(int key);
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
};

struct BfmeLookupBase008AE3A0
{
	char m_padding00[8];
	BfmeF1034 m_value;
};

struct BfmeOwner008AE3A0
{
	char m_padding00[0x0C];
	BfmeLookupBase008AE3A0 *m_lookup;
	char m_padding10[0x0C];
	unsigned m_unused : 25;
	unsigned m_flag : 1;
	unsigned m_rest : 6;
};

union Rva008AE3A0Flags
{
	unsigned m_value;
	struct
	{
		unsigned m_kind : 6;
		unsigned m_reserved : 9;
		unsigned m_bit15 : 1;
		unsigned m_rest : 16;
	};
};

struct BfmeEntry008AE3A0
{
	char m_padding00[4];
	Rva008AE3A0Flags m_flags;
	char m_padding08[0x18];
	void *m_value20;
	char m_padding24[0x2C];
	BfmeOwner008AE3A0 *m_owner;
};

extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern AptValue *g_bfmeFallbackDB;

AptValue *aptHelper008AE3A0(void *entry, int count, int flag)
{
	BfmeEntry008AE3A0 *last;
	int value;

	if (count < 1)
		goto fallback;

	last = (BfmeEntry008AE3A0 *)g_bfmeArr1233[g_bfmeCount1233 - 1];
	BfmeEntry008AE3A0 *current = (BfmeEntry008AE3A0 *)entry;
	unsigned flags = current->m_flags.m_value;
	unsigned kind = flags & 0x3F;
	if (kind == 0x13 && ((unsigned char)~(flags >> 15) & 1) == 0)
		goto fallback;

	if ((last->m_flags.m_value & 0x3F) == 1 ||
		(last->m_flags.m_value & 0x3F) == 0x2A)
	{
		if (((~((last->m_flags.m_value) >> 7) & 0x100)) == 0)
		{
			BfmeEntry008AE3A0 *lookupArg = last;
			if ((last->m_flags.m_value & 0x3F) != 1)
				lookupArg = (BfmeEntry008AE3A0 *)*(void **)((char *)last + 0x20);
			value = current->m_owner->m_lookup->m_value.bfmeGo1034F(
				(int)((char *)lookupArg + 8)) + 1;
		}
		else
			value = ((AptValue *)last)->toInteger();
	}
	else
		value = ((AptValue *)last)->toInteger();

	if (--value < 0)
		goto fallback;
	((BfmeThingCBC *)current)->bfmeStepCBC(value);
	current->m_owner->m_flag = flag != 0;

	fallback:
	return g_bfmeFallbackDB;
}
