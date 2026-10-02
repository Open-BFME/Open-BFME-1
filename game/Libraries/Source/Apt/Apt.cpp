// cl: /DNDEBUG /MD /EHs-c-

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
