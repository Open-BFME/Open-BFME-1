// cl: /DNDEBUG /MD /EHsc

// The Apt allocator-hook pair pointer at VA 0x01337A30, and the Apt GC-root
// registry vector pointer at VA 0x01337810.  Evidence:
// build/report_0x01337A30.md, sections "0x01337A30 -- Apt operator-new/delete
// pair pointer" and "0x01337810 -- the Apt GC root registry vector".
//
// 0x01337A30 holds a POINTER to the two-slot table, not the table: RVA
// 0x0089487A initialises it to 0x01337828, the address of the global operator
// new hook, so pool->m_alloc is *(0x01337828) and pool->m_free is
// *(0x0133782C) (the global operator delete).  Only slot +4 is ever called, at
// 276 sites, e.g. RVA 0x00891B80 (`?release@Rva00891B80@@QAEXXZ`) and RVA
// 0x00891BC0.  The setter RVA 0x00891C40 and clearer RVA 0x00891C50 confirm an
// externally driven API.
//
// 0x01337810 points at a heap-allocated twelve-byte {int capacity; int count;
// void **items;} object built by `??0Gen_008A3070@@QAE@H@Z` at RVA 0x008948BC
// out of this module's bootstrap.  Every Apt value-class constructor appends
// `this` to it in the inlined form `mov esi,[0x1337810]; ebx=[esi]; ecx=esi+4;
// edi=[ecx]; cmp edi,ebx; jl <append>`, and the overflow path clears
// 0x40000000 of the new value's flag word instead of appending -- so the list
// is the GC root list.
//
// Both names are address-derived: the report found no RTTI (the vftable at
// 0x01135D68 has a null COL), no string literal, no export and no ea_evidence
// name row for this library, and it is owned by the Apt library rather than
// GameEngine (docs/naming_evidence.md).  The class spellings are the proven
// shapes already claiming these VAs in targets/game/reverse/dir32_addresses.csv,
// so referencing files need only the variable renamed.

struct BfmeStringPool3AF0
{
    void *m_alloc;
    void (__cdecl *m_free)(void *storage);
};

struct Rva00899560Pool
{
    int m_capacity, m_count;
    void **m_items;
};

BfmeStringPool3AF0 *g_rva01337A30AllocPair = 0;
Rva00899560Pool *g_rva01337810GcRoots = 0;

// Raw configuration byte at VA 0x0133781D, initially loader-zeroed.
// Bootstrap RVA 0x00894800+0x53/+0x56 copies config+0x4D here. Readers
// separately test nonzero, compare with 1, or copy bit 0 into a bitfield.
// Keep the existing address-qualified name and the full byte representation.
unsigned char flag0133781D = 0;

// The 34-byte store body below writes four independent dwords at retail
// VA 0x013377DC/0x013377E0/0x013377E4/0x013377EC. Each is initially zero;
// data_rows.csv verifies the scalar widths and initial bytes.
int g_bfme1017I = 0;
int g_013377E0 = 0;
int g_013377E4 = 0;
int g_013377EC = 0;

// Retail 0x00891AA0 consumes only the first cdecl stack argument and forwards
// it to the allocator table's second slot. The original name and formal
// parameter count are unknown: no direct or absolute reference survives.
// An unused second formal preserves the retail call/pop/ret instead of VC7.1's
// one-argument tail jump. This is an ABI-compatible codegen view, not an
// identification as a sized delete. See identity_evidence/0x00891aa0.md.
void Rva00891AA0(void *storage, unsigned int)
{
    g_rva01337A30AllocPair->m_free(storage);
}

// Retail RVA 0x00892170, 34 bytes. EA file evidence places this body in Apt.cpp;
// its original function name and the meanings of these globals are unproved.
void Rva00892170Store(int first, int second)
{
    g_bfme1017I = first;
    g_013377E0 = first;
    g_013377E4 = second;
    g_013377EC = 0;
}

struct Rva00892A00First
{
    char m_prefix[0x58];
    void *m_value;
};

struct Rva00892A00Root
{
    Rva00892A00First *m_first;
};

struct Rva00892A00Value
{
    char m_prefix[4];
    unsigned flags;
    char m_middle[0x48];
    void *m_output;
};

struct Rva00892A00Output
{
    char m_prefix[0xc];
    void *m_nested;
};

