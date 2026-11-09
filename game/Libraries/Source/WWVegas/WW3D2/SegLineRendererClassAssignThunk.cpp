// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift SegLineRendererClass::operator= __emit thunk to clean C++.
// Refcounted texture pointer at +0 (Add_Ref inline: inc word [p+4]; Release_Ref
// out-of-line and matched), then the plain field copies.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
    void Add_Ref() { ++*(unsigned short *)((char *)this + 4); }
    void Release_Ref();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
    SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
    TextureBaseClass *m_texture;
    unsigned int Shader;
    unsigned int Width;
    unsigned int Color;
    unsigned int m_f10;
    unsigned int m_f14;
    unsigned int m_opacity;
    unsigned int SubdivisionLevel;
    unsigned int m_noiseAmplitude;
    unsigned int m_f24;
    unsigned int MergeAbortFactor;
    unsigned int m_textureTileFactor;
    unsigned int m_lastUsedSyncTime;
    unsigned int m_f34;
    unsigned int m_f38;
    unsigned int UVOffsetDeltaPerMS;
    unsigned int m_f40;
    unsigned int m_bits;
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
    Shader = that.Shader;
    Width = that.Width;
    SubdivisionLevel = that.SubdivisionLevel;
    Color = that.Color;
    m_f10 = that.m_f10;
    m_f14 = that.m_f14;
    m_opacity = that.m_opacity;
    m_noiseAmplitude = that.m_noiseAmplitude;
    m_f24 = that.m_f24;
    MergeAbortFactor = that.MergeAbortFactor;
    m_textureTileFactor = that.m_textureTileFactor;
    m_lastUsedSyncTime = that.m_lastUsedSyncTime;
    m_f34 = that.m_f34;
    m_f38 = that.m_f38;
    UVOffsetDeltaPerMS = that.UVOffsetDeltaPerMS;
    m_f40 = that.m_f40;
    m_bits = that.m_bits;
    return *this;
}
