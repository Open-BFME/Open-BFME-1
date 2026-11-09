// ?rva0089D5B0@Rva8D0D80Table@@QAEXABVRva8D0D80String@@PAVRva8D0D80Value@@@Z
// cl: /O2 /DNDEBUG /MD

struct Rva8D0D80StringBlock
{
    unsigned short m_refs;
    unsigned short m_field02;
    unsigned short m_field04;
    unsigned short m_hash;
};
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;
// VA 0x01337A30 is Apt.cpp's ?g_rva01337A30AllocPair@@3PAUBfmeStringPool3AF0@@A (data_rows).
struct BfmeStringPool3AF0 { void *m_alloc; void (__cdecl *m_free)(void *storage); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern "C" int __cdecl _strcmpi(const char *, const char *);

class Rva8D0D80String
{
public:
    Rva8D0D80StringBlock *m_block;
    __forceinline void initialize(const Rva8D0D80String &other)
    {
        m_block = other.m_block;
        ++m_block->m_refs;
    }
    __forceinline bool operator==(const Rva8D0D80String &other) const
    {
        if (m_block == other.m_block) return true;
        if (m_block->m_hash != other.m_block->m_hash) return false;
        bool equal = _strcmpi((const char *)(m_block + 1), (const char *)(other.m_block + 1)) == 0;
        return equal;
    }
    __forceinline void assign(const Rva8D0D80String &other)
    {
        ++other.m_block->m_refs;
        Rva8D0D80StringBlock *old = m_block;
        --old->m_refs;
        if (old->m_refs == 0) g_rva01337A30AllocPair->m_free(old);
        m_block = other.m_block;
    }
};
class Rva8D0D80Value
{
public:
    virtual void addRef();
    virtual void release();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual unsigned char slot5();
};
class BfmeHeldC680;
class BfmeHeldC6E0;
class AptNativeHash { public: void SetAt(int, BfmeHeldC680 *); };
class BfmeStoreC6E0 { public: void bfmePutC6E0(int, BfmeHeldC6E0 *); };
struct Rva0089D5B0Entry { Rva8D0D80String key; void *value; };
// Retail's resize body at 0x0089D180 is defined by the ledger as ?d_0089d180@@YAXXZ.
extern void d_0089d180();
class Rva8D0D80Table;
typedef void (Rva8D0D80Table::*Rva0089D180Call)();
template<class T> T dumpMemberCall(void (*p)()) { union { void (*plain)(); T member; } call; call.plain = p; return call.member; }
class Rva8D0D80Table
{
public:
    int count;
    Rva0089D5B0Entry *entries;
    void rva0089D5B0(const Rva8D0D80String &key, Rva8D0D80Value *value);
    void add(Rva8D0D80String *key, Rva8D0D80Value *value);
    __forceinline void hashSet(const Rva8D0D80String &key, Rva8D0D80Value *value)
    {
        {
            int empty = -1;
            int slot = (count - 1) & key.m_block->m_hash;
            if (!entries[slot].key.m_block)
            {
                entries[slot].key.initialize(key);
                value->addRef();
                void *stored = value;
                if (value->slot5() == 1) stored = (void *)((unsigned)value | 1);
                entries[slot].value = stored;
                return;
            }
            if (entries[slot].key.m_block == (void *)&g_rva012D5298Empty)
                empty = slot;
            else if (entries[slot].key == key)
            {
                ((AptNativeHash *)this)->SetAt(slot, (BfmeHeldC680 *)value);
                return;
            }
            int low = slot - 8;
            int high;
            if (low < 0)
            {
                low = 0;
                high = 16;
                if (count <= high) high = count - 1;
            }
            else
            {
                high = slot + 8;
                if (high > count - 1)
                {
                    high = count - 1;
                    low = high - 16;
                    if (low < 0) low = 0;
                }
            }
            int index = slot;
            int remaining = high - slot;
            while (remaining)
            {
                --remaining;
                ++index;
                if (!entries[index].key.m_block)
                {
                    entries[index].key.initialize(key);
                    ((BfmeStoreC6E0 *)this)->bfmePutC6E0(index, (BfmeHeldC6E0 *)value);
                    return;
                }
                if (entries[index].key.m_block == (void *)&g_rva012D5298Empty)
                {
                    if (empty != -1) empty = index;
                }
                else if (entries[index].key == key)
                {
                    ((AptNativeHash *)this)->SetAt(index, (BfmeHeldC680 *)value);
                    return;
                }
            }
            index = slot;
            remaining = slot - low;
            while (remaining)
            {
                --index;
                --remaining;
                if (!entries[index].key.m_block)
                {
                    entries[index].key.initialize(key);
                    ((BfmeStoreC6E0 *)this)->bfmePutC6E0(index, (BfmeHeldC6E0 *)value);
                    return;
                }
                if (entries[index].key.m_block == (void *)&g_rva012D5298Empty)
                {
                    if (empty != -1) empty = index;
                }
                else if (entries[index].key == key)
                {
                    ((AptNativeHash *)this)->SetAt(index, (BfmeHeldC680 *)value);
                    return;
                }
            }
            if (empty == -1)
            {
                (this->*dumpMemberCall<Rva0089D180Call>(d_0089d180))();
                rva0089D5B0(key, value);
                return;
            }
            entries[empty].key.assign(key);
            ((BfmeStoreC6E0 *)this)->bfmePutC6E0(empty, (BfmeHeldC6E0 *)value);
        }
    }
};

// ?rva0089D5B0@Rva8D0D80Table@@QAEXABVRva8D0D80String@@PAVRva8D0D80Value@@@Z
void Rva8D0D80Table::rva0089D5B0(const Rva8D0D80String &key, Rva8D0D80Value *value)
{
    for (;;)
    {
        int empty = -1;
        int slot = (count - 1) & key.m_block->m_hash;
        if (!entries[slot].key.m_block)
        {
            entries[slot].key.initialize(key);
            value->addRef();
            void *stored = value;
            if (value->slot5() == 1) stored = (void *)((unsigned)value | 1);
            entries[slot].value = stored;
            return;
        }
        if (entries[slot].key.m_block == (void *)&g_rva012D5298Empty)
            empty = slot;
        else if (entries[slot].key == key)
        {
            ((AptNativeHash *)this)->SetAt(slot, (BfmeHeldC680 *)value);
            return;
        }
        int low = slot - 8;
        int high;
        if (low < 0)
        {
            low = 0;
            high = 16;
            if (count <= high) high = count - 1;
        }
        else
        {
            high = slot + 8;
            if (high > count - 1)
            {
                high = count - 1;
                low = high - 16;
                if (low < 0) low = 0;
            }
        }
        int index = slot;
        int remaining = high - slot;
        while (remaining)
        {
            --remaining;
            ++index;
            if (!entries[index].key.m_block)
            {
                entries[index].key.initialize(key);
                ((BfmeStoreC6E0 *)this)->bfmePutC6E0(index, (BfmeHeldC6E0 *)value);
                return;
            }
            if (entries[index].key.m_block == (void *)&g_rva012D5298Empty)
            {
                if (empty != -1) empty = index;
            }
            else if (entries[index].key == key)
            {
                ((AptNativeHash *)this)->SetAt(index, (BfmeHeldC680 *)value);
                return;
            }
        }
        index = slot;
        remaining = slot - low;
        while (remaining)
        {
            --index;
            --remaining;
            if (!entries[index].key.m_block)
            {
                entries[index].key.initialize(key);
                ((BfmeStoreC6E0 *)this)->bfmePutC6E0(index, (BfmeHeldC6E0 *)value);
                return;
            }
            if (entries[index].key.m_block == (void *)&g_rva012D5298Empty)
            {
                if (empty != -1) empty = index;
            }
            else if (entries[index].key == key)
            {
                ((AptNativeHash *)this)->SetAt(index, (BfmeHeldC680 *)value);
                return;
            }
        }
        if (empty != -1)
        {
            entries[empty].key.assign(key);
            ((BfmeStoreC6E0 *)this)->bfmePutC6E0(empty, (BfmeHeldC6E0 *)value);
            return;
        }
        (this->*dumpMemberCall<Rva0089D180Call>(d_0089d180))();
    }
}

// 0x0089D890 (814 B): Open BFME 2 59e3f8f8 Code/Libraries/Source/Apt/
// AptNativeHash.cpp names this AptNativeHash::Set (its alternatename maps
// Rva8D0D80Table::add to Set). Retail inlines the table allocation and one
// HashSet copy; that copy ends with Expand + an out-of-line HashSet call where
// the out-of-line body above loops instead.
struct BfmeKey1279;
class BfmeLookup1279 { public: void bfmeErase1279(BfmeKey1279 &key); };
class BfmeTaggedItem;
class Gen_00897510 { public: void bfmeSet(BfmeTaggedItem *item); };
class Gen_008974C0 { public: void bfmeSet(BfmeTaggedItem *item); };
class BfmeThing929G { public: void bfmeInit929G(); };
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)


void Rva8D0D80Table::add(Rva8D0D80String *key, Rva8D0D80Value *value)
{
    if (!value)
    {
        ((BfmeLookup1279 *)this)->bfmeErase1279(*(BfmeKey1279 *)key);
        return;
    }
    if (key->m_block == (void *)&g_rva012D5298Empty)
        return;
    if (key->m_block->m_hash == 0)
        ((BfmeThing929G *)key)->bfmeInit929G();
    unsigned int h = key->m_block->m_hash;
    if (h == 0x699 && _strcmpi((const char *)(key->m_block + 1), "prototype") == 0)
    {
        ((Gen_00897510 *)this)->bfmeSet((BfmeTaggedItem *)value);
        return;
    }
    else if (h == 0x6bbd && _strcmpi((const char *)(key->m_block + 1), "__proto__") == 0)
    {
        ((Gen_008974C0 *)this)->bfmeSet((BfmeTaggedItem *)value);
        return;
    }
    if (!entries)
    {
        entries = (Rva0089D5B0Entry *)Rva008C5D70Alloc(count * 8);
        memset(entries, 0, count * 8);
    }
    hashSet(*key, value);
}
