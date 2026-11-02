// ?bfmeFind1024@BfmeTab1024@@QAEHH@Z
// partial score=0.1365 date=2026-11-02
// partial score=0.2431 date=2026-10-04
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

struct Bucket1024
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

static __forceinline bool keysEqualHash(const BfmeStringData3AF0 *left, const BfmeStringData3AF0 *right, unsigned short hash)
{
    if (left == right)
        return true;
    if (left->m_unknown06 != hash)
        return false;
    return bfmeCompareVSC((const char *)(left + 1), (const char *)(right + 1)) == 0;
}

class BfmeTab1024
{
public:
    int bfmeFind1024(int key);

    __forceinline Bucket1024 *find(const BfmeKey1279 &key, unsigned short hash);

    int m_capacity;
    Bucket1024 *m_entries;
    unsigned int m_proto08;
    unsigned int m_prototype0c;
};

__forceinline Bucket1024 *BfmeTab1024::find(const BfmeKey1279 &key, unsigned short hash)
{
    int nIndex = (m_capacity - 1) & hash;
    BfmeStringData3AF0 *probe = m_entries[nIndex].m_key;
    if (!probe)
        return 0;
    if (probe != &g_bfmeDefaultString1284) {
        if (keysEqualHash(probe, key.m_data, hash))
            return &m_entries[nIndex];
    }
    int nBoundMin = nIndex - 8;
    int nBoundMax;
    if (nBoundMin < 0) {
        nBoundMin = 0;
        nBoundMax = 0x10;
        if (m_capacity <= 0x10)
            nBoundMax = m_capacity - 1;
    } else {
        nBoundMax = nIndex + 8;
        if (nBoundMax > m_capacity - 1) {
            nBoundMax = m_capacity - 1;
            nBoundMin = nBoundMax - 0x10;
            if (nBoundMin < 0)
                nBoundMin = 0;
        }
    }
    int current = nIndex, i = nBoundMax - nIndex;
    while (i--) {
        ++current;
        probe = m_entries[current].m_key;
        if (!probe)
            return 0;
        if (probe != &g_bfmeDefaultString1284) {
            if (keysEqual(probe, key.m_data))
                return &m_entries[current];
        }
    }
    current = nIndex;
    i = nIndex - nBoundMin;
    while (i--) {
        --current;
        probe = m_entries[current].m_key;
        if (!probe)
            return 0;
        if (probe != &g_bfmeDefaultString1284) {
            if (keysEqual(probe, key.m_data))
                return &m_entries[current];
        }
    }
    return 0;
}

int BfmeTab1024::bfmeFind1024(int keyArg)
{
    BfmeKey1279 &key = *(BfmeKey1279 *)keyArg;
    if (key.m_data->m_unknown06 == 0)
        ((BfmeThing929G *)&key)->bfmeInit929G();
    unsigned short hash = key.m_data->m_unknown06;
    int hashValue = hash;
    if (m_entries) {
        Bucket1024 *entry = find(key, hash);
        if (entry)
            return entry->m_value & ~1U;
    }
    if (hashValue == 0x699) {
        if (bfmeCompareVSC(key.text(), "prototype") == 0)
            return m_prototype0c & ~1U;
    } else if (hashValue == 0x6bbd) {
        if (bfmeCompareVSC(key.text(), "__proto__") == 0)
            return m_proto08 & ~1U;
    }
    return 0;
}
