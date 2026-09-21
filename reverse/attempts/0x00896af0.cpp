// ?d_00896af0@@YAXXZ
// partial score=0.42 date=2026-09-17
// ?rva00896AF0@Rva00896AF0Tracker@@QAEXPAVRva8CD130String@@V2@@Z
//
// The owner remains address-derived.  The caller at 0x008AE70E proves the
// pointer/by-value string ABI, while the body itself proves the Apt-value
// flag filter and the shared empty-string comparison.

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolVKI *g_bfmeStringPool1284;
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	BfmeStrVKI(const BfmeStrVKI &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeHdrVKI *m_data;
};

class Rva8CD130String : public BfmeStrVKI
{
public:
	Rva8CD130String(const Rva8CD130String &other) : BfmeStrVKI(other) {}
	~Rva8CD130String() {}
};

class Rva00899770
{
};

extern void (*TheBfmeFree)(void *, unsigned int);

class BfmeRefVGO
{
public:
	BfmeRefVGO() : m_bfmeP(0) {}
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &other);

	unsigned *m_bfmeP;
};

class Rva00893030Manager
{
public:
	BfmeRefVGO &rva00895950(BfmeRefVGO *out, BfmeStrVKI *name);
	struct BfmeResultEVB bfmeBuildEVB(BfmeStrVKI *name);
};

extern Rva00893030Manager *g_rva00893030Manager;

struct BfmeResultEVB
{
	BfmeResultEVB();
	BfmeResultEVB(const BfmeResultEVB &other);
	~BfmeResultEVB();

	void *m_bfmeAEVB;
	void *m_bfmeBEVB;
	void *m_bfmeCEVB;
	void *m_bfmeDEVB;
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

	void operator delete(void *value, unsigned int bytes)
	{
		TheBfmeFree(value, bytes);
	}

	int m_refCount;
	void *m_bfmeString;
	int m_kind;
	void *m_argument;
	void *m_object;
	void *m_buffer;
};

struct BfmeRefDB
{
	int m_bfmeCount;
	char m_gap04[0x10];
	int m_bfmeKind;
};

class BfmeHolderDB
{
public:
	BfmeHolderDB() : m_bfmeRef(0) {}
	BfmeHolderDB(const BfmeHolderDB &other)
		: m_bfmeRef(other.m_bfmeRef)
	{
		if (m_bfmeRef)
			++m_bfmeRef->m_bfmeCount;
	}
	~BfmeHolderDB()
	{
		if (m_bfmeRef)
			--m_bfmeRef->m_bfmeCount;
	}

	BfmeRefDB *m_bfmeRef;
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet() const;
};

class BfmeObj4310
{
public:
	virtual void destroy();
	virtual void release();
	void bfmeCleanup(int mode);

	unsigned m_bfmeFlags;
	void *m_bfme08;
	BfmeHdrVKI *m_bfme0c;
	char m_gap10[0x4c - 0x10];
	void *m_bfme4c;
	void *m_bfme50;
	void *m_bfme54;
	void *m_bfme58;
	char m_gap5c[4];
	unsigned m_bfmeState;
};

class Rva00896AF0Provider
{
public:
	virtual void reserved0();
	virtual void reserved1();
	virtual void reserved2();
	virtual void reserved3();
	virtual void reserved4();
	virtual void reserved5();
	virtual void *getTable(void *name, void *value);

	char m_gap1c[0x50 - 0x1c];
	void *m_bfme50;
};

class BfmeNestedBE
{
public:
	BfmeNestedBE(int kind, unsigned int marker, int value);

	void *m_vtable;
	unsigned m_bfmeFlags;
	void *m_bfme08;
	BfmeHdrVKI *m_bfme0c;
	char m_gap10[0x4c - 0x10];
	void *m_bfme4c;
	void *m_bfme50;
	void *m_bfme54;
	void *m_bfme58;
	char m_gap5c[8];
};

class BfmeItemDX
{
};

extern void __cdecl bfmePush(BfmeItemDX *item);
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);

class Rva008951B0Handle
{
public:
	Rva008951B0Handle() : m_bfmeNode(0) {}
	Rva008951B0Handle(const Rva008951B0Handle &other)
		: m_bfmeNode(other.m_bfmeNode)
	{
		if (m_bfmeNode)
			++*(int *)m_bfmeNode;
	}

	void *m_bfmeNode;
};

class Rva008951B0Owner
{
public:
	Rva008951B0Handle find(void *key);
};

class BfmeNodeVMU
{
public:
	void *m_bfmePayload;
	BfmeNodeVMU *m_bfmeNext;
};

class BfmeListVMU
{
public:
	void bfmeEraseVMU(BfmeNodeVMU **it);
};

class BfmeRefBC
{
public:
	int m_bfmeRefs;
};

class Gen_00896500
{
public:
	void bfmePush(BfmeRefBC **value);
};

class Gen_00895670
{
public:
	Gen_00895670(BfmeDropObjectA *object, void *extra);
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
};

class BfmeNodeEA
{
};

extern void __cdecl bfmeUnlink(BfmeNodeEA *node);

class Rva8D0D80String
{
};