struct Rva00892A00Nested
{
    char m_prefix[0x1c];
    void *m_first;
    void *m_second;
};

// Layout stand-in for the retail singleton at 0x013377D8; the defining
// spelling is BfmePicker1284.cpp's BfmePickWorld1284 (struct -> ?PAU).
struct BfmePickWorld1284
{
    char m_prefix[0x122c];
    Rva00892A00Root *m_root;
};

extern BfmePickWorld1284 *g_bfmeHolderBU;

// ?query@Rva00892A00@@YAXPAPAX0@Z
void __cdecl Rva00892A00Query(void **firstResult, void **secondResult)
{
      BfmePickWorld1284 *holder = g_bfmeHolderBU;
      if (!holder)
          return;

      Rva00892A00Root *root = holder->m_root;
      Rva00892A00First *first = root->m_first;
      Rva00892A00Value *value = (Rva00892A00Value *)first->m_value;
      if (!value)
          goto fail;
      unsigned flags = value->flags;
      unsigned char highFlag = (unsigned char)(flags >> 15);
      if ((flags & 0x3f) != 0x12 || (((unsigned char)~highFlag) & 1) != 0)
          goto fail;

      Rva00892A00Output *output = (Rva00892A00Output *)value->m_output;
      if (firstResult)
      {
          Rva00892A00Nested *nested = (Rva00892A00Nested *)output->m_nested;
          *firstResult = nested->m_first;
      }
      if (secondResult)
      {
          Rva00892A00Nested *nested = (Rva00892A00Nested *)output->m_nested;
          *secondResult = nested->m_second;
      }
      return;

  fail:
      if (firstResult)
          *firstResult = 0;
      if (secondResult)
          *secondResult = 0;
  }

// Retail RVA 0x00894800, 524 bytes: the Apt library bootstrap.  EA file
// evidence (wb1) places it in Apt.cpp; its original name is unproved, so the
// name keeps the address.  WindowManager::init (0x0046C5F0) passes its
// Gen_004659D0 parameter block; a null block selects a default-constructed
// local.  The body installs the default sized-free hook, then allocates the
// GC-root and registry vectors, the manager, tracker, item-table and
// BfmeThingUEW singletons through each class's inline operator new (the
// allocator hook at VA 0x01337828).  Retail's five unwind states call each
// class's out-of-line sized operator delete, a `jmp [TheBfmeFree]` body at
// 0x008917F0 (Gen_008A3070, states 0 and 1), 0x00891700 (Rva008947A0Owner),
// 0x00891750 (Gen_uw_00893e70) and 0x00891690 (BfmeThingUEW); those rows
// are still generated import scaffolds, so the deletes stay declarations
// (identity_evidence/00894800-apt-bootstrap-class-deletes.md).  Class views
// are TU-local: sizes come from the allocation requests, the ctor names
// from the ledger.

typedef unsigned int size_t;

extern void *(*Rva008C5D70Alloc)(unsigned int size);
extern void (*TheBfmeFree)(void *storage, unsigned int size);
extern void (*g_bfmeFreeDWF)(void *storage);


class Gen_004659D0
{
public:
	Gen_004659D0();
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
	int m_bfmeF;
	int m_bfmeG;
	int m_bfmeH;
	int m_bfmeI;
	int m_bfmeJ;
	int m_bfmeK;
	int m_bfmeL;
	int m_bfmeM;
	int m_bfmeN;
	int m_bfmeO;
	int m_bfmeP;
	int m_bfmeQ;
	int m_bfmeR;
	int m_bfmeS;
	unsigned char m_bfmeT;
	unsigned char m_bfmeU;
};

struct BfmeRefEMI;
struct BfmeStringData3AF0
{
	unsigned short m_refs;
};
extern BfmeRefEMI *g_bfmeRefEMIa;
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern unsigned char g_bfmeDispatchEnabled1281;

class BfmeSpecXA;
class BfmePoolXA
{
public:
	void bfmeSetupXA(BfmeSpecXA *spec);
};
struct Rva008AE770Stack;
extern Rva008AE770Stack Rva008AE770TheStack;

