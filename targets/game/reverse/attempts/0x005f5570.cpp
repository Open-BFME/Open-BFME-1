// ?slot4@QuadDrawModule@FXParticleSystem@@UAEHPAXPBMPAH@Z
// partial score=0.697 date=2026-09-28
// cl: /Igame/Libraries/Source/WWVegas/WWDebug /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2
// QuadDrawModule slot 4, retail 0x005F5570. The owner and slot are proven by vtable 0x01111E2C.

#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "sharebuf.h"
#include "texture.h"

typedef char Char;
typedef unsigned int UInt;

class Particle
{
public:
	bool isInvisible();
};

class ParticleSystemZA
{
};

class Gen00001B18;
Gen00001B18 *Make00001B18();

class Rva005C30A0Owner
{
public:
	float Rva005C30A0() const;
	float Rva005C3120() const;
};

class Rva005C3160Owner
{
public:
	float Rva005C3160() const;
};

class Rva005C3140
{
public:
	int query() const;
};

class Rva005C3180
{
public:
	int dispatch() const;
};

class Rva0090F8C0Holder
{
public:
	void set(int count, RefCountClass *a, RefCountClass *b,
		RefCountClass *c, RefCountClass *d);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((TextureClass *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, int mipCount, int format);

class Gen0090F680
{
public:
	RefCountClass *m_00;
	RefCountClass *m_04;
	RefCountClass *m_08;
	RefCountClass *m_0c;
	int m_10;
	TextureClass *m_14;
	RefCountClass *m_18;
};

extern Gen0090F680 *TheGen012F6DFC;

class DX8Wrapper
{
public:
	static unsigned render_state_changed;
};

void ji_009fb802();
void ji_009fb89e();
void ji_009fb93b();
void ji_009fb9f7();
class RenderRva0090FEE0 { public: void render(void *arg); };

namespace FXParticleSystem
{

class QuadDrawModule
{
public:
	virtual ~QuadDrawModule();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int slot4(void *arg1, const float *bounds, int *counter);
    ParticleSystemZA *getSystem() const { ParticleSystemZA *p = *(ParticleSystemZA **)((char *)this + 4); return p ? p : (ParticleSystemZA *)Make00001B18(); }
};

int QuadDrawModule::slot4(void *arg1, const float *bounds, int *counter)
{

    Vector3 *positions = (*(ShareBufferClass<Vector3> **)0x012F6DC8)->Get_Array();
    Vector4 *colours = (*(ShareBufferClass<Vector4> **)0x012F6DCC)->Get_Array();
    Vector3 center, extent;
    center.X=bounds[0]; center.Y=bounds[1]; center.Z=bounds[2];
    extent.X=bounds[3]; extent.Y=bounds[4]; extent.Z=bounds[5];
    int count = 0;
    Matrix4 matrix;
    if (DX8Wrapper::render_state_changed & 0x80000) matrix.Make_Identity();
    else {
        matrix[0][0] = *(float *)0x013410CC;
        matrix[0][1] = *(float *)0x013410DC;
        matrix[0][2] = *(float *)0x013410EC;
        matrix[0][3] = *(float *)0x013410FC;
        matrix[1][0] = *(float *)0x013410D0;
        matrix[1][1] = *(float *)0x013410E0;
        matrix[1][2] = *(float *)0x013410F0;
        matrix[1][3] = *(float *)0x01341100;
        matrix[2][0] = *(float *)0x013410D4;
        matrix[2][1] = *(float *)0x013410E4;
        matrix[2][2] = *(float *)0x013410F4;
        matrix[2][3] = *(float *)0x01341104;
    }
    Particle *particle = *(Particle **)((char *)getSystem()+0xA0);
    while (particle) {
        if (!particle->isInvisible()) {
            float radius = ((Rva005C30A0Owner *)particle)->Rva005C30A0();
            float angle = ((Rva005C30A0Owner *)particle)->Rva005C3120();
            const Vector3 &position = *(Vector3 *)((char *)particle+0x1c);
            if (WWMath::Fabs(position.X-center.X) <= radius+extent.X &&
                WWMath::Fabs(position.Y-center.Y) <= radius+extent.Y &&
                WWMath::Fabs(position.Z-center.Z) <= radius+extent.Z) {
                int flagged = *(int *)((char *)getSystem()+0x7c)==11 && *(unsigned char *)((char *)getSystem()+0x80);
                *counter += flagged;
                Vector4 a(-radius,0.0f,radius,1.0f), b(radius,0.0f,radius,1.0f);
                Vector4 c(-radius,0.0f,-radius,1.0f), d(radius,0.0f,-radius,1.0f);
                Matrix4 rotation;
                int query = ((Rva005C3140 *)particle)->query();
                if (query==4) ((void (__stdcall *)(Matrix4 *,float))ji_009fb93b)(&rotation,angle);
                else if (query==2) ((void (__stdcall *)(Matrix4 *,float))ji_009fb802)(&rotation,angle);
                else if (query==3) ((void (__stdcall *)(Matrix4 *,float))ji_009fb89e)(&rotation,angle);
                else if (query==5) {
                    const Vector3 &axis0=*(Vector3 *)((char *)particle+0x10);
                    Vector3 axis(axis0.X,-axis0.Y,axis0.Z);
                    ((void (__stdcall *)(Matrix4 *,const Vector3 *,float))ji_009fb9f7)(&rotation,&axis,angle);
                } else rotation.Make_Identity();
                a=rotation*a; b=rotation*b; c=rotation*c; d=rotation*d;
                Vector3 particlePosition = position;
                a.X+=particlePosition.X; a.Y+=particlePosition.Y; a.Z+=particlePosition.Z;
                positions[0].X=matrix[0]*a; positions[0].Y=matrix[1]*a; positions[0].Z=matrix[2]*a;
                b.X+=particlePosition.X; b.Y+=particlePosition.Y; b.Z+=particlePosition.Z;
                positions[1].X=matrix[0]*b; positions[1].Y=matrix[1]*b; positions[1].Z=matrix[2]*b;
                c.X+=particlePosition.X; c.Y+=particlePosition.Y; c.Z+=particlePosition.Z;
                positions[2].X=matrix[0]*c; positions[2].Y=matrix[1]*c; positions[2].Z=matrix[2]*c;
                d.X+=particlePosition.X; d.Y+=particlePosition.Y; d.Z+=particlePosition.Z;
                positions[3].X=matrix[0]*d; positions[3].Y=matrix[1]*d; positions[3].Z=matrix[2]*d;
                Vector3 *rgb=(Vector3 *)((Rva005C3180 *)particle)->dispatch();
                float alpha=((Rva005C3160Owner *)particle)->Rva005C3160();
                if (rgb) for (int i=0;i<4;++i) colours[i].Set(rgb->X,rgb->Y,rgb->Z,alpha);
                else for (int i=0;i<4;++i) colours[i].Set(0.0f,0.0f,0.0f,alpha);
                ++count; positions+=4; colours+=4;
                if (count==512) break;
            }
        }
        particle=*(Particle **)((char *)particle+0x3c);
    }

	if (count <= 0)
		return count;

	{
		Char *name = *(Char **)((char *)getSystem() + 0x10);
		BFMEWaterTrackTextureHandle texture =
			BFMEGetWaterTrackTexture(name ? name + 8 : (Char *)0x0107388b, 0, 0);
		if (TheGen012F6DFC)
		{
			if (texture.m_texture) texture.m_texture->Add_Ref();
            if (TheGen012F6DFC->m_14)
				TheGen012F6DFC->m_14->Release_Ref();
			TheGen012F6DFC->m_14 = texture.m_texture;
			switch (*(int *)((char *)getSystem() + 8) - 1)
			{
				case 0:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E2C;
					break;
				case 1:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E30;
					break;
				case 2:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E34;
					break;
				case 3:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E48;
					break;
				case 4:
                    TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E60;
                    break;
                case 5:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E24;
					break;
				case 6:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E28;
					break;
			}
			((Rva0090F8C0Holder *)TheGen012F6DFC)->set(count,
				*(RefCountClass **)0x012F6DC8,
				*(RefCountClass **)0x012F6DCC, 0, 0);
			((RenderRva0090FEE0 *)TheGen012F6DFC)->render(arg1);
		}
		return count;
	}
}

}
