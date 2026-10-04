// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008D32B0. Opaque identity: serialized nested records, relocated in place.
// Code ends 008D35E9; 3-byte alignment and 8-entry switch table end 008D360C.
// ret 12 at 008D34CE; case 2 resumes 008D349E via jmp at 008D35E4.
extern void *(*Rva008C5D70Alloc)(unsigned int);
extern "C" void (*TheBfmeFree)(void *, unsigned int);
struct Rva008D32B0Block { unsigned short refs; };
struct Rva008D32B0Release { void *m_00; void (__cdecl *free)(void *); };
extern Rva008D32B0Release *g_bfmeStringPool1284;
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *p) { bfmeSetVKI(p); }
    void bfmeSetVKI(const char *);
    ~BfmeStrVKI() { Rva008D32B0Block *old = m_00; if (--old->refs == 0) g_bfmeStringPool1284->free(old); }
    Rva008D32B0Block *m_00;
};
// Shared address-based sized-delete view, also used by matched 00899800.
struct Gen_uws16_008976d0 { static void operator delete(void *, unsigned); };
class Rva0089C860State : public Gen_uws16_008976d0 {
public:
    Rva0089C860State(int n) { initialize(n); }
    Rva0089C860State *initialize(int n);
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    int m_00, m_04, m_08, m_0c;
};
struct Rva008D32B0Value {
    void *m_00;
    unsigned m_04;
    union { Rva008D32B0Value *m_next; int m_value; };
};
struct Rva008D32B0Pool {
    int m_capacity, m_count;
    Rva008D32B0Value **m_items;
    __forceinline void add(Rva008D32B0Value *p) {
        int &count = m_count;
        if (count >= m_capacity) p->m_04 &= 0xbfffffff;
        else { m_items[count] = p; count++; }
    }
};
// Chain head at 0x013387D0; defined in game/GameEngine/Source/Common/Rva008D2A10Link.cpp
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
extern Rva008D32B0Pool *g_rva8CD130IdleHook;
// Retail vtables: ??_7AptValue@@6B@ at 0x01135D68, ??_7AptInteger@@6B@ at
// 0x01136400 (targets/game/reverse/dir32_addresses.csv). Referenced by their
// own mangled names, the way CameraPath_dtor.cpp and WorldHeightMapRva0074ACB0Load.cpp
// bind their vftables.
extern "C" const void *__identifier("??_7AptValue@@6B@")[];
extern "C" const void *__identifier("??_7AptInteger@@6B@")[];
__forceinline Rva008D32B0Value *rva008D32B0Integer(int value) {
    Rva008D32B0Value *p = (Rva008D32B0Value *)g_rva008D2A10;
    if (p) {
        g_rva008D2A10 = (Rva008D2A10 *)p->m_next;
        g_rva8CD130IdleHook->add(p);
        p->m_value = value;
        return p;
    }
    p = (Rva008D32B0Value *)Rva008C5D70Alloc(12);
    if (p) {
        p->m_00 = (void *)__identifier("??_7AptValue@@6B@");
        p->m_04 = (p->m_04 & 0xf0008007) | 0x40008007;
        g_rva8CD130IdleHook->add(p);
        p->m_00 = (void *)__identifier("??_7AptInteger@@6B@");
        p->m_value = value;
        return p;
    }
    return 0;
}
class BfmeTab1024 { public: void bfmeAdd1024(int, int); };
// Retail reaches FUN_00ccbdf0 through the 5-byte ILT thunk at 0x008CC560, so
// the call target is ?j_008cc560@@YAXXZ; declare that name and call it with the
// same four stack arguments.
extern void j_008cc560();
typedef void (__cdecl *Rva008D32B0Thunk)(void *, void *, int, void *);
struct Rva008D32B0Command { int m_00; unsigned m_04, m_08; unsigned m_0c[10]; unsigned m_34, m_38, m_3c; };
struct Rva008D32B0Row { int m_count; Rva008D32B0Command **m_commands; };
struct Rva008D32B0Item { unsigned m_00, m_04; void *m_08; };
struct Rva008D32B0Sub { int m_count; Rva008D32B0Item *m_items; };
class Rva008D32B0 {
public:
    int m_count;
    Rva008D32B0Row *m_rows;
    Rva0089C860State *m_state;
    void relocate(unsigned base, int arg2, void *arg3);
};
#define RVA_RELOCATE(lvalue) if (lvalue) (unsigned &)(lvalue) += base
void Rva008D32B0::relocate(unsigned base, int arg2, void *arg3) {
    m_state = new Rva0089C860State(2);
    RVA_RELOCATE(m_rows);
    for (int i = 0; i < m_count; ++i) {
        RVA_RELOCATE(m_rows[i].m_commands);
        for (int j = 0; j < m_rows[i].m_count; ++j) {
            RVA_RELOCATE(m_rows[i].m_commands[j]);
            switch (m_rows[i].m_commands[j]->m_00) {
            case 1:
                RVA_RELOCATE(m_rows[i].m_commands[j]->m_04);
                ((Rva008D32B0Thunk)(void *)j_008cc560)((void *)m_rows[i].m_commands[j]->m_04, (void *)base, arg2, arg3);
                break;
            case 8:
                RVA_RELOCATE(m_rows[i].m_commands[j]->m_08);
                ((Rva008D32B0Thunk)(void *)j_008cc560)((void *)m_rows[i].m_commands[j]->m_08, (void *)base, arg2, arg3);
                break;
            case 3: {
                RVA_RELOCATE(m_rows[i].m_commands[j]->m_34);
                RVA_RELOCATE(m_rows[i].m_commands[j]->m_3c);
                Rva008D32B0Sub *sub = (Rva008D32B0Sub *)m_rows[i].m_commands[j]->m_3c;
                if (sub) {
                    RVA_RELOCATE(sub->m_items);
                    for (int k = 0; k < sub->m_count; ++k) {
                        RVA_RELOCATE(sub->m_items[k].m_08);
                        ((Rva008D32B0Thunk)(void *)j_008cc560)(sub->m_items[k].m_08, (void *)base, arg2, arg3);
                    }
                }
                break;
            }
            case 2: {
                RVA_RELOCATE(m_rows[i].m_commands[j]->m_04);
                BfmeStrVKI key((const char *)m_rows[i].m_commands[j]->m_04);
                ((BfmeTab1024 *)m_state)->bfmeAdd1024((int)&key, (int)rva008D32B0Integer(i));
                break;
            }
            }
        }
    }
}
