// ?d_006e2ac0@@YAXXZ
// partial score=0.6397915389331699 date=2026-09-22
// cl: /FAsc /Fabuild/gap_006e29a6/candidate.cod /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Candidate, not a match. Retail RVA 0x006E2AC0, full extent 13048 bytes.
// Vtable VA 0x0111E23C slot 2 -> ILT 0x0003B1CE -> this body.
// The original derived-class identity is not proved; retain the address token.
// All offsets and address-scoped callee contracts are detailed in
// build/gap_006e29a6/GAP.md. No assembly or emitted retail bytes are used.

#include "dx8wrapper.h"
#include "vertmaterial.h"
#include "texture.h"
#include "wwstring.h"
#include "color.h"
#include "StringInline.h"
#include <math.h>
#include <stddef.h>

// The SDK-like D3D8 header has different virtual offsets from this retail
// device. This view only describes witnessed BFME call slots; it is not an
// alternate definition of the existing SDK interface.
struct Rva006E2AC0Device;
struct Rva006E2AC0DeviceSlots {
    void *before_b0[0xb0/4];
    int (__stdcall *set_transform)(Rva006E2AC0Device *, unsigned, const D3DXMATRIX *);
    int (__stdcall *get_transform)(Rva006E2AC0Device *, unsigned, D3DXMATRIX *);
    void *before_e4[(0xe4-0xb8)/4];
    int (__stdcall *render_state)(Rva006E2AC0Device *, unsigned, unsigned);
    void *before_10c[(0x10c-0xe8)/4];
    int (__stdcall *texture_state)(Rva006E2AC0Device *, unsigned, unsigned, unsigned);
    void *at_110;
    int (__stdcall *sampler_state)(Rva006E2AC0Device *, unsigned, unsigned, unsigned);
};
struct Rva006E2AC0Device { Rva006E2AC0DeviceSlots *v; };

extern Rva006E2AC0Device *g_va01340534;
extern unsigned g_va0133F9E0[8][32];
extern unsigned g_va01340100[256];
extern bool g_va0133F451;
extern unsigned g_va01340594;
extern unsigned g_va01340564;
extern unsigned g_va01340568;
extern unsigned g_va0134054C;
extern unsigned g_va0133F49C;
extern VertexMaterialClass *g_va01340EC4;
extern unsigned g_va0133F420;
extern int g_va012BA938;
extern unsigned char g_va012D6DFC;

static __forceinline void RenderState(unsigned long state, unsigned value)
{
    if (g_va01340100[state] == value) return;
    if (g_va0133F451) {
        StringClass name(0,true);
        DX8Wrapper::Get_DX8_Render_State_Value_Name(name,state,value);
    }
    g_va01340100[state] = value;
    g_va01340534->v->render_state(g_va01340534,state,value);
    ++g_va01340594;
    ++g_va01340564;
}

static __forceinline void TextureState(unsigned stage, unsigned long state, unsigned value)
{
    if (g_va0133F9E0[stage][state] == value) return;
    if (g_va0133F451) {
        StringClass name(0,true);
        DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(name,state,value);
    }
    g_va0133F9E0[stage][state] = value;
    g_va01340534->v->texture_state(g_va01340534,stage,state,value);
    ++g_va01340594;
    ++g_va01340568;
}

static __forceinline void SamplerState(unsigned stage, unsigned state, unsigned value)
{
    g_va01340534->v->sampler_state(g_va01340534,stage,state,value);
    ++g_va01340594;
    ++g_va01340568;
}

static __forceinline void GetTransform(unsigned state, D3DXMATRIX &matrix)
{
    g_va01340534->v->get_transform(g_va01340534,state,&matrix);
    ++g_va01340594;
}

static __forceinline void SetTransform(unsigned state, const D3DXMATRIX &matrix)
{
    ++g_va0134054C;
    g_va01340534->v->set_transform(g_va01340534,state,&matrix);
    ++g_va01340594;
}

static __forceinline void Identity(D3DXMATRIX &m)
{
    m._12 = m._13 = m._14 = m._21 = m._23 = m._24 = m._31 = m._32 =
        m._34 = m._41 = m._42 = m._43 = 0.0f;
    m._11 = m._22 = m._33 = m._44 = 1.0f;
}

