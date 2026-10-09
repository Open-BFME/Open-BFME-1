// ?rva00896AF0@Rva00896AF0Tracker@@QAEXPAVRva8CD130String@@V2@@Z
// partial score=0.2728 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Partial address-derived tracker reconstruction; see its ownership evidence note.
class BfmeItemDX;

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
extern const char g_Rva0107301CEmptyString[];
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class BfmeStrVKI
{
public:
	__forceinline BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	BfmeStrVKI(const BfmeStrVKI &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	__forceinline ~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}


    __forceinline int length() const { return m_data->m_length; }
    __forceinline bool operator==(const BfmeStrVKI &other) const
    {
        BfmeHdrVKI *left = m_data;
        BfmeHdrVKI *right = other.m_data;
        int leftLength = left->m_length;
        int rightLength = right->m_length;
        bool equal;
        if (leftLength != rightLength) equal = false;
        else if (left == right) equal = true;
        else equal = memcmp((char *)left + 8, (char *)right + 8, leftLength) == 0;
        return equal;
    }
	BfmeHdrVKI *m_data;
};

class Rva8CD130String : public BfmeStrVKI
{
public:
	Rva8CD130String(const Rva8CD130String &other) : BfmeStrVKI(other) {}
	__forceinline ~Rva8CD130String() {}
};

class Rva00899770
{
};

extern void (*TheBfmeFree)(void *, unsigned int);

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

class Rva00894D90Accessor
{
public:
    static __forceinline unsigned int decrement(unsigned int *value)
    {
        unsigned int result = *value - 1;
        *value = result;
        return result;
    }
};
class Rva00894D80Accessor
{
public:
    static __forceinline unsigned int increment(unsigned int *value)
    {
        unsigned int result = *value + 1;
        *value = result;
        return result;
    }
};

class BfmeRefVGO
{
public:
    BfmeRefVGO() : m_bfmeP(0) {}
    __forceinline BfmeRefVGO(const BfmeRefVGO &other) : m_bfmeP(other.m_bfmeP)
    {
        if (m_bfmeP) Rva00894D80Accessor::increment((unsigned *)m_bfmeP);
    }
    __forceinline ~BfmeRefVGO();
    BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &other);
    BfmeDropObjectA *m_bfmeP;
};

class Rva00893030Manager
{
public:
	BfmeRefVGO rva00895950(BfmeStrVKI *name);
	struct BfmeResultEVB bfmeBuildEVB(BfmeStrVKI *name);
};

extern Rva00893030Manager *g_rva00893030Manager;

class BfmeElemCU
{
public:
    ~BfmeElemCU();
};
struct BfmeResultEVB
{
    __forceinline ~BfmeResultEVB() { ((BfmeElemCU *)this)->~BfmeElemCU(); }
    void *m_bfmeAEVB;
};




__forceinline BfmeRefVGO::~BfmeRefVGO()
{
    if (m_bfmeP)
    {
        unsigned count = Rva00894D90Accessor::decrement((unsigned *)m_bfmeP);
        if (count == 0) delete m_bfmeP;
    }
}

struct BfmeRefDB
{
	int m_bfmeCount;
	char m_gap04[4];
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
	__forceinline ~BfmeHolderDB()
    {
        if (m_bfmeRef && --m_bfmeRef->m_bfmeCount == 0)
            delete (BfmeDropObjectA *)m_bfmeRef;
    }

	BfmeRefDB *m_bfmeRef;
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet() const;
};

class Rva008C3F10Value
{
public:
    void cleanup(char);
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
	virtual void *getTable();

	char m_gap1c[0x50 - 4];
	void *m_bfme50;
};