void bfmeResetAll();
void bfmeAppend(int, int, int);
void bfmeArenaInit(unsigned int);
extern int g_bfme1017H;
void d_008bf100();
void Rva0089BBF0InitGlobals();
struct Rva008A1DF0State;
void *Rva008A1DF0(Rva008A1DF0State *, int);
void d_008a1e80();

class Gen_008A3070
{
public:
	Gen_008A3070(int capacity);
	static void *operator new(size_t size) { return Rva008C5D70Alloc(size); }
	static void operator delete(void *storage, size_t size);
private:
	int m_capacity, m_count;
	void **m_items;
};
struct Registry008C3F10;
extern Registry008C3F10 *g_registry01337814;

class Rva00893030Manager
{
public:
	Rva00893030Manager() : m_value(0) {}
	static void *operator new(size_t size) { return Rva008C5D70Alloc(size); }
private:
	int m_value;
};
extern Rva00893030Manager *g_rva00893030Manager;

class Rva008947A0Owner
{
public:
	Rva008947A0Owner();
	static void *operator new(size_t size) { return Rva008C5D70Alloc(size); }
	static void operator delete(void *storage, size_t size);
private:
	int m_fields[6];
};
class BfmeTracker4310;
extern BfmeTracker4310 *g_bfmeTracker4310;

class Rva00892640Item
{
public:
	Rva00892640Item();
	~Rva00892640Item();
private:
	int m_fields[2];
};
class Gen_uw_00893e70
{
public:
	Gen_uw_00893e70() : m_first(0), m_second(0), m_items(m_storage) {}
	static void *operator new(size_t size) { return Rva008C5D70Alloc(size); }
	static void operator delete(void *storage, size_t size);
private:
	int m_first;
	int m_second;
	Rva00892640Item *m_items;
	Rva00892640Item m_storage[2];
};
extern Gen_uw_00893e70 *g_rva013377F0;

struct BfmeThingUEWConfig;
struct BfmeThingUEW
{
	BfmeThingUEW(BfmeThingUEWConfig *config);
	static void *operator new(size_t size) { return Rva008C5D70Alloc(size); }
	static void operator delete(void *storage, size_t size);
	char m_fields[0x12b4];
};

// Retail RVA 0x00891C90, 13 bytes: the default sized-free hook the bootstrap
// stores into TheBfmeFree.  It forwards only the pointer to the free hook at
// VA 0x0133782C; the unused size formal keeps retail's call/pop/ret.
void Rva00891C90(void *storage, unsigned int)
{
	g_bfmeFreeDWF(storage);
}

void Rva00894800(Gen_004659D0 *parameters)
{
	Gen_004659D0 defaults;
	Gen_004659D0 *config = parameters ? parameters : &defaults;

	if (!g_bfmeRefEMIa)
	{
		++g_bfmeDefaultString1284.m_refs;
		g_bfmeRefEMIa = (BfmeRefEMI *)&g_bfmeDefaultString1284;
	}
	g_bfmeDispatchEnabled1281 = config->m_bfmeT;
	flag0133781D = config->m_bfmeU;
	((BfmePoolXA *)&Rva008AE770TheStack)->bfmeSetupXA((BfmeSpecXA *)config);

	if (!TheBfmeFree)
		TheBfmeFree = Rva00891C90;
	g_rva01337A30AllocPair = (BfmeStringPool3AF0 *)&Rva008C5D70Alloc;
	bfmeResetAll();

	g_rva01337810GcRoots = (Rva00899560Pool *)new Gen_008A3070(config->m_bfmeN);
	g_registry01337814 = (Registry008C3F10 *)new Gen_008A3070(config->m_bfmeS);
	((void (__cdecl *)(int))(void *)d_008bf100)(config->m_bfmeO);
	Rva0089BBF0InitGlobals();
	g_rva00893030Manager = new Rva00893030Manager;
	g_bfmeTracker4310 = (BfmeTracker4310 *)new Rva008947A0Owner;
	g_rva013377F0 = new Gen_uw_00893e70;
	BfmeThingUEW *thing = new BfmeThingUEW((BfmeThingUEWConfig *)config);
	g_bfmeHolderBU = (BfmePickWorld1284 *)thing;
	bfmeAppend((int)thing, (int)Rva008A1DF0, (int)d_008a1e80);
	bfmeArenaInit(0x800);
	g_bfme1017H = 1;
}
