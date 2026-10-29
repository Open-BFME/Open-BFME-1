// ?aptHelper008AE3A0@@YAPAVAptValue@@PAXHH@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x008AE3A0 (166 bytes, ret then int3 padding): the shared worker the
// Apt callbacks 0x008AE450 and 0x008AE470 call with (entry, count, flag).
// With an argument it reads the Apt stack top: an index value (types 1 and
// 0x2A resolve through the entry owner's lookup, else toInteger), steps the
// entry to that zero-based index and sets the owner's +0x1C bit 25 from flag.
// It always returns g_bfmeFallbackDB.  The name is the pinned address-derived
// one its callers use.
//
// Shape: the type tests read through getType() and isUndefined() accessors
// (retail's `mov edx,eax; shr; not; test` keeps the type in EAX) with plain
// early returns; the bank's raw flag expressions and gotos kept the flags
// dword in ESI (83-104 diffs).

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
	int getType() const { return m_flags.m_value & 63; }
	bool isUndefined() const { return ((m_flags.m_value >> 15) & 1) == 0; }
	char m_padding00[4];
	Rva008AE3A0Flags m_flags;
	char m_padding08[0x18];
	void *m_value20;
	char m_padding24[0x2C];
	BfmeOwner008AE3A0 *m_owner;
};

// 0x01338748: the Apt stack, as in Rva008C6800.cpp.  The old bank's
// g_bfmeArr1233 (0x01338750) and g_bfmeCount1233 (0x01338748) were only
// dir32 pins; both are fields of this object, read through one reference.
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
#define g_bfmeCount1233 (Rva008AE770TheStack.m_count)
#define g_bfmeArr1233 (Rva008AE770TheStack.m_rva01338750)
extern AptValue *g_bfmeFallbackDB;

AptValue *aptHelper008AE3A0(void *entry, int count, int flag)
{
	if (count < 1)
		return g_bfmeFallbackDB;
	Rva008AE770Stack &stack = Rva008AE770TheStack;
	BfmeEntry008AE3A0 *last = (BfmeEntry008AE3A0 *)stack.m_rva01338750[stack.m_count - 1];
	BfmeEntry008AE3A0 *current = (BfmeEntry008AE3A0 *)entry;
	if (current->getType() == 0x13 && !current->isUndefined())
		return g_bfmeFallbackDB;
	int type = last->getType();
	int value;
	if ((type == 1 || type == 0x2A) && !last->isUndefined())
	{
		BfmeEntry008AE3A0 *lookupArg = type == 1 ? last : (BfmeEntry008AE3A0 *)last->m_value20;
		value = current->m_owner->m_lookup->m_value.bfmeGo1034F((int)((char *)lookupArg + 8)) + 1;
	}
	else
		value = ((AptValue *)last)->toInteger();
	if (--value < 0)
		return g_bfmeFallbackDB;
	((BfmeThingCBC *)current)->bfmeStepCBC(value);
	current->m_owner->m_flag = flag != 0;
	return g_bfmeFallbackDB;
}
