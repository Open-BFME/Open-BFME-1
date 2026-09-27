// ?d_005f1370@@YAXXZ
// partial score=0.1432496075353218 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Unfinished native reconstruction, retail RVA005F1370 / 5096 bytes.
// Full algorithm recovered; frame, x87 scheduling and vector lifetimes differ.
// Evidence: targets/game/reverse/identity_evidence/005f1370-particle-geometry.md.
// No byte coverage claimed. No pins added. Canonical WWMath owns its x87 intrinsics.
#define Matrix4x4 Matrix4
#include "aabox.h"
#include "ascii_string.h"
#include "dx8wrapper.h"
#include "matrix4.h"
#include "sharebuf.h"
#include "texture.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

class Rva005C30A0Owner {
  public:
    float Rva005C30A0() const;
    float Rva005C3120() const;
};
class Rva005C3160Owner {
  public:
    float Rva005C3160() const;
};
class Rva005C3180 {
  public:
    int dispatch() const;
};
class Particle {
  public:
    bool isInvisible();
    unsigned char unknown00[0x10];
    Vector3 vector10;
    Vector3 vector1C;
    unsigned char unknown28[0x14];
    Particle *next3C;
};
class ParticleSystemZA {
  public:
    unsigned char unknown00[8];
    int field08;
    unsigned unknown0C;
    AsciiString name10;
    unsigned char unknown14[0x68];
    int field7C;
    bool field80;
    unsigned char unknown81[0x1F];
    Particle *firstA0;
};
ParticleSystemZA *bfmeNullSystemZA();

class BFMEWaterTrackTextureHandle {
  public:
    TextureBaseClass *texture;
    ~BFMEWaterTrackTextureHandle() {
        if (texture)
            texture->Release_Ref();
    }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *, int, int);

class Rva0090F8C0Holder {
  public:
    void set(int, RefCountClass *, RefCountClass *, RefCountClass *, RefCountClass *);
};
class Rva0090FEE0Renderer {
  public:
    void render(unsigned);
    ShareBufferClass<Vector3> *positions;
    ShareBufferClass<Vector4> *colors;
    ShareBufferClass<Vector3> *normals;
    ShareBufferClass<Vector2> *uvs;
    int count;
    TextureBaseClass *texture;
    ShaderClass shader;
    Vector4 defaultColor;
    void setTexture(TextureBaseClass *value) {
        if (value)
            ++*(unsigned short *)((char *)value + 4);
        if (texture)
            texture->Release_Ref();
        texture = value;
    }
};
typedef char Rva005F1370_ParticleNext[(offsetof(Particle, next3C) == 0x3C) ? 1 : -1];
typedef char Rva005F1370_SystemFirst[(offsetof(ParticleSystemZA, firstA0) == 0xA0) ? 1 : -1];
typedef char Rva005F1370_RendererLayout[(sizeof(Rva0090FEE0Renderer) == 0x2C) ? 1 : -1];
extern ShareBufferClass<Vector3> *Va012F6DC8;
extern ShareBufferClass<Vector4> *Va012F6DCC;
extern Rva0090FEE0Renderer *Va012F6D88;
extern ShaderClass Va012D6E30, Va012D6E34, Va012D6E48, Va012D6E60, Va012D6E24, Va012D6E28;
typedef D3DXMATRIX Rva005F1370Matrix;
// The retail call goes through D3DX9's runtime-selected MatrixRotationZ stub
// at009FB93B, whose dispatch slot012DBE78 initially targets init009FB91F.

class Rva005F1370Owner {
  public:
    int render(unsigned, const AABoxClass &, int *);
    unsigned unknown00;
    ParticleSystemZA *system04;
    ParticleSystemZA *system() const { return system04 ? system04 : bfmeNullSystemZA(); }
};

static __forceinline void Rotate5096(const Rva005F1370Matrix &m, Vector4 &p) { p = *(const Matrix4 *)&m * p; }
static __forceinline void Place5096(const Matrix4 &m, Vector4 &p, const Vector3 &position, Vector3 *out) {
    p.X += position.X;
    p.Y += position.Y;
    p.Z += position.Z;
    *out = Vector3(m[0][0] * p.X + m[0][1] * p.Y + m[0][2] * p.Z + m[0][3] * p.W,
                   m[1][0] * p.X + m[1][1] * p.Y + m[1][2] * p.Z + m[1][3] * p.W,
                   m[2][0] * p.X + m[2][1] * p.Y + m[2][2] * p.Z + m[2][3] * p.W);
}

