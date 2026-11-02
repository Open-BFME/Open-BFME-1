// cl: /O2 /DNDEBUG /MD

class BfmeHeldC680
{
public:
	virtual void bfmeAddRefC680(void) = 0;
	virtual void bfmeReleaseC680(void) = 0;
	virtual void bfmeSpare002C680(void) = 0;
	virtual void bfmeSpare003C680(void) = 0;
	virtual void bfmeSpare004C680(void) = 0;
	virtual unsigned char bfmeIsUniqueC680(void) = 0;
};

struct BfmeSlotC680
{
	void *m_bfmeHead;
	void *m_bfmeHeld;
};

class AptNativeHash
{
public:
	void SetAt(int index, BfmeHeldC680 *obj);

private:
	int m_bfmeHead;
	BfmeSlotC680 *m_bfmeSlots;
};

// Apt name lookup 0x0089C290 (929 B with its jump tables). Open BFME 2
// donor (59e3f8f8) Code/Libraries/Source/Apt/AptValue.cpp names the same body
// AptValue::findChild; the BFME 1 ledger keeps the reloc-derived caller name.
// The keyword switch, _level atoi(+6) and prototype walk follow the donor.
extern "C" int __cdecl atoi(const char *);

struct R4Word
{
	const char *name;
	int value;
};
const R4Word *Rva00897FD0(const char *str, unsigned int len);

class BfmeNestedBE;
BfmeNestedBE *Rva008930C0AptLookup(int level);

class Gen_008C41D0
{
public:
	int bfmeValue() const;
};

class BfmeNode1220;

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class Rva00899C20Node
{
public:
	int rva00899C20();
};

class AptScope1220 : public BfmeTab1024
{
public:
	BfmeNode1220 *proto() const { return (BfmeNode1220 *)(m_link & ~1u); }

	void *m_vtable;
	unsigned int m_word04;
	unsigned int m_link;
};

struct Rva00899C20Registry
{
	char m_pad00[8];
	AptScope1220 m_table;
};
struct BfmeMap1024
{
	char m_pad00[8];
	AptScope1220 m_table;
};
extern Rva00899C20Registry *g_Va013387D8;
extern BfmeMap1024 *g_bfmeMap1024;

struct AptStringHeader
{
	unsigned short refs;
	unsigned short len;
	unsigned short capacity;
	unsigned short flags;
	char text[1];
};

class BfmeNode1220
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual AptScope1220 *scope();

	int bfmeTest1220(int *name, int context);

	__forceinline int type() const { return m_flags04 & 0x3f; }
	__forceinline bool isUndefined() const { return !m_bits.m_defined; }
	__forceinline bool isCIH() const { return type() >= 12 && type() <= 19 && !isUndefined(); }
	__forceinline bool isObject() const { return type() == 0x1b && !isUndefined(); }
	__forceinline bool isPrototype() const { unsigned int f = *(volatile unsigned int *)&m_flags04; return ((f & 0x3f) & 0xff) == 0x1c && !((unsigned char)(~(f >> 15)) & 1); }

	union
	{
		unsigned int m_flags04;
		struct
		{
			unsigned int m_kind : 6;
			unsigned int m_bits06 : 9;
			unsigned int m_defined : 1;
		} m_bits;
	};
	unsigned char m_pad08[0x14];
	unsigned int m_flags1c;
	unsigned char m_pad20[0x2c];
	BfmeNode1220 *m_parent4c;
};

struct AptValueStack
{
	int m_count;
	int m_capacity;
	BfmeNode1220 **m_items;
	BfmeNode1220 *top() const { return m_items[m_count - 1]; }
};
extern AptValueStack g_Va01338760;
extern AptValueStack g_Va01338778;

class BfmeThingVDW;
class Rva89A540Derived;
class Rva89A2C0Derived;
class Rva008A9B00;
class Rva89AA20Derived;
class Rva00898D60Target;
class AptValue;
extern BfmeThingVDW *g_Va013379FC;
extern Rva89A540Derived *g_Va013379AC;
extern Rva89A2C0Derived *g_Va013379B4;
extern Rva008A9B00 *g_Va013379F0;
extern Rva89AA20Derived *g_Va01337A00;
extern Rva00898D60Target *g_Rva01337A20;
extern AptValue *g_bfmeFallbackDB;