class Rva00891650HeaderedDelete
{
public:
    static void operator delete(void *, unsigned int);
};
class BfmeNestedBE : public Rva00891650HeaderedDelete
{
public:
    BfmeNestedBE(int kind, unsigned int marker, int value);
    virtual void destroy();
    virtual void release();
    static void *operator new(unsigned int bytes)
    {
        extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
        extern void __cdecl bfmePush(class BfmeItemDX *);
        char *node = (char *)Rva008C5D70Alloc(bytes + 8) + 8;
        bfmePush((BfmeItemDX *)node);
        return node;
    }
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
    Rva008951B0Handle(const Rva008951B0Handle &other) : m_bfmeNode(other.m_bfmeNode) {}
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
    Gen_00895670(BfmeRefVGO object, void *extra);
    static void *operator new(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }
    __declspec(dllimport) static void operator delete(void *value, unsigned int bytes);
    unsigned m_zero;
    BfmeDropObjectA *m_obj;
    void *m_extra;
    char m_flag;
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

struct Rva008AE770Stack
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


class Gen_00892CA0
{
public:
    void bfmeCleanup();
};

class Rva00896AF0EntryRef
{
public:
    Rva00896AF0EntryRef(Gen_00895670 *value) : m_bfmeNode(value)
    {
        if (m_bfmeNode) ++m_bfmeNode->m_zero;
    }
    __forceinline ~Rva00896AF0EntryRef()
    {
        if (m_bfmeNode)
        {
            unsigned count = Rva00894D90Accessor::decrement((unsigned *)m_bfmeNode);
            if (count == 0)
            {
                BfmeDropObjectA *object = m_bfmeNode->m_obj;
                if (object)
                {
                    unsigned refs = Rva00894D90Accessor::decrement((unsigned *)object);
                    if (refs == 0) delete m_bfmeNode->m_obj;
                }
                TheBfmeFree(m_bfmeNode, 0x10);
            }
        }
    }
    Gen_00895670 *m_bfmeNode;
};

class BfmeSubmitter1283
{
public:
    void bfmeSubmit1283(int, int, int, int, int, int, int, float *, int, int, int, int);
};

class Rva00896AF0TailRef
{
public:
    Rva00896AF0TailRef(Gen_00895670 *value) : m_bfmeNode(value)
    {
        if (m_bfmeNode) ++m_bfmeNode->m_zero;
    }
    __forceinline ~Rva00896AF0TailRef() { ((Gen_00892CA0 *)this)->bfmeCleanup(); }
    Gen_00895670 *m_bfmeNode;
};

// ?rva00896AF0@Rva00896AF0Tracker@@QAEXPAVRva8CD130String@@V2@@Z
void Rva00896AF0Tracker::rva00896AF0(Rva8CD130String *volatile input, Rva8CD130String text)
{
    Rva00899770 *created = Rva008AE770TheStack.createString(
        Rva008930C0AptLookup(0), 0, &text, 1, 1, 0);
    {
    if (created == 0) goto done;
    unsigned flags = *(unsigned *)((char *)created + 4);
    int kind = flags & 0x3f;
    if (kind < 0x0c || kind > 0x13) goto done;
    if (((unsigned char)~(flags >> 15) & 1) != 0) goto done;
    BfmeRefVGO result;
    bool equal = *input == BfmeStrVKI(g_Rva0107301CEmptyString);
    if (!equal)
    {
        result.bfmeAssignVGO(g_rva00893030Manager->rva00895950(input));
        if (result.m_bfmeP == 0)
            result.bfmeAssignVGO(*(BfmeRefVGO *)&g_rva00893030Manager->bfmeBuildEVB(input));
        else rva00896390(result);
    }

    BfmeObj4310 *object = (BfmeObj4310 *)created;
    BfmeNestedBE *node = (BfmeNestedBE *)created;
    ((Rva008C3F10Value *)object)->cleanup(1);
    if ((object->m_bfmeState & 0xc0000) == 0x40000)
    {
        Rva008951B0Handle handle = ((Rva008951B0Owner *)this)->find(object);
        Rva00896AF0EntryRef handleNode(*(Gen_00895670 **)handle.m_bfmeNode);
        BfmeRefDB *ref = ((Gen_00895650 *)handleNode.m_bfmeNode)->bfmeGet().m_bfmeRef;
        if (ref->m_bfmeKind != 5)
        {
            ((BfmeListVMU *)this)->bfmeEraseVMU((BfmeNodeVMU **)&handle.m_bfmeNode);
            ref->m_bfmeKind = 5;
        }

        node = new BfmeNestedBE(0x13, 0, (int)object->m_bfme4c);
        node->m_bfme08 = object->m_bfme08;
        ++object->m_bfme0c->m_refCount;
        BfmeHdrVKI *old = node->m_bfme0c;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        node->m_bfme0c = object->m_bfme0c;
        node->m_bfme54 = object->m_bfme54;
        node->m_bfme58 = object->m_bfme58;
        if (object->m_bfme4c)
        {
            Rva00896AF0Provider *provider = (Rva00896AF0Provider *)object->m_bfme4c;
            ((Rva8D0D80Table *)provider->getTable())->add(
                (Rva8D0D80String *)&object->m_bfme0c, (Rva8D0D80Value *)node);
            ((BfmeWrapper1279 *)((char *)provider->m_bfme50 + 0x24))->bfmeProcess1279(object);
            if (node->m_bfme54) ((BfmeNestedBE *)node->m_bfme54)->m_bfme58 = node;
            if (node->m_bfme58) ((BfmeNestedBE *)node->m_bfme58)->m_bfme54 = node;
            object->destroy();
            provider = (Rva00896AF0Provider *)node->m_bfme4c;
            ((BfmeSubmitter1283 *)((char *)provider->m_bfme50 + 0x24))->bfmeSubmit1283(
                (int)node, (int)node->m_bfme08, 0, (int)result.m_bfmeP, (int)provider,
                1, -1, (float *)((char *)node + 0x28), (int)((char *)node + 0x10), 0, 0, 0);
            object->m_bfmeFlags |= 0x8000;
            ((BfmeObj4310 *)node->m_bfme4c)->release();
            object->m_bfme4c = 0;
        }
        else
        {
            bfmeUnlink((BfmeNodeEA *)object);
            if (node->m_bfme54) ((BfmeNestedBE *)node->m_bfme54)->m_bfme58 = node;
            if (node->m_bfme58) ((BfmeNestedBE *)node->m_bfme58)->m_bfme54 = node;
        }
        node->destroy();
        object->m_bfmeFlags = (object->m_bfmeFlags & 0xffffc07f) | 0x40;
    }

    node->m_bfmeFlags = (node->m_bfmeFlags & ~0x2c) | 0x8013;
    node->m_bfme50 = 0;
    Rva008951B0Handle existing = ((Rva008951B0Owner *)this)->find(node);
    if (existing.m_bfmeNode == 0)
    {
        if (result.m_bfmeP)
        {
            Gen_00895670 *entry = new Gen_00895670(result, node);
            Rva00896AF0TailRef held(entry);
            ((Gen_00896500 *)this)->bfmePush((BfmeRefBC **)&held.m_bfmeNode);
        }
    }
    else
    {
        ((BfmeListVMU *)this)->bfmeEraseVMU((BfmeNodeVMU **)&existing.m_bfmeNode);
        if (result.m_bfmeP)
        {
            Gen_00895670 *entry = new Gen_00895670(result, node);
            Rva00896AF0TailRef held(entry);
            ((Gen_00896500 *)this)->bfmePush((BfmeRefBC **)&held.m_bfmeNode);
        }
    }
    }
done:;
}
