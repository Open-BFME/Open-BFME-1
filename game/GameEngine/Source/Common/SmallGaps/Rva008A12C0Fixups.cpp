// ?rva008A12C0@Rva008A25C0Object@@QAEXPAX0@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Opaque reconstruction of the retail object-table fixup method.
// Retail code: RVA008A12C0..008A143C (381 bytes; RET8 at +17A).
// Owned six-entry jump table is at +180, after three alignment bytes.
// Full COFF code/table range agrees with all 408 retail bytes modulo relocations.
// See reverse/identity_evidence/008a12c0-object-table-fixups.md.
// The reference helper preserves the index-to-pointer assignment expression.
// Case 4 must continue to link fixups even after a nonempty entry loop.

struct Rva008A1050Entry;

struct Rva008A1050Table {
    char m_pad00[0x18];
    int *m_values;
    char m_pad1c[0x14];
    int m_count;
    Rva008A1050Entry *m_entries;
};

struct Rva008A1050Owner {
    char m_pad00[0x10];
    Rva008A1050Table *m_table;
    int findNamedSlot(const char *name);
};

struct Rva008A12C0Entry {
    void *m_pad00;
    const char *m_name;
    int m_slot;
    Rva008A1050Owner *m_owner;
};

struct Rva008A12C0RecordEntry {
    int m_pad00;
    int m_slot;
    char m_pad08[0x3c];
};

struct Rva008A12C0Link {
    int m_slot00;
    int m_slot04;
    int m_slot08;
    int m_slot0c;
};

struct Rva008A12C0Record {
    int m_kind;
    int m_pad04;
    int m_slot08;
    int m_count0c;
    int *m_slots10;
    char m_pad14[0x18];
    int m_count2c;
    Rva008A12C0RecordEntry *m_entries30;
    char m_pad34[8];
    Rva008A12C0Link *m_link3c;
};

typedef void (__cdecl *Rva008A12C0Callback)(void *, int, void *);
extern void (__cdecl *g_bfmeSlot23VB)(void);

struct Rva008A25C0Object {
    char m_pad00[0x0c];
    int m_recordCount;
    int *m_slots;
    char m_pad14[0x0c];
    int m_namedCount;
    Rva008A12C0Entry *m_namedEntries;

    void rva008A12C0(void *, void *);
    __forceinline void rva008A12C0Slot(int &slot) { slot=m_slots[slot]; }
};

void Rva008A25C0Object::rva008A12C0(void *unused, void *argument)
{
    for (int i = 0; i < m_namedCount; ++i) {
        Rva008A1050Owner *owner = m_namedEntries[i].m_owner;
        int value = owner->findNamedSlot(m_namedEntries[i].m_name);
        m_slots[m_namedEntries[i].m_slot] = value;
    }

    for (int i = 0; i < m_recordCount; ++i) {
        Rva008A12C0Record *record =
            ((Rva008A12C0Record **)m_slots)[i];
        if (record == 0)
            continue;

        switch (record->m_kind) {
        case 7:
            ((Rva008A12C0Callback)g_bfmeSlot23VB)(
                argument, i, (void *)record->m_slot08);
            break;

        case 8:
            ((Rva008A12C0Record **)m_slots)[i]->m_slot08 =
                m_slots[((Rva008A12C0Record **)m_slots)[i]->m_slot08];
            ((Rva008A12C0Record **)m_slots)[i]->m_count0c =
                m_slots[((Rva008A12C0Record **)m_slots)[i]->m_count0c];
            break;

        case 4:
                for (int j = 0;
                     j < ((Rva008A12C0Record **)m_slots)[i]->m_count2c; ++j) {
                    Rva008A12C0RecordEntry *entry =
                        ((Rva008A12C0Record **)m_slots)[i]->m_entries30 + j;
                    rva008A12C0Slot(entry->m_slot);
                }
            if (((Rva008A12C0Record **)m_slots)[i]->m_link3c != 0) {
                Rva008A12C0Link *link =
                    ((Rva008A12C0Record **)m_slots)[i]->m_link3c;
                if (link->m_slot04 != 0)
                    link->m_slot04 = m_slots[link->m_slot04];
                if (link->m_slot0c != 0)
                    link->m_slot0c = m_slots[link->m_slot0c];
                if (link->m_slot00 != 0)
                    link->m_slot00 = m_slots[link->m_slot00];
                if (link->m_slot08 != 0)
                    link->m_slot08 = m_slots[link->m_slot08];
            }
            break;

        case 5:
        case 6:
            break;

        case 3:
            for (int j = 0;
                 j < ((Rva008A12C0Record **)m_slots)[i]->m_count0c; ++j) {
                int *slots = ((Rva008A12C0Record **)m_slots)[i]->m_slots10;
                rva008A12C0Slot(slots[j]);
            }
            break;
        }
    }

    (void)unused;
}


