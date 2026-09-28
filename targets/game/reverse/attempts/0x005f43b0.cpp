// ?draw@LightningDraw005F43B0@@QAEHPAX0PAH@Z
// partial score=0.967 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System /Iinputs/reference/shims/sweep
#include <stddef.h>
#include "vector3.h"
#include "vector4.h"
#include "sharebuf.h"
#include "coord3d.h"
#include "game_client_random_variable.h"

// Candidate symbol: ?draw@LightningDraw005F43B0@@QAEHPAX0PAH@Z
// Not landed: 2220-byte compiled body; 50 masked differing bytes; shape 0.967.
// Residue: x87 memory-operand order in both cross products and the first
// offset term (+0x2A0..+0x31F, +0x3C3..+0x3DA). No inline assembly.
// Intended home: game/GameEngine/Source/GameClient/System/FXParticleSystem/.
// Retail 005F43B0: LightningDrawModule primary vtable 01112FD0 slot +10,
// installed by the verified ctor 005F4E90. The method spelling is unproven.
// Layout below is offset-derived from this body and that constructor.
// Renderer callees use their landed symbols except 00918DA0, whose landed
// spelling takes int while this caller passes a copy-constructed shader word.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();
class Rva005C30A0Owner { public: float Rva005C30A0() const; float Rva005C3120() const; };
class Rva005C3160Owner { public: float Rva005C3160() const; };
class Rva005C3180 { public: int dispatch() const; };
class TextureClass { public: void Release_Ref(); }; // 009EB7A0
class BFMEWaterTrackTexture : public TextureClass {};
class BFMEWaterTrackTextureHandle {
public:
    TextureClass *m_texture;
    ~BFMEWaterTrackTextureHandle() { if(m_texture) ((BFMEWaterTrackTexture*)m_texture)->Release_Ref(); }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class RefCountClass;
extern RefCountClass *g_rva005F4340Resource;
extern ShareBufferClass<Vector3> *g_vector3Buffer;
extern ShareBufferClass<Vector4> *g_vector4Buffer;
extern ShareBufferClass<float> *g_floatBuffer;
extern ShareBufferClass<unsigned char> *g_byteBuffer;

// These typed declarations record the actual caller ABI. Historical names
// at 9182C0/9182F0/91A480 have misleading pointer/value parameter types.
struct ShaderWord005F43B0 {
    unsigned value;
    ShaderWord005F43B0(const ShaderWord005F43B0& v) : value(v.value) {}
};
extern ShaderWord005F43B0 shader012D6E2C,shader012D6E30,shader012D6E34,
    shader012D6E48,shader012D6E60,shader012D6E24,shader012D6E28;
class StreakLineClass { public: void Set_Texture(TextureClass *texture); }; // 009182C0
struct BfmeThingDUC { void bfmeGoDUC(); }; // 00918290
class Rva00918DA0 { public: void set(int a); }; // 00918DA0
class BfmeStreakUGB { public: void bfmeSetUGB(unsigned n,void *locs,void *widths,void *colors,int stamp); }; // 0091A480
class BfmeThingCBA { public: void bfmeGoCBA(void *what); }; // 009182F0
typedef void (BfmeThingCBA::*TileSetter005F43B0)(float);
class StreakCalls005F43B0 {
public:
    // ?texture@StreakCalls005F43B0@@QAEXABVBFMEWaterTrackTextureHandle@@@Z absent-from-retail
    void texture(const BFMEWaterTrackTextureHandle &h) { ((StreakLineClass*)this)->Set_Texture((TextureClass*)&h); }
    // ?reset@StreakCalls005F43B0@@QAEXXZ absent-from-retail
    void reset() { ((BfmeThingDUC*)this)->bfmeGoDUC(); }
    void shader(ShaderWord005F43B0); // 00918DA0: landed ?set@Rva00918DA0@@QAEXH@Z takes int; see handoff
    // ?points@StreakCalls005F43B0@@QAEXIPAX000@Z absent-from-retail
    void points(unsigned n,void *locs,void *widths,void *colors,void *stamps) { ((BfmeStreakUGB*)this)->bfmeSetUGB(n,locs,widths,colors,(int)stamps); }
    // ?tile@StreakCalls005F43B0@@QAEXM@Z absent-from-retail
    void tile(float f) { (((BfmeThingCBA*)this)->*reinterpret_cast<TileSetter005F43B0>(&BfmeThingCBA::bfmeGoCBA))(f); }
};
class RenderSlots005F43B0 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void render(void*);
};
struct Particle005F43B0 {
    char bytes00[0x1c]; Vector3 field1c; char bytes28[0x14];
    Particle005F43B0 *field3c; char bytes40[0x18]; unsigned field58;
    char bytes5c[0xc]; unsigned field68; unsigned field6c;
};
struct System005F43B0 {
    char bytes00[8]; int field08; char bytes0c[4]; char *field10;
    char bytes14[0x68]; int field7c; bool field80;
    char bytes81[0x1f]; Particle005F43B0 *fielda0;
};
class LightningDraw005F43B0 {
public:
    int draw(void *renderInfo,void *unused,int *count);
    System005F43B0 *system() const { return field04 ? field04 : (System005F43B0*)bfmeNullSystemZA(); }
    char bytes00[4]; System005F43B0 *field04; char bytes08[0x14];
    GameClientRandomVariable field1c,field28,field34;
    float field40; bool field44; char bytes45[3];
    Vector3 field48[3][30]; Vector3 field480[3][30];
    int field8b8; Vector3 field8bc,field8c8,field8d4; unsigned field8e0;
};
typedef char Layout005F43B0[(sizeof(LightningDraw005F43B0)==0x8e4)?1:-1];
typedef char Check005F43B0System[(offsetof(System005F43B0,fielda0)==0xa0)?1:-1];
typedef char Check005F43B0Particle[(offsetof(Particle005F43B0,field6c)==0x6c)?1:-1];
typedef char Check005F43B0Points[(offsetof(LightningDraw005F43B0,field48)==0x48)?1:-1];
typedef char Check005F43B0Offsets[(offsetof(LightningDraw005F43B0,field480)==0x480)?1:-1];
typedef char Check005F43B0Axes[(offsetof(LightningDraw005F43B0,field8bc)==0x8bc)?1:-1];

