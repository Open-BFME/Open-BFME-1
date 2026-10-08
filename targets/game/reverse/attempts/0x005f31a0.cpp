// ?method@Rva005F31A0@@QAEHAAVRenderInfoClass@@PBVAABoxClass@@PAH@Z
// partial score=0.999 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Retail 0x005F31A0 has an integer return and three stack arguments.
// The owner and the system fields retain address-derived identities.
#include "vector3.h"
#include "vector4.h"
#include "sharebuf.h"
#include "pointgr.h"
#include "texture.h"
#include "aabox.h"
#include "ascii_string.h"

extern ShareBufferClass<Vector3> *g_vector3Buffer;
extern ShareBufferClass<Vector4> *g_vector4Buffer;
extern ShareBufferClass<float> *g_floatBuffer;
extern ShareBufferClass<unsigned char> *g_byteBuffer;
extern PointGroupClass *TheBfmeSecondManager;

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
class Rva009120F0FlagBit {
public:
    void setFlag(unsigned char value);
};
class Rva00917E10 {
public:
    void method(RenderInfoClass &info, unsigned int depth, int argument);
};
class Particle {
public:
    bool isInvisible();
    unsigned char m_before001C[0x1C];
    Vector3 m_field001C;
    unsigned char m_before003C[0x14];
    Particle *m_field003C;
};
class ParticleSystem {
public:
    unsigned char m_before0008[8];
    int m_field0008;
    int m_field000C;
    AsciiString m_field0010;
    unsigned char m_before007C[0x68];
    int m_field007C;
    bool m_field0080;
    unsigned char m_before0084[3];
    int m_field0084;
    unsigned char m_before00A0[0x18];
    Particle *m_field00A0;
};
extern ParticleSystem *Make00001B18();
class Rva005F31A0SystemHandle {
public:
    ParticleSystem *operator->() const {
        return m_pointer ? m_pointer : Make00001B18();
    }
    ParticleSystem *m_pointer;
};
class BFMEWaterTrackTextureHandle {
public:
    ~BFMEWaterTrackTextureHandle() {
        if (m_texture) m_texture->Release_Ref();
    }
    TextureClass *m_texture;
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);

class Rva005F31A0 {
public:
    int method(RenderInfoClass &info, const AABoxClass *box, int *output);
    unsigned char m_before0004[4];
    Rva005F31A0SystemHandle m_field0004;
};

// ?method@Rva005F31A0@@QAEHAAVRenderInfoClass@@PBVAABoxClass@@PAH@Z
int Rva005F31A0::method(RenderInfoClass &info, const AABoxClass *box, int *output)
{
    Vector3 *positions = g_vector3Buffer->Get_Array();
    float *sizes = g_floatBuffer->Get_Array();
    Vector4 *colors = g_vector4Buffer->Get_Array();
    unsigned char *angles = g_byteBuffer->Get_Array();
    const float centerX = box->Center.X;
    const float centerY = box->Center.Y;
    const float centerZ = box->Center.Z;
    const float extentX = box->Extent.X;
    const float extentY = box->Extent.Y;
    const float extentZ = box->Extent.Z;
    int count = 0;
    for (Particle *particle = m_field0004->m_field00A0; particle; particle = particle->m_field003C) {
        if (particle->isInvisible()) continue;
        float size = reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C30A0();
        if (WWMath::Fabs(particle->m_field001C.X - centerX) > extentX + size) continue;
        if (WWMath::Fabs(particle->m_field001C.Y - centerY) > extentY + size) continue;
        if (WWMath::Fabs(particle->m_field001C.Z - centerZ) > extentZ + size) continue;
        *output += m_field0004->m_field007C == 11 && m_field0004->m_field0080;
        positions[count].X = particle->m_field001C.X;
        positions[count].Y = particle->m_field001C.Y;
        positions[count].Z = particle->m_field001C.Z;
        sizes[count] = size;
        const Vector3 *color = reinterpret_cast<const Vector3 *>(reinterpret_cast<Rva005C3180 *>(particle)->dispatch());
        if (color) {
            colors[count].X = color->X;
            colors[count].Y = color->Y;
            colors[count].Z = color->Z;
        } else {
            colors[count].X = 0.0f;
            colors[count].Y = 0.0f;
            colors[count].Z = 0.0f;
        }
        colors[count].W = reinterpret_cast<Rva005C3160Owner *>(particle)->Rva005C3160();
        angles[count] = static_cast<unsigned char>(reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C3120() * *reinterpret_cast<const float *>(0x011135A8));
        if (++count == 512) break;
    }
    if (count > 0) {
        BFMEWaterTrackTextureHandle texture = BFMEGetWaterTrackTexture(const_cast<char *>(m_field0004->m_field0010.str()), 0, 0);
        if (TheBfmeSecondManager) {
            TheBfmeSecondManager->Set_Texture(reinterpret_cast<TextureClass *>(&texture));
            TheBfmeSecondManager->Set_Flag(PointGroupClass::TRANSFORM, true);
            switch (m_field0004->m_field0008) {
                case 1: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E2C)); break;
                case 2: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E30)); break;
                case 3: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E34)); break;
                case 4: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E48)); break;
                case 5: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E60)); break;
                case 6: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E24)); break;
                case 7: TheBfmeSecondManager->Set_Shader(*reinterpret_cast<const ShaderClass *>(0x012D6E28)); break;
            }
            TheBfmeSecondManager->Set_Point_Mode(PointGroupClass::QUADS);
            TheBfmeSecondManager->Set_Arrays(g_vector3Buffer, g_vector4Buffer, 0, g_floatBuffer, g_byteBuffer, 0, count);
            reinterpret_cast<Rva009120F0FlagBit *>(TheBfmeSecondManager)->setFlag(!m_field0004->m_field0080);
            if ((m_field0004->m_field000C == 4 ? 6u : 0u) > 1)
                reinterpret_cast<Rva00917E10 *>(TheBfmeSecondManager)->method(info, m_field0004->m_field000C == 4 ? 6u : 0u, reinterpret_cast<int>(&m_field0004->m_field0084));
            else
                TheBfmeSecondManager->Render(info, reinterpret_cast<int>(&m_field0004->m_field0084));
        }
    }
    return count;
}