static inline bool FindChildInherits(BfmeNode1220 *value, BfmeNode1220 *proto)
{
	AptScope1220 *hash = value->scope();
	BfmeNode1220 *prototype;
	while (hash && (prototype = hash->proto()))
	{
		if (prototype == proto)
			return true;
		hash = prototype->scope();
	}
	return false;
}

static __forceinline BfmeNode1220 *FindChildThis(BfmeNode1220 *self)
{
	BfmeNode1220 *context = g_Va01338778.top();
	if (context == self)
		return self;
	if (g_Va01338760.m_count > 0 && !g_Va01338760.top()->isUndefined())
	{
		BfmeNode1220 *with = g_Va01338760.top();
		if (context == with)
			return context;
		AptScope1220 *hash = with->scope();
		BfmeNode1220 *prototype;
		while (hash && (prototype = hash->proto()))
		{
			if (prototype == context)
				return with;
			hash = prototype->scope();
		}
	}
	if (FindChildInherits(self, context))
		return self;
	return g_Va01338778.top();
}

int BfmeNode1220::bfmeTest1220(int *name, int contextArg)
{
	BfmeNode1220 *context = (BfmeNode1220 *)contextArg;
	if (!context)
		context = this;
	AptStringHeader *header = *(AptStringHeader **)name;
	const R4Word *word = Rva00897FD0(header->text, header->len);
	if (word)
	{
		switch (word->value)
		{
		case 2: return (int)FindChildThis(this);
		case 3:
		{
			if (!context->isCIH())
				return 0;
			BfmeNode1220 *root = context;
			while (root->m_parent4c)
				root = root->m_parent4c;
			return (int)root;
		}
		case 19: return (int)g_Va013387D8;
		case 4: return (int)g_Va013379FC;
		case 20: return (int)g_Va013379AC;
		case 5: return (int)g_Va013379B4;
		case 36: return (int)g_Va013379F0;
		case 37: return (int)g_Va01337A00;
		case 17: return (int)g_Rva01337A20;
		case 18:
		{
			context = g_Va01338778.top();
			AptScope1220 *hash = context->scope();
			BfmeNode1220 *prototype;
			if (hash && (prototype = hash->proto()))
			{
				if (context != this && ((Rva00899C20Node *)context)->rva00899C20() && !context->isCIH())
				{
					if (context->isObject() && (context->m_flags1c & 0x200))
					{
						hash = prototype->scope();
						if (!hash)
							return (int)prototype;
						prototype = hash->proto();
					}
				}
				else if (!context->isPrototype())
				{
					hash = prototype->scope();
					if (hash && hash->proto())
						return (int)hash->proto();
					return (int)g_bfmeFallbackDB;
				}
				return (int)prototype;
			}
			return (int)g_bfmeFallbackDB;
		}
		case 16:
			if (context->isCIH())
				return (int)context->m_parent4c;
			return 0;
		default:
		undefined:
			return 0;
		case 1:
			return 0;
		case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
		case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
		case 31: case 32: case 33: case 34: case 35:
			return (int)Rva008930C0AptLookup(atoi(header->text + 6));
		}
	}
	if (context->isUndefined())
		goto undefined;
	AptScope1220 *hash = context->scope();
	if (!hash && context->isCIH() && context->type() == 0xe)
		hash = (AptScope1220 *)((Gen_008C41D0 *)context->m_parent4c)->bfmeValue();
	while (hash)
	{
		int value = hash->bfmeFind1024((int)name);
		if (value)
			return value;
		BfmeNode1220 *prototype = hash->proto();
		if (!prototype)
			break;
		hash = prototype->scope();
	}
	int value = g_bfmeMap1024->m_table.bfmeFind1024((int)name);
	if (value)
		return value;
	return g_Va013387D8->m_table.bfmeFind1024((int)name);
}

void AptNativeHash::SetAt(int index, BfmeHeldC680 *obj)
{
	BfmeHeldC680 *old = (BfmeHeldC680 *)((unsigned)m_bfmeSlots[index].m_bfmeHeld & ~1u);
	obj->bfmeAddRefC680();
	if (old)
		old->bfmeReleaseC680();
	if (obj->bfmeIsUniqueC680() == 1)
		m_bfmeSlots[index].m_bfmeHeld = (void *)((unsigned)obj | 1);
	else
		m_bfmeSlots[index].m_bfmeHeld = obj;
}
