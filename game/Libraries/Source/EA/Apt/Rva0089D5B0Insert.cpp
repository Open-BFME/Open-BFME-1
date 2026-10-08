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
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
int bfmeCompareVSC(const char *, const char *);

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
        bool equal = bfmeCompareVSC((const char *)(m_block + 1), (const char *)(other.m_block + 1)) == 0;
        return equal;
    }
    __forceinline void assign(const Rva8D0D80String &other)
    {
        ++other.m_block->m_refs;
        Rva8D0D80StringBlock *old = m_block;
        --old->m_refs;
        if (old->m_refs == 0) Rva01337A30ReleaseTable[1](old);
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
class Rva8D0D80Table
{
public:
    int count;
    Rva0089D5B0Entry *entries;
    void rva0089D180();
    void rva0089D5B0(const Rva8D0D80String &key, Rva8D0D80Value *value);
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
        rva0089D180();
    }
}
