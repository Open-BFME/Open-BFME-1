// ?create008BE760@BfmeSubmitter1283@@QAEXHPAXHHHHPAPAVBfmeNodeDX@@PAH@Z
// partial score=0.984 date=2026-09-28
// ?create008BE760@BfmeSubmitter1283@@QAEXHPAXHHHHPAPAVBfmeNodeDX@@PAH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008BE760, 1162 bytes (ret 0x20). Apt display-list placement: looks
// the depth/name up (bfmeQuery1279), reuses or replaces the existing character,
// allocates the per-kind record (descriptor kinds 5/4/2/10/1/8 -> node kinds
// 13/14/15/16/12/17), links the node under its parent and returns it. Only
// caller: BfmeSubmitter1283::bfmeSubmit1283 (BfmeSubmitColors1283.cpp), whose
// declaration fixes the pinned address-derived name and signature.
//
// STATUS (opus-5.5, 2026-09-28): 1162/1162 bytes, 206 differing, instruction
// shape 0.984. Residue: the frame is 0xC, not 0x8, because the second
// kind-15 string temporary gets its own slot instead of packing onto `found`
// (retail packs it there; the allocation temporaries do pack onto `previous`
// once `previous` sits in a nested block), plus small register-order
// differences. Kind 2's record stores go through the record variable (esi)
// where retail uses eax: storing through a typed temporary instead makes the
// compiler keep the descriptor in EBX and spill `this`.

typedef bool Bool;

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

extern void *(*Rva008C5D70Alloc)(unsigned int);
extern "C" void (*TheBfmeFree)(void *, unsigned int);

// EAStringC's shared data block (see game/Libraries/Source/Apt/string/EAString.cpp).
struct BfmeStringData3AF0
{
	unsigned short refCount;
	unsigned short size;
	unsigned short maxSize;
	unsigned short hash;
};

struct BfmeStringPool3AF0
{
	void *unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern BfmeStringData3AF0 g_bfmeDefaultString1284;

// Refcounted Apt string; its const char * setter is the matched 0x0089E680.
class BfmeStrVKI
{
public:
	__forceinline BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	__forceinline ~BfmeStrVKI()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->refCount == 0)
			g_bfmeStringPool1284->free(old);
	}
	__forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}
	__forceinline Bool operator==(const BfmeStrVKI &other) const
	{
		unsigned int size = m_data->size;
		return size == other.m_data->size &&
			(m_data == other.m_data || memcmp((char *)m_data + 8, (char *)other.m_data + 8, size) == 0);
	}
	void bfmeSetVKI(const char *text);

	BfmeStringData3AF0 *m_data;
};

struct Alloc008BE760
{
	static void *operator new(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }
	static void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }
};

// The per-character record every arm allocates; the fields below are the ones
// this body touches.
class Rva008BE760Record : public Alloc008BE760
{
public:
	virtual void slot0();
	int m_04;
	int m_08;
	int *m_descriptor;
};

class Gen_008AC620 : public Rva008BE760Record
{
public:
	Gen_008AC620();
	virtual ~Gen_008AC620();
	int m_10;
	int m_14;
	int m_18;
	unsigned int m_1c;
	int m_unmodelled20[4];
};

// Kind-13 record: the vptr-only derived class whose out-of-line constructor is
// ??0Rva008BD2B0@@QAE@XZ (vtable 0x01136DD0), inlined here.
class Detail008BE760 : public Gen_008AC620
{
public:
	Detail008BE760() {}
	virtual void handle();
};

class BfmeDerived1283 : public Rva008BE760Record
{
public:
	BfmeDerived1283();
	int m_10[3];
	int m_1c;
	int m_20;
};

class Rva008BE450SizedDeleting : public Rva008BE760Record
{
public:
	Rva008BE450SizedDeleting() throw();
	int m_10[2];
	BfmeStrVKI m_name;
	BfmeStrVKI m_target;
	int m_20;
	int m_24;
	int m_28[5];
	int m_3c;
	int m_40[4];
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70[2];
};

class Rva008BD2D0 : public Rva008BE760Record
{
public:
	Rva008BD2D0() throw();
	int m_10[2];
};

class Rva008BD2F0 : public Rva008BE760Record
{
public:
	Rva008BD2F0() throw();
	int m_10[2];
};

class Rva008BD310 : public Rva008BE760Record
{
public:
	Rva008BD310() throw();
	int m_10[3];
};

// The descriptor the caller passes: kind word, then the placement values.
struct Rva008BE760Descriptor
{
	int kind;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
};

class Rva8CD130Value;
class Rva008AD530StringBinding
{
public:
	void resolve(Rva8CD130Value *value);
};

class BfmeTab1024
{
public:
	void bfmeAdd1024(BfmeStrVKI *name, class BfmeNodeDX *node);
};

class BfmeNodeDX
{
public:
	virtual void retain();
	virtual void release();

	Bool isContainer() const
	{
		return ((m_flags & 63) == 13 && !((unsigned char)~(m_flags >> 15) & 1)) ||
			((m_flags & 63) == 18 && !((unsigned char)~(m_flags >> 15) & 1));
	}
	void bfmeSetState1285(int state);

	unsigned int m_flags;
	int m_key;
	BfmeStrVKI m_name;
	int m_unmodelled10[15];
	BfmeNodeDX *m_parent;
	Rva008BE760Record *m_record;
	int m_54;
	int m_58;
	int m_depth;
};

struct BfmeContainer1024
{
	int m_00[4];
	BfmeTab1024 *m_names;
	int m_14;
	int m_depth;
};

class BfmeNestedBE;
class BfmeNodeEA;
class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *key, int name, void **previous, void **found);
	BfmeNestedBE *bfmeCreate1284(void *key, int kind, int record);
	BfmeNestedBE *bfmeInsert1279(int key, BfmeNestedBE *node);
};
void bfmeUnlink(BfmeNodeEA *node);

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *node);
};

