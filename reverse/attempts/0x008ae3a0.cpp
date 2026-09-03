// ?bfmeVisit008AE3A0@@YAHPAUBfmeEntry008AE3A0@@H@Z
// partial score=0.65 date=2026-09-03
// Open-BFME5 conversion.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeF1034
{
public:
	int bfmeGo1034F(int key);
};

struct BfmeLookupBase008AE3A0
{
	char m_padding00[8];
	BfmeF1034 m_value;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
};

class BfmeN1034
{
public:
	int bfmeVal1034(void);
};

struct BfmeOwner008AE3A0;

struct BfmeEntry008AE3A0
{
	char m_padding00[4];
	unsigned m_kind;
	char m_padding08[0x18];
	void *m_value20;
	char m_padding24[0x2C];
	BfmeOwner008AE3A0 *m_owner;
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

extern BfmeEntry008AE3A0 **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern int g_bfmeFallbackDB;

int bfmeVisit008AE3A0(register BfmeEntry008AE3A0 *entry, volatile int count)
{
	if (count < 1)
		return g_bfmeFallbackDB;

	BfmeEntry008AE3A0 *last = g_bfmeArr1233[g_bfmeCount1233 - 1];
	unsigned flags = ((BfmeEntry008AE3A0 *)entry)->m_kind;
	unsigned kind = flags & 0x3F;
	if (kind == 0x13 && ((unsigned char)~(flags >> 15) & 1) == 0)
		return g_bfmeFallbackDB;

	unsigned lastKind = last->m_kind & 0x3F;
	int value;
	if (lastKind == 1 || lastKind == 0x2A)
	{
		if (((unsigned char)~(last->m_kind >> 15) & 1) == 0)
		{
			BfmeEntry008AE3A0 *lookupArg = last;
			if (lastKind != 1)
				lookupArg = (BfmeEntry008AE3A0 *)last->m_value20;
			value = entry->m_owner->m_lookup->m_value.bfmeGo1034F(
				(int)((char *)lookupArg + 8)) + 1;
		}
		else
			value = ((BfmeN1034 *)last)->bfmeVal1034();
	}
	else
		value = ((BfmeN1034 *)last)->bfmeVal1034();

	if (--value < 0)
		return g_bfmeFallbackDB;
	((BfmeThingCBC *)entry)->bfmeStepCBC(value);
	entry->m_owner->m_flag = count != 0;

	return g_bfmeFallbackDB;
}
