// ?rebuild@Rva0089D180Table@@QAEXXZ
// partial score=0.2606060606 date=2026-09-22
// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0089D180..0089D4B8 inclusive: 825 bytes, then seven INT3 bytes.
// Address-derived owner. Witnessed table: capacity +0, entries +4,
// tagged special values +8/+C. Entry: string block pointer +0, value +4.
// This body doubles capacity, reinserts the live entries, swaps the storage,
// and clears/destroys the old table. No source-level semantic identity claimed.
#include <string.h>

struct Rva0089D180Block {
    unsigned short refs, field2, field4, hash;
};
extern Rva0089D180Block Rva012D5298;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
int bfmeCompareVSC(const char *, const char *);
class BfmeHeldC680;
class BfmeHeldC6E0;
class BfmeStoreC680 { public: void bfmePutC680(int, BfmeHeldC680 *); };
class BfmeStoreC6E0 { public: void bfmePutC6E0(int, BfmeHeldC6E0 *); };
class Gen0089C880 { public: void handle(); };

struct Rva0089D180Key {
    Rva0089D180Block *block;
    bool operator==(const Rva0089D180Key &other) const {
        if (block == other.block) return true;
        if (block->hash != other.block->hash) return false;
        bool equal = bfmeCompareVSC((const char *)(block + 1),
                                  (const char *)(other.block + 1)) == 0;
        return equal;
    }
    __forceinline void assign(const Rva0089D180Key &other) {
        ++other.block->refs;
        Rva0089D180Block *old = block;
        --old->refs;
        if (old->refs == 0) Rva01337A30ReleaseTable[1](old);
        block = other.block;
    }
};
struct Rva0089D180Entry { Rva0089D180Key key; unsigned value; };

// Reuse the existing destructor symbol, whose decoded layout is 16 bytes.
class Q3EhMember0089C900 {
public:
    int count;
    Rva0089D180Entry *entries;
    unsigned field8, fieldC;
    Q3EhMember0089C900(int n) : count(n), entries(0), field8(0), fieldC(0) {}
    ~Q3EhMember0089C900();
};
class Rva0089D180Table : public Q3EhMember0089C900 {
public:
    Rva0089D180Table(int n) : Q3EhMember0089C900(n) {}
    void rebuild();
    // Decoded 0089D5B0..0089D88A: thiscall, key by reference, value, ret 8.
    void rva0089D5B0(const Rva0089D180Key &, void *);
    void replace(int index, void *value) {
        ((BfmeStoreC680 *)this)->bfmePutC680(index, (BfmeHeldC680 *)value);
    }
    void store(int index, void *value) {
        ((BfmeStoreC6E0 *)this)->bfmePutC6E0(index, (BfmeHeldC6E0 *)value);
    }
    __forceinline void insert(const Rva0089D180Key &key, void *value) {
        int slot = key.block->hash & (count - 1);
        int empty = -1;
        if (!entries[slot].key.block) {
            Rva0089D180Block *data = key.block;
            entries[slot].key.block = data;
            ++data->refs;
            store(slot, value);
            return;
        }
        if (entries[slot].key.block == &Rva012D5298)
            empty = slot;
        else if (entries[slot].key == key) {
            replace(slot, value);
            return;
        }
        int low = slot - 8;
        int high;
        if (low < 0) {
            low = 0;
            high = 16;
            if (count <= high) high = count - 1;
        } else {
            high = slot + 8;
            if (high > count - 1) {
                high = count - 1;
                low = high - 16;
                if (low < 0) low = 0;
            }
        }
        int index = slot;
        int remaining = high - slot;
        while (remaining) {
            --remaining;
            ++index;
            if (!entries[index].key.block) {
                Rva0089D180Block *data = key.block;
                entries[index].key.block = data;
                ++data->refs;
                store(index, value);
                return;
            }
            if (entries[index].key.block == &Rva012D5298) {
                // Retail deliberately updates only an already found tombstone.
                if (empty != -1) empty = index;
            } else if (entries[index].key == key) {
                replace(index, value);
                return;
            }
        }
        index = slot;
        remaining = slot - low;
        while (remaining) {
            --index;
            --remaining;
            if (!entries[index].key.block) {
                Rva0089D180Block *data = key.block;
                entries[index].key.block = data;
                ++data->refs;
                store(index, value);
                return;
            }
            if (entries[index].key.block == &Rva012D5298) {
                if (empty != -1) empty = index;
            } else if (entries[index].key == key) {
                replace(index, value);
                return;
            }
        }
        if (empty == -1) {
            rebuild();
            rva0089D5B0(key, value);
        } else {
            entries[empty].key.assign(key);
            store(empty, value);
        }
    }
};

void Rva0089D180Table::rebuild() {
    Rva0089D180Table table(count * 2);
    table.entries = (Rva0089D180Entry *)Rva008C5D70Alloc(table.count * 8);
    memset(table.entries, 0, table.count * 8);
    for (int i = 0; i < count; ++i) {
        Rva0089D180Entry *entry = entries + i;
        if (entry->key.block && entry->key.block != &Rva012D5298)
            table.insert(entry->key, (void *)(entry->value & ~1u));
    }
    Rva0089D180Entry *oldEntries = entries;
    entries = table.entries;
    table.entries = oldEntries;
    int oldCount = count;
    count = table.count;
    table.count = oldCount;
    ((Gen0089C880 *)&table)->handle();
}
