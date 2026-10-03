// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
// RVA 0x006EB000, 54 bytes. The owner and method name are not recovered.
// Thiscall with one borrowed pointer-handle reference; RET 4 at 0x006EB033,
// then INT3 at 0x006EB036. Only the reference-counted texture contract is named.
// The texture count is the low word at +4; Release_Ref reaches 0x009EB7A0.
// An inlined handle assignment preserves the retail pointer-before-mask stores.
// See targets/game/reverse/identity_evidence/006eb000-owning-texture-assignment.md.
#include "texture.h"

class Rva006EB000TextureRef
{
public:
    TextureBaseClass *m_value;

    ~Rva006EB000TextureRef()
    {
        if (m_value)
            m_value->Release_Ref();
    }

    __forceinline Rva006EB000TextureRef &operator=(const Rva006EB000TextureRef &other)
    {
        if (other.m_value)
            other.m_value->Add_Ref();
        if (m_value)
            m_value->Release_Ref();
        m_value = other.m_value;
        return *this;
    }
};

class Rva006EB000
{
public:
    void method(const Rva006EB000TextureRef &value);

private:
    unsigned char m_fields00[0x4c];
    Rva006EB000TextureRef m_bfmeTexERB;
    int m_bfmeMaskERB;
};

void Rva006EB000::method(const Rva006EB000TextureRef &value)
{
    if (value.m_value == m_bfmeTexERB.m_value)
        return;
    m_bfmeTexERB = value;
    m_bfmeMaskERB = m_bfmeTexERB.m_value ? -1 : 0;
}
