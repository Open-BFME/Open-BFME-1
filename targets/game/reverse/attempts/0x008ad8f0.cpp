// ?bfmeApply1236@BfmeB1236@@QAEXPAX@Z
// partial score=0.9834 date=2026-09-30
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AD8F0 (603 B): lays out an Apt text binding through an inline binding method
// that takes the character and the binding's source as parameters, fills the 0x70-byte
// host layout request, and re-anchors the character for centred and right alignment.

struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;

class BfmeStrVKI {
public:
    const char *text() const { return (const char *)(m_data + 1); }
    BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value;

struct Rva008AD8F0Source {
    char m_gap00[0x18];
    int m_index18;
    char m_gap1c[0x2c - 0x1c];
    int m_2c;
    int m_30;
};

struct Rva008AD8F0Owner {
    BfmeStrVKI m_string00;
    char m_gap04[4];
    int m_08;
    char m_gap0c[4];
    int m_rect[4];
};

struct Rva008AD8F0Handle;
extern Rva008AD8F0Handle g_aptTextNull012D5598;

class Rva008AD750StringBinding {
public:
    void refresh(Rva8CD130Value *scope);
    void layout(class BfmeB1236 *character, Rva008AD8F0Source *source, void *a);
    char m_gap00[0x0c];
    Rva008AD8F0Source *m_source0c;
    char m_gap10[8];
    BfmeStrVKI m_string18;
    BfmeStrVKI m_string1c;
    Rva008AD8F0Handle *m_handle20;
    int m_fallback24;
    int m_28;
    int m_2c;
    int m_30;
    int m_34;
    int m_mode38;
    int m_3c;
    char m_gap40[4];
    int m_44;
    int m_48;
    int m_4c;
    float m_left50, m_top54, m_right58, m_bottom5c;
    int m_60;
    int m_index64;
    Rva008AD8F0Owner *m_owner68;
    unsigned m_flags6c;
    char m_gap70[4];
    unsigned m_flags74;
};

// The request the host layout callback fills in.
struct BfmeApplyRecord1236 {
    const char *m_text;
    float m_left, m_top, m_right, m_bottom;
    int m_14;
    int m_mode;
    int m_1c;
    int m_20;
    int m_sourceA;
    int m_sourceB;
    int m_2c;
    int m_30;
    int m_34;
    int m_flagBit2;
    int m_flagBit1;
    int m_40;
    int m_44;
    int m_60;
    int m_2cCopy;
    int m_50;
    const char *m_string;
    unsigned m_flags;
    Rva008AD8F0Handle *m_handle;
    int m_ownerRect[4];
};

extern void (__cdecl *g_aptTextRelease01337874)(Rva008AD8F0Handle *handle, unsigned flags);
extern Rva008AD8F0Handle *(__cdecl *g_aptTextLayout01337870)(BfmeApplyRecord1236 *request);

struct Rva008AD8F0Entry { char m_gap00[8]; const char *m_text08; };
struct Rva008AD8F0Table { char m_gap00[0x10]; Rva008AD8F0Entry **m_entries; };
struct BfmeApplyMap1236 { char m_gap00[4]; char *m_base04; };
struct BfmeApplyNode1236 { char m_gap00[0x0c]; BfmeApplyMap1236 *m_movie; };
struct BfmeApplyArgument1236 { char m_gap00[0x50]; BfmeApplyNode1236 *m_node; };

class BfmeSlotState1289 {
public:
    void bfmeSetAxis1289(int axis, float value, int enabled);
};

class BfmeB1236 {
public:
    void bfmeApply1236(void *a);
    char m_gap00[0x20];
    float m_position20;
    char m_gap24[0x50 - 0x24];
    Rva008AD750StringBinding *m_binding50;
};

// ?layout@Rva008AD750StringBinding@@QAEXPAVBfmeB1236@@PAURva008AD8F0Source@@PAX@Z absent-from-retail
__forceinline void Rva008AD750StringBinding::layout(BfmeB1236 *character, Rva008AD8F0Source *source, void *a)
{
    refresh((Rva8CD130Value *)a);
    if (m_flags6c & 1)
        return;
    if (m_handle20 && m_handle20 != &g_aptTextNull012D5598)
        g_aptTextRelease01337874(m_handle20, m_flags6c);

    char *movieText = ((BfmeApplyArgument1236 *)a)->m_node->m_movie->m_base04 + 8;
    BfmeStringData3AF0 *string = m_string18.m_data;
    if (string == &g_bfmeDefaultString1284) {
        m_handle20 = &g_aptTextNull012D5598;
        if (m_mode38 != 3) {
            m_right58 = m_left50 + 4.0f;
            m_bottom5c = m_top54 + 4.0f;
        }
        m_44 = 0;
        m_48 = 0;
        m_flags6c = 1;
        return;
    }

    BfmeApplyRecord1236 request;
    request.m_sourceA = source->m_2c;
    request.m_sourceB = source->m_30;
    request.m_14 = m_3c;
    request.m_mode = m_mode38;
    Rva008AD8F0Owner *owner = m_owner68;
    request.m_60 = m_60;
    if (owner && owner->m_08 != -1)
        request.m_2c = owner->m_08;
    else
        request.m_2c = m_fallback24;
    request.m_2cCopy = m_2c;
    if (owner && owner->m_string00.m_data != &g_bfmeDefaultString1284)
        request.m_text = owner->m_string00.text();
    else if (source->m_index18 >= 0)
        request.m_text = ((Rva008AD8F0Table *)movieText)->m_entries[m_index64]->m_text08;
    else
        request.m_text = 0;
    request.m_left = m_left50;
    request.m_right = m_right58;
    request.m_top = m_top54;
    request.m_bottom = m_bottom5c;
    request.m_30 = m_30;
    request.m_34 = m_34;
    request.m_string = (const char *)(string + 1);
    unsigned styleFlags = m_flags74;
    request.m_flagBit2 = (styleFlags >> 2) & 1;
    request.m_flagBit1 = (styleFlags >> 1) & 1;
    request.m_flags = m_flags6c;
    request.m_handle = m_handle20;
    if (!owner) {
        request.m_ownerRect[0] = 0;
        request.m_ownerRect[1] = -1;
        request.m_ownerRect[2] = -1;
        request.m_ownerRect[3] = -1;
    } else {
        request.m_ownerRect[0] = owner->m_rect[0];
        request.m_ownerRect[1] = owner->m_rect[1];
        request.m_ownerRect[2] = owner->m_rect[2];
        request.m_ownerRect[3] = owner->m_rect[3];
    }
    m_handle20 = g_aptTextLayout01337870(&request);

    int mode = m_mode38;
    if (mode != 3) {
        float oldWidth = m_right58 - m_left50;
        float newWidth = request.m_right - request.m_left;
        if (mode == 2)
            ((BfmeSlotState1289 *)character)->bfmeSetAxis1289(0, character->m_position20 - (newWidth - oldWidth) * 0.5f, 1);
        else if (mode == 1)
            ((BfmeSlotState1289 *)character)->bfmeSetAxis1289(0, oldWidth + character->m_position20 - newWidth, 1);
    }
    m_left50 = request.m_left;
    m_right58 = request.m_right;
    m_top54 = request.m_top;
    m_bottom5c = request.m_bottom;
    int lines = request.m_1c;
    m_28 = lines;
    if (m_2c > lines)
        m_2c = lines;
    m_44 = request.m_40;
    m_48 = request.m_44;
    m_4c = request.m_20;
    m_flags6c = 1;
}

// ?bfmeApply1236@BfmeB1236@@QAEXPAX@Z
void BfmeB1236::bfmeApply1236(void *a)
{
    Rva008AD750StringBinding *binding = m_binding50;
    binding->layout(this, binding->m_source0c, a);
}