struct Rva008A5380List
{
	int m_00[3];
	BfmeNodeDX **m_items;
	int m_count;
};
extern char *Rva008A5380Holder;

class BfmeSubmitter1283
{
public:
	void create008BE760(int key, void *descriptorArg, int nameArg, int parentArg, int replace,
		int value, BfmeNodeDX **output, int *created);

	BfmeQuery1279 *m_query;
};

void BfmeSubmitter1283::create008BE760(int key, void *descriptorArg, int nameArg, int parentArg,
	int replace, int value, BfmeNodeDX **output, int *created)
{
	BfmeStrVKI *name = (BfmeStrVKI *)nameArg;
	BfmeNodeDX *parent = (BfmeNodeDX *)parentArg;
	BfmeNodeDX *node = 0;
	Bool isNew;

	{
	BfmeNodeDX *found;
	void *previous;
	m_query->bfmeQuery1279((void *)key, nameArg, &previous, (void **)&found);
	if (found)
	{
		if (replace)
			((BfmeWrapper1279 *)this)->bfmeProcess1279(found);
		else if ((unsigned char)~(found->m_flags >> 15) & 1)
		{
			if (name && *name == found->m_name)
			{
				found->m_flags |= 0x8000;
				node = found;
			}
		}
		else
		{
			node = found;
			isNew = false;
			goto done;
		}
	}
	}

	{
		Rva008BE760Record *record = 0;
		isNew = true;
		int kind = 13;
		if (((Rva008BE760Descriptor *)descriptorArg)->kind == 5)
		{
			Detail008BE760 *r = new Detail008BE760;
			r->m_18 = -1;
			r->m_1c |= 0x3000000;
			kind = 13;
			record = r;
		}
		else if (((Rva008BE760Descriptor *)descriptorArg)->kind == 4)
		{
			BfmeDerived1283 *r = new BfmeDerived1283;
			kind = 14;
			r->m_1c = 0;
			record = r;
		}
		else if (((Rva008BE760Descriptor *)descriptorArg)->kind == 2)
		{
			record = new Rva008BE450SizedDeleting;
			Rva008BE450SizedDeleting *r = (Rva008BE450SizedDeleting *)record;
			r->m_descriptor = (int *)descriptorArg;
			r->m_24 = ((Rva008BE760Descriptor *)descriptorArg)->m_20;
			r->m_60 = ((Rva008BE760Descriptor *)descriptorArg)->m_24;
			r->m_3c = ((Rva008BE760Descriptor *)descriptorArg)->m_1c;
			r->m_64 = ((Rva008BE760Descriptor *)descriptorArg)->m_18;
			r->m_5c = ((Rva008BE760Descriptor *)descriptorArg)->m_14;
			r->m_50 = ((Rva008BE760Descriptor *)descriptorArg)->m_08;
			r->m_58 = ((Rva008BE760Descriptor *)descriptorArg)->m_10;
			r->m_54 = ((Rva008BE760Descriptor *)descriptorArg)->m_0c;
			kind = 15;
		}
		else if (((Rva008BE760Descriptor *)descriptorArg)->kind == 10)
		{
			Rva008BD2D0 *r = new Rva008BD2D0;
			kind = 16;
			record = r;
		}
		else if (((Rva008BE760Descriptor *)descriptorArg)->kind == 1)
		{
			Rva008BD2F0 *r = new Rva008BD2F0;
			kind = 12;
			record = r;
		}
		else if (((Rva008BE760Descriptor *)descriptorArg)->kind == 8)
		{
			Rva008BD310 *r = new Rva008BD310;
			kind = 17;
			record = r;
		}
		if (parent->isContainer())
			record->m_08 = ((BfmeContainer1024 *)parent->m_record)->m_depth;
		else
			record->m_08 = -1;

		if (!node)
			node = (BfmeNodeDX *)m_query->bfmeCreate1284((void *)key, kind, (int)record);
		else
		{
			if (key != node->m_key)
			{
				bfmeUnlink((BfmeNodeEA *)node);
				m_query->bfmeInsert1279(key, (BfmeNestedBE *)node);
				node->release();
			}
			node->m_record = record;
		}

		if (parent->isContainer())
			node->m_depth = record->m_08;
		else
			node->m_depth = -1;

		if (kind == 13 || kind == 14)
		{
			Rva008A5380List *list = (Rva008A5380List *)Rva008A5380Holder;
			list->m_items[list->m_count] = node;
			++((Rva008A5380List *)Rva008A5380Holder)->m_count;
			node->retain();
		}
		else if (kind == 15)
		{
			Rva008BE450SizedDeleting *r = (Rva008BE450SizedDeleting *)node->m_record;
			r->m_name = BfmeStrVKI(*(const char **)((char *)r->m_descriptor + 0x34));
			r->m_target = BfmeStrVKI(*(const char **)((char *)r->m_descriptor + 0x38));
			((Rva008AD530StringBinding *)r)->resolve((Rva8CD130Value *)parent);
			r->m_6c = 6;
		}

		if (name)
		{
			node->m_name = *name;
			if (name->m_data != &g_bfmeDefaultString1284)
				((BfmeContainer1024 *)parent->m_record)->m_names->bfmeAdd1024(name, node);
		}
	}

done:
	parent->retain();
	if (node->m_parent)
		node->m_parent->release();
	node->m_parent = parent;
	node->m_record->m_descriptor = (int *)descriptorArg;
	node->m_record->m_04 = value;
	if (((Rva008BE760Descriptor *)descriptorArg)->kind == 4)
		node->bfmeSetState1285(1);
	*output = node;
	*created = isNew;
}