// Retail uses the D3DX out-parameter multiply followed by 64-byte copies.
// This helper restores that multiply-and-copy shape using the existing
// matrix type. Its built-in operator instead expands scalar expressions.
static __forceinline D3DXMATRIX Multiply(const D3DXMATRIX &left, const D3DXMATRIX &right)
{
    D3DXMATRIX result;
    D3DXMatrixMultiply(&result,&left,&right);
    return result;
}

extern "C" D3DXPLANE *__stdcall D3DXPlaneFromPointNormal(D3DXPLANE *, const D3DXVECTOR3 *, const D3DXVECTOR3 *);

// One-word nontrivial return object: 0x0090E910 returns through a hidden
// caller-owned word, and 0x009EB7A0 releases it after handle assignment.
class BFMEWaterTrackTextureHandle {
public:
    TextureBaseClass *value;
    ~BFMEWaterTrackTextureHandle() { if (value) value->Release_Ref(); }
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *,int,int);
class Gen_005D2040 {
public:
    Gen_005D2040 &operator=(const Gen_005D2040 &);
};
class ShroudFilter {
public:
    char before_0c[0x0c];
    int at_0c, at_10;
};
class ShroudTexture {
public:
    ShroudFilter *getFilter();
};
class Gen_00920a60 {
public:
    void m(int);
};
extern void BoxSetTexture(unsigned,TextureBaseClass *&);

// These signatures are address-scoped declarations, NOT semantic pins.
// Retail: ECX receiver, one hidden string-result pointer, callee ret 4.
class Rva006E2220 { public: AsciiString copyString(); };
class Rva006E2250 { public: AsciiString copyString(); };
class Rva006E2280 { public: AsciiString copyString(); };
class Rva006E22B0 { public: AsciiString copyString(); };
struct Rva006E1C80Pair { unsigned first,second; };
class Rva006E1C80Owner { public: void copyTo(Rva006E1C80Pair *) const; };
class Rva0040B2E0 { public: float scale() const; };

struct Rva012F1104View {
    char before_18[0x18];
    float at_18;
    char before_24[8];
    float at_24, at_28;
    char before_b0[0xb0-0x2c];
    int at_b0, at_b4;
};
extern Rva012F1104View *g_va012F1104;
struct Rva012F0FE0View { char before_0c[0xc]; int at_0c; };
extern Rva012F0FE0View *g_va012F0FE0;
struct Rva012F7FE0Dimensions { char before_08[8]; int at_08,at_0c; };
struct Rva012F7FE0View { char before_2ff4[0x2ff4]; Rva012F7FE0Dimensions *at_2ff4; };
extern Rva012F7FE0View *g_va012F7FE0;
struct Rva012F0898View { char before_3c[0x3c]; unsigned at_3c; };
extern Rva012F0898View *g_va012F0898;
struct Rva012F1464View {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64();
    virtual unsigned slot68();
};
extern Rva012F1464View *g_va012F1464;

static __forceinline void AssignTexture(TextureBaseClass *&dst,const BFMEWaterTrackTextureHandle &src)
{
    ((Gen_005D2040 *)&dst)->operator=((const Gen_005D2040 &)src);
}

static __forceinline void ConfigureTexture(TextureBaseClass *&value, int mode)
{
    ((ShroudTexture *)&value)->getFilter()->at_0c = mode;
    ((ShroudTexture *)&value)->getFilter()->at_10 = mode;
    ((Gen_00920a60 *)((ShroudTexture *)&value)->getFilter())->m(0);
}

class Rva006E2AC0 {
public:
    virtual void method() const;
    char before_38[0x38-4];
    mutable float at_38, at_3c, at_40;
    mutable unsigned at_44;
    unsigned at_48;
    mutable float at_4c, at_50;
    unsigned char at_54;
    char before_58[3];
    mutable TextureBaseClass *at_58, *at_5c, *at_60, *at_64;
    mutable unsigned char at_68;
    unsigned char at_69, at_6a, at_6b;
    mutable D3DXVECTOR3 at_6c, at_78;
    mutable D3DXPLANE at_84;
    mutable D3DXMATRIX at_94;
    mutable float at_d4, at_d8;
    unsigned at_dc;
    mutable float at_e0;
    mutable unsigned at_e4;
};