int Rva005F1370Owner::render(unsigned info, const AABoxClass &box, int *fieldCount) {
    Vector3 *positions = Va012F6DC8->Get_Array();
    Vector4 *colors = Va012F6DCC->Get_Array();
    const float centerX = box.Center.X, centerY = box.Center.Y, centerZ = box.Center.Z;
    const float extentX = box.Extent.X, extentY = box.Extent.Y, extentZ = box.Extent.Z;
    int count = 0;
    Matrix4 view;
    DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
    for (Particle *p = system()->firstA0; p; p = p->next3C) {
        if (p->isInvisible())
            continue;
        const Vector3 *position = &p->vector1C;
        float size = ((Rva005C30A0Owner *)p)->Rva005C30A0();
        float angle = ((Rva005C30A0Owner *)p)->Rva005C3120();
        if (WWMath::Fabs(position->X - centerX) > extentX + size)
            continue;
        if (WWMath::Fabs(position->Y - centerY) > extentY + size)
            continue;
        if (WWMath::Fabs(position->Z - centerZ) > extentZ + size)
            continue;
        *fieldCount += (system()->field7C == 11 && system()->field80);
        float c = WWMath::Cos(angle);
        float height = c * size * 2.0f;
        if (height < -size)
            height = -size;
        float s = WWMath::Sin(angle);
        float spread = s * size * 2.0f;
        Vector4 vertices[8];
        vertices[0].Set(0.0f, size, 0.0f, 1.0f);
        vertices[1].Set(spread, size, height, 1.0f);
        vertices[2].Set(0.0f, -size, 0.0f, 1.0f);
        vertices[3].Set(spread, -size, height, 1.0f);
        vertices[4].Set(0.0f, size, 0.0f, 1.0f);
        vertices[5].Set(-spread, size, height, 1.0f);
        vertices[6].Set(0.0f, -size, 0.0f, 1.0f);
        vertices[7].Set(-spread, -size, height, 1.0f);
        if ((float)fabs(p->vector10.X) > 0.0001f) {
            Rva005F1370Matrix rotation;
            float z = (float)(atan2(-p->vector10.Y, p->vector10.X) - 1.5707963267948966);
            D3DXMatrixRotationZ(&rotation, z);
            Rotate5096(rotation, vertices[0]);
            Rotate5096(rotation, vertices[1]);
            Rotate5096(rotation, vertices[2]);
            Rotate5096(rotation, vertices[3]);
            Rotate5096(rotation, vertices[4]);
            Rotate5096(rotation, vertices[5]);
            Rotate5096(rotation, vertices[6]);
            Rotate5096(rotation, vertices[7]);
        }
        Place5096(view, vertices[0], *position, positions + 0);
        Place5096(view, vertices[1], *position, positions + 1);
        Place5096(view, vertices[2], *position, positions + 2);
        Place5096(view, vertices[3], *position, positions + 3);
        Place5096(view, vertices[4], *position, positions + 4);
        Place5096(view, vertices[5], *position, positions + 5);
        Place5096(view, vertices[6], *position, positions + 6);
        Place5096(view, vertices[7], *position, positions + 7);
        const Vector3 *rgb = (const Vector3 *)((Rva005C3180 *)p)->dispatch();
        float alpha = ((Rva005C3160Owner *)p)->Rva005C3160();
        Vector4 *color = colors;
        for (int i = 0; i < 8; ++i, ++color) {
            if (rgb) {
                color->X = rgb->X;
                color->Y = rgb->Y;
                color->Z = rgb->Z;
            } else {
                color->X = 0.0f;
                color->Y = 0.0f;
                color->Z = 0.0f;
            }
            color->W = alpha;
        }
        count += 2;
        positions += 8;
        colors += 8;
        if (count >= 512)
            break;
    }
    if (count < 1)
        return count;
    BFMEWaterTrackTextureHandle texture = BFMEGetWaterTrackTexture((char *)system()->name10.str(), 0, 0);
    if (Va012F6D88) {
        Va012F6D88->setTexture(texture.texture);
        switch (system()->field08) {
        case 1:
            Va012F6D88->shader = ShaderClass::_PresetAdditiveSpriteShader;
            break;
        case 2:
            Va012F6D88->shader = Va012D6E30;
            break;
        case 3:
            Va012F6D88->shader = Va012D6E34;
            break;
        case 4:
            Va012F6D88->shader = Va012D6E48;
            break;
        case 5:
            Va012F6D88->shader = Va012D6E60;
            break;
        case 6:
            Va012F6D88->shader = Va012D6E24;
            break;
        case 7:
            Va012F6D88->shader = Va012D6E28;
            break;
        }
        ((Rva0090F8C0Holder *)Va012F6D88)->set(count, Va012F6DC8, Va012F6DCC, 0, 0);
        Va012F6D88->render(info);
    }
    return count;
}