// ?updateLightningPoint005F43B0@@YAXHHPAVVector3@@PBV1@1@Z absent-from-retail
inline void updateLightningPoint005F43B0(int k,int n,Vector3 *out, const Vector3 *offset, const Vector3 *base) {
 if(k!=0 && k!=n-1) Vector3::Add(*base,*offset,out); else *out=*offset;
}

int LightningDraw005F43B0::draw(void *renderInfo,void *unused,int *count)
{
    int n=0;
    Vector3 *positions=g_vector3Buffer->Get_Array();
    float *widths=g_floatBuffer->Get_Array();
    Vector4 *colors=g_vector4Buffer->Get_Array();
    unsigned char *bytes=g_byteBuffer->Get_Array();
    unsigned stamps[512];
    bool changed=false;
    unsigned stamp=1;
    Particle005F43B0 *p=system()->fielda0;
    if(p && field8e0!=p->field6c) {
        field8e0=p->field6c;
        changed=true;
        stamp=p->field68;
        if(WWMath::Random_Float()<field40) field8b8=2;
        else field8b8=1;
    }
    p=system()->fielda0;
    for(;p;p=p->field3c) {
        float width=((Rva005C30A0Owner*)p)->Rva005C30A0();
        if(changed) p->field68=stamp;
        *count += (system()->field7c==11 && system()->field80) ? 1 : 0;
        stamps[n]=p->field58;
        positions[n]=p->field1c;
        widths[n]=width;
        Vector3 *rgb=(Vector3*)((Rva005C3180*)p)->dispatch();
        if(rgb) { colors[n].X=rgb->X; colors[n].Y=rgb->Y; colors[n].Z=rgb->Z; }
        else { colors[n].X=0; colors[n].Y=0; colors[n].Z=0; }
        colors[n].W=((Rva005C3160Owner*)p)->Rva005C3160();
        bytes[n]=(unsigned char)(int)(((Rva005C30A0Owner*)p)->Rva005C3120()*40.58451080322265625f);
        if(++n==512) break;
    }
    if(g_rva005F4340Resource && n>=2) {
        char *text=system()->field10;
        BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture(text ? text+8 : "",0,0);
        if(changed) {
            Vector3 &along=field8bc; Vector3 *end=positions+n; along=Vector3(end[-1].X-positions[0].X,end[-1].Y-positions[0].Y,end[-1].Z-positions[0].Z);
            ((Coord3D*)&along)->normalize();
            field8d4.Z=1; field8d4.X=0; field8d4.Y=0;
            Vector3::Cross_Product(field8d4,along,&field8c8);
            Vector3::Cross_Product(along,field8c8,&field8d4);
            for(int j=0;j<field8b8;++j) {
                Vector3 *out=field48[j];
                Vector3 *offset=field480[j];
                for(int k=0;k<n;++k) {
                    if(k!=0 && k!=n-1) {
                        float a=field1c.getValue();
                        float b=field28.getValue();
                        float c=field34.getValue();
                        offset[k].X = a*field8c8.X+b*field8d4.X+c*field8bc.X;
                        offset[k].Y = a*field8c8.Y+b*field8d4.Y+c*field8bc.Y;
                        offset[k].Z = a*field8c8.Z+b*field8d4.Z+c*field8bc.Z;
                        Vector3::Add(positions[k],offset[k],&out[k]);
                    } else {
                        out[k].X=offset[k].X=positions[k].X;
                        out[k].Y=offset[k].Y=positions[k].Y;
                        out[k].Z=offset[k].Z=positions[k].Z;
                    }
                }
            }
        } else {
            for(int j=0;j<field8b8;++j) {
                Vector3 *out=field48[j];
                Vector3 *offset=field480[j];
                for(int k=0;k<n;++k) {
                    if(k!=0 && k!=n-1) { out[k].X=positions[k].X+offset[k].X; out[k].Y=positions[k].Y+offset[k].Y; out[k].Z=positions[k].Z+offset[k].Z; }
                    else { out[k].X=offset[k].X; out[k].Y=offset[k].Y; out[k].Z=offset[k].Z; }
                }
            }
        }
        ((StreakCalls005F43B0*)g_rva005F4340Resource)->texture(texture);
        ((StreakCalls005F43B0*)g_rva005F4340Resource)->reset();
        switch(system()->field08) {
        case 1: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E2C); break;
        case 2: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E30); break;
        case 3: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E34); break;
        case 4: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E48); break;
        case 5: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E60); break;
        case 6: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E24); break;
        case 7: ((StreakCalls005F43B0*)g_rva005F4340Resource)->shader(shader012D6E28); break;
        }
        for(int j=0;j<field8b8;++j) {
            ((StreakCalls005F43B0*)g_rva005F4340Resource)->points(n,field48[j],g_floatBuffer->Get_Array(),g_vector4Buffer->Get_Array(),stamps);
            if(!field44) ((StreakCalls005F43B0*)g_rva005F4340Resource)->tile(1.0f/(n-1));
            else ((StreakCalls005F43B0*)g_rva005F4340Resource)->tile(1.0f);
            ((RenderSlots005F43B0*)g_rva005F4340Resource)->render(renderInfo);
        }
    }
    return n;
}
