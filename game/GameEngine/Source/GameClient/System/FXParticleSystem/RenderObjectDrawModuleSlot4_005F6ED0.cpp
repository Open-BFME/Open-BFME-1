// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
#include "WWMath/matrix3.h"
#include "WWMath/matrix3d.h"
#include "WWMath/matrix4.h"
#include "WWMath/aabox.h"
#include "WW3D2/rendobj.h"

class Particle { public: bool isInvisible(); };
class Rva005C30A0Owner {
public:
    float Rva005C30C0() const;
    float Rva005C30E0() const;
    float Rva005C3100() const;
    float Rva005C3120() const;
};
class Rva005C3160Owner { public: float Rva005C3160() const; };
class Rva005C3180 { public: int dispatch() const; };
class Rva005C3140 { public: int query() const; };

struct Rva005F6ED0Particle;
class ParticleSystemZA {
public:
    unsigned char field00[8];
    unsigned int field08;
    unsigned char field0C[0x70];
    unsigned int field7C;
    bool field80;
    unsigned char field81[0x1F];
    Rva005F6ED0Particle *fieldA0;
    unsigned char fieldA4[0x1C];
    Matrix3D fieldC0;
    unsigned char fieldF0[0xB4];
    bool field1A4;
};
ParticleSystemZA *bfmeNullSystemZA();

struct Rva005F6ED0Particle {
    unsigned char field00[0x10];
    Vector3 field10;
    Vector3 field1C;
    unsigned char field28[0x14];
    Rva005F6ED0Particle *field3C;
    unsigned char field40[0xC];
    ParticleSystemZA *field4C;
    unsigned char field50[0x20];
    RenderObjClass *field70;
    unsigned int field74;
    ParticleSystemZA *system() const { return field4C ? field4C : bfmeNullSystemZA(); }
};

struct Coord3D;
class TerrainLogic;

class Rva005F6ED0Terrain {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual float slot18(float, float, Coord3D *) const;
};
extern TerrainLogic *TheTerrainLogic;
extern const float Rva0109BF40ZeroRange;

extern "C" Matrix4 *__stdcall D3DXMatrixRotationX(Matrix4 *, float);
extern "C" Matrix4 *__stdcall D3DXMatrixRotationY(Matrix4 *, float);
void ji_009fb93b();
extern "C" Matrix4 *__stdcall D3DXMatrixRotationAxis(Matrix4 *, const Vector3 *, float);
bool Rva007397E0(void *, float, float, float);
unsigned char Rva00739900ForwardSub(void *, float);
bool Rva00739A10(void *, float, float, float);

class Rva005F6ED0 {
public:
    int slot4(RenderInfoClass &, const AABoxClass &, int *);
    void *field00;
    ParticleSystemZA *field04;
    unsigned char field08[0x14];
    bool field1C;
    unsigned char field1D[3];
    float field20;
    bool field24;
    ParticleSystemZA *system() const { return field04 ? field04 : bfmeNullSystemZA(); }
};

// ?slot4@Rva005F6ED0@@QAEHAAVRenderInfoClass@@ABVAABoxClass@@PAH@Z
int Rva005F6ED0::slot4(RenderInfoClass &, const AABoxClass &bounds, int *counter)
{
    int count = 0;
    float centerX = bounds.Center.X;
    float centerY = bounds.Center.Y;
    float centerZ = bounds.Center.Z;
    float extentX = bounds.Extent.X;
    float extentY = bounds.Extent.Y;
    float extentZ = bounds.Extent.Z;
    Rva005F6ED0Particle *particle = system()->fieldA0;
    for (; particle; particle = particle->field3C) {
        if (reinterpret_cast<Particle *>(particle)->isInvisible())
            continue;
        float scaleX = reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C30C0();
        float scaleY = reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C30E0();
        float scaleZ = reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C3100();
        if (WWMath::Fabs(particle->field1C.X - centerX) > scaleX + extentX)
            continue;
        if (WWMath::Fabs(particle->field1C.Y - centerY) > scaleY + extentY)
            continue;
        bool below = false;
        if (field1C) {
            if (particle->field1C.Z - scaleZ > centerZ + extentZ)
                continue;
            float positionZ = particle->field1C.Z;
            if (reinterpret_cast<Rva005F6ED0Terrain *>(TheTerrainLogic)->slot18(particle->field1C.X, particle->field1C.Y, 0) > positionZ)
                below = true;
        } else if (WWMath::Fabs(particle->field1C.Z - centerZ) > scaleZ + extentZ) {
            continue;
        }
        *counter += system()->field7C == 11 && system()->field80 ? 1 : 0;
        const Vector3 *color = reinterpret_cast<const Vector3 *>(reinterpret_cast<Rva005C3180 *>(particle)->dispatch());
        float opacity = reinterpret_cast<Rva005C3160Owner *>(particle)->Rva005C3160();
        int rotationType = reinterpret_cast<Rva005C3140 *>(particle)->query();
        float rotation = reinterpret_cast<Rva005C30A0Owner *>(particle)->Rva005C3120();
        Matrix4 rotation4;
        if (rotationType == 4)
            reinterpret_cast<Matrix4 *(__stdcall *)(Matrix4 *, float)>(ji_009fb93b)(&rotation4, rotation);
        else if (rotationType == 2)
            D3DXMatrixRotationX(&rotation4, rotation);
        else if (rotationType == 3)
            D3DXMatrixRotationY(&rotation4, rotation);
        else if (rotationType == 5) {
            Vector3 axis(particle->field10.X, -particle->field10.Y, particle->field10.Z);
            D3DXMatrixRotationAxis(&rotation4, &axis, rotation);
        }
        if (particle->field70) {
            Matrix3D transform(particle->system()->fieldC0);
            if (below) {
                transform[2][3] += field20;
            } else {
                if (rotationType != 1) {
                    Matrix3 rot(rotation4);
                    if (!particle->system()->field1A4) {
                        Matrix3 original(transform);
                        rot = original * rot;
                    }
                    transform.Set_Rotation(rot);
                }
                if (scaleX < Rva0109BF40ZeroRange) scaleX = 0.0001f;
                if (scaleY < Rva0109BF40ZeroRange) scaleY = 0.0001f;
                if (scaleZ < Rva0109BF40ZeroRange) scaleZ = 0.0001f;
                if (scaleX != 1.0f || scaleY != 1.0f || scaleZ != 1.0f)
                    transform.Scale(scaleX, scaleY, scaleZ);
                transform.Set_Translation(Vector3(particle->field1C.X, particle->field1C.Y, particle->field1C.Z));
            }
            particle->field70->Set_Transform(transform);
            unsigned int materialMode = field24 ? particle->field74 : system()->field08;
            switch (materialMode) {
            case 10:
                Rva007397E0(particle->field70, opacity * color->X, opacity * color->Y, opacity * color->Z);
                break;
            case 9:
                Rva00739900ForwardSub(particle->field70, opacity);
                break;
            case 8:
                Rva00739A10(particle->field70, opacity * color->X, opacity * color->Y, opacity * color->Z);
                break;
            }
            if (particle->field70->Is_Hidden())
                particle->field70->Set_Hidden(0);
        }
        if (++count == 512)
            break;
    }
    return count;
}
