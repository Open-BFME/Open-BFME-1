// ?bfmeErase1279@BfmeLookup1279@@QAEXAAUBfmeKey1279@@@Z
// partial score=0.1864 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 0089CC80 (617 B): erase one member from an Apt object's open-addressed
// member table. Rva00899800TableSet.cpp calls it as
// BfmeLookup1279::bfmeErase1279 with the member name. The table probes the
// name's hash slot, then a 16-slot window around it (forward, then back);
// keys compare by identity or by hash plus case-insensitive text. A removed
// slot keeps the shared empty string as its tombstone. Names that are not in
// the table may still be the object's two reserved links, "prototype" (hash
// 0x699) and "__proto__" (hash 0x6BBD), which live in their own slots.
// String block and pool follow Rva008AD750RefreshString.cpp.

int bfmeCompareVSC(const char *, const char *);

struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeThing929G { public: void bfmeInit929G(); };

struct BfmeKey1279
{
    const char *text() const { return (const char *)(m_data + 1); }
    BfmeStringData3AF0 *m_data;
};

class Rva0089CC80Object
{
public:
    virtual void retain();
    virtual void release();
};

static inline void releaseTagged(unsigned int tagged)
{
    ((Rva0089CC80Object *)(tagged & ~1U))->release();
}

struct Rva0089CC80Entry
{
    BfmeStringData3AF0 *m_key;
    unsigned int m_value;
};

static __forceinline bool keysEqual(const BfmeStringData3AF0 *left, const BfmeStringData3AF0 *right)
{
    if (left == right)
        return true;
    if (left->m_unknown06 != right->m_unknown06)
        return false;
    return bfmeCompareVSC((const char *)(left + 1), (const char *)(right + 1)) == 0;
}

class BfmeLookup1279
{
public:
    void bfmeErase1279(BfmeKey1279 &key);

    __forceinline Rva0089CC80Entry *find(const BfmeKey1279 &key, unsigned short hash);

    int m_capacity;
    Rva0089CC80Entry *m_entries;
    unsigned int m_proto08;
    unsigned int m_prototype0c;
};

__forceinline Rva0089CC80Entry *BfmeLookup1279::find(const BfmeKey1279 &key, unsigned short hash)
{
    if (!m_entries)
        return 0;
    int slot = (m_capacity - 1) & hash;
    BfmeStringData3AF0 *probe = m_entries[slot].m_key;
    if (!probe)
        return 0;
    if (probe != &g_bfmeDefaultString1284 && keysEqual(probe, key.m_data))
        return &m_entries[slot];

    int capacity = m_capacity;
    int low = slot - 8;
    int high;
    if (low < 0) {
        low = 0;
        high = capacity > 16 ? 16 : capacity - 1;
    } else {
        high = slot + 8;
        if (high > capacity - 1) {
            high = capacity - 1;
            low = high - 16;
            if (low < 0)
                low = 0;
        }
    }

    int index = slot;
    for (int count = high - slot; count; ) {
        --count;
        ++index;
        probe = m_entries[index].m_key;
        if (!probe)
            return 0;
        if (probe != &g_bfmeDefaultString1284 && keysEqual(probe, key.m_data))
            return &m_entries[index];
    }
    index = slot;
    for (int count = slot - low; count; ) {
        --index;
        probe = m_entries[index].m_key;
        --count;
        if (!probe)
            return 0;
        if (probe != &g_bfmeDefaultString1284 && keysEqual(probe, key.m_data))
            return &m_entries[index];
    }
    return 0;
}

// ?bfmeErase1279@BfmeLookup1279@@QAEXAAUBfmeKey1279@@@Z
void BfmeLookup1279::bfmeErase1279(BfmeKey1279 &key)
{
    if (key.m_data == &g_bfmeDefaultString1284)
        return;
    if (key.m_data->m_unknown06 == 0)
        ((BfmeThing929G *)&key)->bfmeInit929G();
    unsigned short hash = key.m_data->m_unknown06;
    int hashValue = hash;
    Rva0089CC80Entry *entry = find(key, hash);
    if (entry) {
        BfmeStringData3AF0 *old = entry->m_key;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        entry->m_key = &g_bfmeDefaultString1284;
        ++g_bfmeDefaultString1284.m_refCount;
        releaseTagged(entry->m_value);
        entry->m_value = 0;
        return;
    }
    if (hashValue == 0x699) {
        if (bfmeCompareVSC(key.text(), "prototype") == 0 && m_prototype0c) {
            releaseTagged(m_prototype0c);
            m_prototype0c = 0;
        }
    } else if (hashValue == 0x6bbd) {
        if (bfmeCompareVSC(key.text(), "__proto__") == 0 && m_proto08) {
            releaseTagged(m_proto08);
            m_proto08 = 0;
        }
    }
}
