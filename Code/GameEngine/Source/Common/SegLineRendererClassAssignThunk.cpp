// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift SegLineRendererClass::operator= __emit thunk to clean C++.
// Refcounted texture pointer at +0 (Add_Ref inline: inc word [p+4]; Release_Ref
// out-of-line and matched), then the plain field copies.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
    void Add_Ref() { ++*(unsigned short *)((char *)this + 4); }
    void Release_Ref();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
    SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
    TextureBaseClass *m_texture;
    unsigned int m_f04;
    unsigned int m_f08;
    unsigned int m_f0C;
    unsigned int m_f10;
    unsigned int m_f14;
    unsigned int m_f18;
    unsigned int m_f1C;
    unsigned int m_f20;
    unsigned int m_f24;
    unsigned int m_f28;
    unsigned int m_f2C;
    unsigned int m_f30;
    unsigned int m_f34;
    unsigned int m_f38;
    unsigned int m_f3C;
    unsigned int m_f40;
    unsigned int m_f44;
};

// ??4SegLineRendererClass@@QAEAAV0@ABV0@@Z
SegLineRendererClass &SegLineRendererClass::operator=(const SegLineRendererClass &that)
{
    if (this == &that)
        return *this;
    if (that.m_texture)
        that.m_texture->Add_Ref();
    if (m_texture)
        m_texture->Release_Ref();
    m_texture = that.m_texture;
    m_f04 = that.m_f04;
    m_f08 = that.m_f08;
    m_f1C = that.m_f1C;
    m_f0C = that.m_f0C;
    m_f10 = that.m_f10;
    m_f14 = that.m_f14;
    m_f18 = that.m_f18;
    m_f20 = that.m_f20;
    m_f24 = that.m_f24;
    m_f28 = that.m_f28;
    m_f2C = that.m_f2C;
    m_f30 = that.m_f30;
    m_f34 = that.m_f34;
    m_f38 = that.m_f38;
    m_f3C = that.m_f3C;
    m_f40 = that.m_f40;
    m_f44 = that.m_f44;
    return *this;
}