// Compile-time checks for the measured ABI view; padding has no inferred meaning.
typedef char Rva006E2AC0_Size[(sizeof(Rva006E2AC0)==0xe8)?1:-1];
typedef char Rva006E2AC0_MatrixSize[(sizeof(D3DXMATRIX)==64)?1:-1];
typedef char Rva006E2AC0_VectorOutput[(sizeof(D3DXVECTOR4)==16)?1:-1];
typedef char Rva006E2AC0_TextureOffset[(offsetof(Rva006E2AC0,at_58)==0x58)?1:-1];
typedef char Rva006E2AC0_PlaneOffset[(offsetof(Rva006E2AC0,at_84)==0x84)?1:-1];
typedef char Rva006E2AC0_MatrixOffset[(offsetof(Rva006E2AC0,at_94)==0x94)?1:-1];
typedef char Rva006E2AC0_FrameOffset[(offsetof(Rva006E2AC0,at_e4)==0xe4)?1:-1];
typedef char Rva006E2AC0_ConfigState[(offsetof(Rva012F1104View,at_b0)==0xb0)?1:-1];

void Rva006E2AC0::method() const
{
    if (!g_va012BA938) return;
    if (!g_va012F0FE0) return;
    DX8Wrapper::Invalidate_Cached_Render_States();
    g_va012D6DFC = 1;
    VertexMaterialClass *material = VertexMaterialClass::Get_Preset((VertexMaterialClass::PresetType)0);
    if (material) material->Add_Ref();
    if (g_va01340EC4) g_va01340EC4->Release_Ref();
    g_va01340EC4 = material;
    g_va0133F49C |= 0x4000;
    if (material) material->Release_Ref();
    DX8Wrapper::Apply_Render_State_Changes();

    if (g_va012BA938 == 1) {
        if (!at_58) {
            AssignTexture(at_58,BFMEGetWaterTrackTexture((char *)((Rva006E2220 *)g_va012F1104)->copyString().str(),0,0));
            ConfigureTexture(at_58,0);
        }
        if (!at_60) {
            AssignTexture(at_60,BFMEGetWaterTrackTexture((char *)((Rva006E2280 *)g_va012F1104)->copyString().str(),0,0));
            ConfigureTexture(at_60,1);
        }
        if (!at_64) {
            AssignTexture(at_64,BFMEGetWaterTrackTexture((char *)((Rva006E22B0 *)g_va012F1104)->copyString().str(),0,0));
            ConfigureTexture(at_64,1);
        }
        BoxSetTexture(0,at_58);
        BoxSetTexture(1,at_58);
        BoxSetTexture(2,at_60);
        BoxSetTexture(3,at_64);
        RenderState(15,0);
        if (!at_69) {
            TextureState(0,1,1);
            return;
        }
        TextureState(0,1,2);
        TextureState(0,2,2);
        TextureState(0,3,1);
        TextureState(0,4,2);
        TextureState(0,5,2);
        TextureState(0,6,1);
        TextureState(1,1,3);
        TextureState(1,2,2);
        TextureState(1,3,1);
        TextureState(1,4,2);
        TextureState(1,5,2);
        TextureState(1,6,1);
        TextureState(2,1,19);
        TextureState(2,2,2);
        TextureState(2,3,1);
        TextureState(2,4,2);
        TextureState(2,5,2);
        TextureState(2,6,1);
        if (!at_6a) {
            TextureState(3,1,1);
        } else {
            TextureState(3,1,19);
            TextureState(3,2,2);
            TextureState(3,3,1);
            TextureState(3,4,2);
            TextureState(3,5,2);
            TextureState(3,6,1);
        }
        RenderState(23,4);
        RenderState(14,0);
        TextureState(0,11,0x20000);
        TextureState(0,24,2);
        TextureState(2,11,0x20000);
        TextureState(2,24,2);
        if (!at_6a) {
            TextureState(3,24,0);
        } else {
            TextureState(3,11,0x20000);
            TextureState(3,24,2);
        }

        D3DXMATRIX view, inverse, offset, scaling, rotation, center, diagonalShift;
        D3DXMATRIX negativeCenter, partial, combined;
        float determinant;
        GetTransform(2,view);
        D3DXMatrixInverse(&inverse,&determinant,&view);
        Identity(offset);
        int width = g_va012F7FE0->at_2ff4->at_08;
        int height = g_va012F7FE0->at_2ff4->at_0c;
        bool sameFrame = false;
        if (at_e4 == g_va012F0898->at_3c) sameFrame = true;
        at_e4 = g_va012F0898->at_3c;
        if (!sameFrame) at_38 += ((Rva0040B2E0 *)g_va012F1104)->scale();
        if (at_38 > 1.0f) at_38 = 1.0f;
        // Match the two witnessed float-rounding boundaries around fsqrt.
        volatile float diagonalSquared = (float)(height*height + width*width);
        volatile float diagonal = (float)sqrt(diagonalSquared);
        offset._41 -= diagonal * at_38 * 10.0f;
        float scaledWidth = (float)width * 10.0f;
        float scaledHeight = (float)height * 10.0f;
        D3DXMatrixScaling(&scaling,1.0f/scaledWidth,1.0f/scaledHeight,1.0f);
        D3DXMatrixRotationZ(&rotation,g_va012F1104->at_18);
        float centerX = scaledWidth * 0.5f;
        float centerY = scaledHeight * 0.5f;
        D3DXMatrixTranslation(&center,centerX,centerY,0.0f);
        D3DXMatrixTranslation(&diagonalShift,diagonal*5.0f,0.0f,0.0f);
        Identity(negativeCenter);
        negativeCenter._41 = scaledWidth * -0.5f;
        negativeCenter._42 = scaledHeight * -0.5f;
        partial = Multiply(negativeCenter,rotation);
        combined = Multiply(partial,center);
        partial = Multiply(combined,diagonalShift);
        D3DXMATRIX textureMatrix = Multiply(partial,offset);
        D3DXMATRIX scaledTexture = Multiply(textureMatrix,scaling);
        view = Multiply(inverse,scaledTexture);
        SetTransform(18,view);
        at_94 = textureMatrix;
        D3DXMatrixInverse(&textureMatrix,&determinant,&textureMatrix);
        D3DXVECTOR3 point;
        D3DXVECTOR4 transformed;
        point.x = (float)width * 0.5f * 10.0f;
        point.y = (float)height * 0.5f * 10.0f;
        point.z = 0.0f;
        D3DXVec3Transform(&transformed,&point,&textureMatrix);
        at_6c.x = transformed.x;
        at_6c.y = transformed.y;
        at_6c.z = transformed.z;
        at_78.x = textureMatrix._11;
        at_78.y = textureMatrix._12;
        at_78.z = textureMatrix._21; // retail loads matrix byte offset 0x10 at 0x006E4758
        D3DXPlaneFromPointNormal(&at_84,&at_6c,&at_78);

        int elapsed = g_va0133F420 - at_44;
        at_44 = g_va0133F420;
        if (sameFrame) elapsed = 0;
        Rva006E1C80Pair velocity;
        ((Rva006E1C80Owner *)g_va012F1104)->copyTo(&velocity);
        volatile float delta = (float)elapsed; // retail rounds at 0x006E47A5
        at_4c += *(float *)&velocity.first * delta * 0.002f;
        at_50 += *(float *)&velocity.second * delta * 0.002f;
        while (at_4c > 1.0f) at_4c -= 1.0f;
        while (at_50 > 1.0f) at_50 -= 1.0f;
        while (at_4c < -1.0f) at_4c += 1.0f;
        while (at_50 < -1.0f) at_50 += 1.0f;
        D3DXMATRIX scrolling;
        D3DXMatrixTranslation(&scrolling,at_4c,at_50,0.0f);
        D3DXMatrixScaling(&scaling,1.0f/315.0f,1.0f/315.0f,1.0f);
        partial = Multiply(inverse,scaling);
        view = Multiply(partial,scrolling);
        SetTransform(16,view);

        if (at_6a) {
            at_d4 = centerX;
            at_d8 = centerY;
            D3DXMATRIX translated;
            D3DXMatrixTranslation(&translated,-centerX,-centerY,0.0f);
            D3DXMATRIX half;
            D3DXMatrixTranslation(&half,0.5f,0.5f,0.0f);
            // qword constant at VA 0x0111E2C0 is double(float(0.15f)).
            at_40 = (float)(g_va012F1104->at_24 + at_3c*0.1f + at_3c*at_3c*(double)0.15f);
            if (!at_68) {
                if (at_40 > 100.0f) at_40 = 100.0f;
                else if (!sameFrame) at_3c += g_va012F1104->at_28;
            }
            float sx = 1.0f / (at_40 * 128.0f);
            float sy = 1.0f / (at_40 * 128.0f);
            D3DXMatrixScaling(&scaling,sx,sy,1.0f);
            D3DXMATRIX shifted = Multiply(inverse,translated);
            D3DXMATRIX resized = Multiply(shifted,scaling);
            view = Multiply(resized,half);
            SetTransform(19,view);
            at_e0 = at_40 * 64.0f;
        }
        RenderState(27,1);
        RenderState(19,1);
        RenderState(20,3);
        at_68 = 1;
    } else if (g_va012BA938 == 2) {
        unsigned frame = g_va012F1464->slot68();
        bool sameFrame = false;
        if (at_e4 == frame) sameFrame = true;
        at_e4 = frame;
        Rva012F1104View *config = g_va012F1104;
        if (config->at_b0 == 1) {
            if (!sameFrame) --config->at_b4;
            if (config->at_b4 <= 0) {
                config->at_b4 = 0;
                config->at_b0 = 2;
            }
        } else if (config->at_b0 == 3) {
            if (!sameFrame) ++config->at_b4;
            if (config->at_b4 >= 255) {
                config->at_b4 = 255;
                config->at_b0 = 0;
            }
        }
        if (!at_58) {
            AssignTexture(at_58,BFMEGetWaterTrackTexture((char *)((Rva006E2220 *)g_va012F1104)->copyString().str(),0,0));
            ConfigureTexture(at_58,0);
        }
        if (!at_5c) {
            AssignTexture(at_5c,BFMEGetWaterTrackTexture((char *)((Rva006E2250 *)g_va012F1104)->copyString().str(),0,0));
            ConfigureTexture(at_5c,0);
        }
        BoxSetTexture(0,g_va012F0FE0->at_0c == 1 ? at_5c : at_58);
        TextureState(0,1,7);
        TextureState(0,2,2);
        TextureState(0,3,3);
        TextureState(0,4,7);
        TextureState(0,5,2);
        TextureState(0,6,3);
        SamplerState(0,6,2);
        SamplerState(0,5,2);
        SamplerState(0,7,2);
        TextureState(0,11,0x20000);
        TextureState(0,24,2);
        D3DXMATRIX view, inverse, scaling, scrolling;
        float determinant;
        GetTransform(2,view);
        D3DXMatrixInverse(&inverse,&determinant,&view);
        int elapsed = g_va0133F420 - at_44;
        at_44 = g_va0133F420;
        if (sameFrame) elapsed = 0;
        Rva006E1C80Pair velocity;
        ((Rva006E1C80Owner *)g_va012F1104)->copyTo(&velocity);
        float delta = (float)elapsed;
        at_4c += *(float *)&velocity.first * delta * 0.001f;
        at_50 += delta * *(float *)&velocity.second * 0.001f;
        while (at_4c > 1.0f) at_4c -= 1.0f;
        while (at_50 > 1.0f) at_50 -= 1.0f;
        while (at_4c < -1.0f) at_4c += 1.0f;
        while (at_50 < -1.0f) at_50 += 1.0f;
        D3DXMatrixTranslation(&scrolling,at_4c,at_50,0.0f);
        D3DXMatrixScaling(&scaling,1.0f/1280.0f,1.0f/1280.0f,1.0f);
        view = Multiply(Multiply(inverse,scaling),scrolling);
        SetTransform(16,view);
        RenderState(23,4);
        RenderState(14,0);
        TextureState(1,1,1);
        TextureState(1,4,1);
        RenderState(15,1);
        RenderState(24,config->at_b4);
        RenderState(25,7);
        RenderState(26,1);
        RGBColor color;
        color.red = color.green = color.blue = (float)config->at_b4 * (1.0f/255.0f);
        RenderState(60,color.getAsInt() | 0xff000000);
        RenderState(27,1);
        RenderState(19,1);
        RenderState(20,3);
        at_68 = 1;
    }
}