class Rva8D0D80Value
{
};

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

void *operator new(unsigned int, void *where)
{
	return where;
}

void operator delete(void *, void *)
{
}

class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

extern Rva008AE770Stack Rva008AE770TheStack;

class Rva00896AF0Tracker
{
public:
	void rva00896AF0(Rva8CD130String *input, Rva8CD130String text);
	void rva00896390(BfmeRefVGO value);
};

void Rva00896AF0Tracker::rva00896AF0(
	Rva8CD130String *input, Rva8CD130String text)
{
	Rva00899770 *created = Rva008AE770TheStack.createString(
		Rva008930C0AptLookup(0), 0, &text, 1, 1, 0);
	if (created == 0)
		return;

	unsigned flags = *(unsigned *)((char *)created + 4);
	unsigned kind = flags & 0x3f;
	if (kind < 0x0c || kind > 0x13)
		return;
	if (((unsigned char)~(flags >> 15) & 1) != 0)
		return;

	BfmeRefVGO result;
	{
		BfmeStrVKI empty((const char *)0x0107301c);
		BfmeHdrVKI *left = input->m_data;
		BfmeHdrVKI *right = empty.m_data;
		bool equal = false;
		if (left->m_length == right->m_length)
		{
			if (left == right)
				equal = true;
			else
				equal = memcmp((char *)left + 8, (char *)right + 8,
					left->m_length) == 0;
		}
		if (!equal)
		{
			BfmeRefVGO temporary;
			result.bfmeAssignVGO(
				g_rva00893030Manager->rva00895950(
					&temporary, (BfmeStrVKI *)input));
		}
	}

	if (result.m_bfmeP != 0)
		rva00896390(result);
	else
	{
		BfmeResultEVB built =
			g_rva00893030Manager->bfmeBuildEVB((BfmeStrVKI *)input);
		result.bfmeAssignVGO(*(BfmeRefVGO *)&built);
	}

	BfmeObj4310 *object = (BfmeObj4310 *)created;
	object->bfmeCleanup(1);
	void *handleNode = 0;
	if ((object->m_bfmeState & 0xc0000) == 0x40000)
	{
		Rva008951B0Handle handle =
			((Rva008951B0Owner *)this)->find(object);
		handleNode = handle.m_bfmeNode;
		if (handle.m_bfmeNode != 0)
			++*(int *)handle.m_bfmeNode;

		BfmeHolderDB holder =
			((Gen_00895650 *)handle.m_bfmeNode)->bfmeGet();
		BfmeRefDB *ref = holder.m_bfmeRef;
		if (ref != 0 && ref->m_bfmeKind != 5)
		{
			BfmeNodeVMU *node =
				(BfmeNodeVMU *)((char *)handle.m_bfmeNode);
			((BfmeListVMU *)this)->bfmeEraseVMU(&node);
			ref->m_bfmeKind = 5;
		}

		{
			void *raw = Rva008C5D70Alloc(0x6c);
			BfmeNestedBE *node =
				(BfmeNestedBE *)((char *)raw + 8);
			bfmePush((BfmeItemDX *)node);
			node = new (node) BfmeNestedBE(
				0x13, 0, (int)object->m_bfme4c);

			node->m_bfme08 = object->m_bfme08;
			++object->m_bfme0c->m_refCount;
			BfmeHdrVKI *old = node->m_bfme0c;
			if (--old->m_refCount == 0)
				g_bfmeStringPool1284->free(old);
			node->m_bfme0c = object->m_bfme0c;
			node->m_bfme54 = object->m_bfme54;
			node->m_bfme58 = object->m_bfme58;

			if (object->m_bfme4c != 0)
			{
				Rva00896AF0Provider *provider =
					(Rva00896AF0Provider *)object->m_bfme4c;
				Rva8D0D80Table *table =
					(Rva8D0D80Table *)provider->getTable(this, node);
				((Rva8D0D80Table *)table)->add(
					(Rva8D0D80String *)this, (Rva8D0D80Value *)node);
				Rva00896AF0Provider *tail =
					(Rva00896AF0Provider *)provider->m_bfme50;
				((BfmeWrapper1279 *)((char *)tail + 0x24))
					->bfmeProcess1279(object);
				object->m_bfme4c = 0;
			}
			else
			{
				bfmeUnlink((BfmeNodeEA *)object);
			}

			if (node->m_bfme54 != 0)
				((BfmeNestedBE *)node->m_bfme54)->m_bfme58 = node;
			if (node->m_bfme58 != 0)
				((BfmeNestedBE *)node->m_bfme58)->m_bfme54 = node;
			object->destroy();
		}
	}

	object->m_bfmeFlags = (object->m_bfmeFlags & 0xffffc07f) | 0x40;

	if (handleNode != 0)
	{
		if (--*(int *)handleNode == 0)
		{
			BfmeDropObjectA *value =
				*(BfmeDropObjectA **)((char *)handleNode + 4);
			if (value != 0 && --value->m_refCount == 0)
			{
				value->~BfmeDropObjectA();
				TheBfmeFree(value, 0x18);
			}
			TheBfmeFree(handleNode, 0x10);
		}
	}
}
