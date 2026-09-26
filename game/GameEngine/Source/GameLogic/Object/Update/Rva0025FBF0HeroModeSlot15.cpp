// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x0025FBF0, 201 bytes.
//
// The enclosing HeroModeSpecialAbilityUpdate constructor stores the primary
// vtable 0x010B59A0.  Its slot 15 is the ILT 0x00033870, which enters this
// body.  The semantic spelling of that slot is not established by the
// available headers, so the callable owner below deliberately stays
// address-derived while retaining the proven class/layout relationship.

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    ~AsciiString() { releaseBuffer(); }
};

class Rva0025FBF0LayoutString
{
public:
    const char *str() const
    {
        return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
    }

    void *m_data;
};

class Rva0025FBF0ModuleData
{
private:
    unsigned char m_base[0x254];

public:
    Rva0025FBF0LayoutString m_layout;
    int m_258;
    bool m_25c;
};

class Rva0025FBF0Object
{
private:
    unsigned char m_base[0x124];

public:
    unsigned int m_flags124;
    unsigned int m_flags128;
};

class Rva0025FBF0HeroModeSlot15
{
public:
    void run();

private:
    void *m_primaryVtable;
    Rva0025FBF0ModuleData *m_moduleData;
    Rva0025FBF0Object *m_object;
};

extern void j_0002852e();
extern void j_00033870();
extern void j_00037a56();
extern void j_0003fa30();

// ?run@Rva0025FBF0HeroModeSlot15@@QAEXXZ
void Rva0025FBF0HeroModeSlot15::run()
{
    typedef void (Rva0025FBF0HeroModeSlot15::*InitializeCall)();
    union
    {
        void *asVoid;
        InitializeCall asMember;
    } initializeCast;
    initializeCast.asVoid = (void *)j_0003fa30;
    (this->*initializeCast.asMember)();

    Rva0025FBF0ModuleData *data = m_moduleData;
    Rva0025FBF0Object *object = m_object;
    if (data->m_layout.m_data != 0 &&
        *(const unsigned short *)((const char *)data->m_layout.m_data + 4) != 0)
    {
        AsciiString temporary(data->m_layout.str());

        typedef void (Rva0025FBF0Object::*ApplyLayoutCall)(
            const AsciiString *, int);
        union
        {
            void *asVoid;
            ApplyLayoutCall asMember;
        } applyLayoutCast;
        applyLayoutCast.asVoid = (void *)j_00037a56;
        (object->*applyLayoutCast.asMember)(&temporary, -1);
    }

    typedef void (Rva0025FBF0Object::*ApplyCommandCall)(int, int);
    union
    {
        void *asVoid;
        ApplyCommandCall asMember;
    } applyCommandCast;
    applyCommandCast.asVoid = (void *)j_0002852e;

    if (data->m_25c)
    {
        if ((object->m_flags124 & 0x10000) == 0)
            (object->*applyCommandCast.asMember)(0xB0, data->m_258);
    }
    else if ((object->m_flags128 & 0x20000) == 0)
    {
        (object->*applyCommandCast.asMember)(0xD1, data->m_258);
    }
}
