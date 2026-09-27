// ?slot4@QuadDrawModule@FXParticleSystem@@UAEHPAXPBMPAH@Z
// partial score=0.36 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2
// QuadDrawModule slot 4, retail 0x005F5570. The owner and slot are proven by vtable 0x01111E2C.

#include "vector3.h"
#include "vector4.h"
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
void d_0090fee0(void *holder, void *arg);

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
};

int QuadDrawModule::slot4(void *arg1, const float *bounds, int *counter)
{
	float matrix[12];
	float local[24];
	float record[16];
	float corners[19];
	int count = 0;
	int modeFlag = 0;
	Particle *particle;
	ParticleSystemZA *system;
	QuadDrawModule *volatile self = this;
	Vector3 *positions;
	Vector4 *colours;

	positions = (*(ShareBufferClass<Vector3> **)0x012F6DC8)->Get_Array();
	colours = (*(ShareBufferClass<Vector4> **)0x012F6DCC)->Get_Array();

	*(unsigned int *)&local[0] = *(unsigned int *)((char *)bounds + 0);
	*(unsigned int *)&local[3] = *(unsigned int *)((char *)bounds + 4);
	*(unsigned int *)&local[2] = *(unsigned int *)((char *)bounds + 8);
	*(unsigned int *)&local[4] = *(unsigned int *)((char *)bounds + 12);
	*(unsigned int *)&local[1] = *(unsigned int *)((char *)bounds + 16);
	*(unsigned int *)&local[5] = *(unsigned int *)((char *)bounds + 20);

	if ((DX8Wrapper::render_state_changed & 0x80000) != 0)
	{
		matrix[0] = 1.0f;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[3] = 0.0f;
		matrix[4] = 0.0f;
		matrix[5] = 1.0f;
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;
		matrix[8] = 0.0f;
		matrix[9] = 0.0f;
		matrix[10] = 1.0f;
		matrix[11] = 0.0f;
	}
	else
	{
		matrix[0] = *(float *)0x013410CC;
		matrix[1] = *(float *)0x013410D0;
		matrix[2] = *(float *)0x013410D4;
		matrix[3] = *(float *)0x013410D8;
		matrix[4] = *(float *)0x013410DC;
		matrix[5] = *(float *)0x013410E0;
		matrix[6] = *(float *)0x013410E4;
		matrix[7] = *(float *)0x013410E8;
		matrix[8] = *(float *)0x013410EC;
		matrix[9] = *(float *)0x013410F0;
		matrix[10] = *(float *)0x013410F4;
		matrix[11] = *(float *)0x013410F8;
	}

	system = *(ParticleSystemZA **)((char *)self + 4);
	if (!system)
		system = (ParticleSystemZA *)Make00001B18();
	particle = *(Particle **)((char *)system + 0xA0);

	while (particle && count < 0x200)
	{
		float *p = (float *)particle;
		float px;
		float py;
		float pz;
		float radius;
		float left;
		float right;
		float top;
		float bottom;
		float depth;
		float half;
		float uv;
		int query;
		int i;
		int j;
		void *colour;

		if (!particle->isInvisible())
		{
			px = p[4];
			py = p[5];
			pz = p[6];
			left = p[7] + ((Rva005C30A0Owner *)particle)->Rva005C30A0();
			right = p[8] + ((Rva005C30A0Owner *)particle)->Rva005C3120();
			depth = p[9];
			if (left >= local[0] && left <= local[3] &&
				right >= local[1] && right <= local[4] &&
				depth >= local[2] && depth <= local[5])
			{
				if (*(int *)((char *)system + 0x7c) == 0x0b &&
					*(unsigned char *)((char *)system + 0x80) != 0)
					modeFlag = 1;

				radius = ((Rva005C30A0Owner *)particle)->Rva005C30A0();
				half = radius * 0.5f;
				if (counter)
					*counter += modeFlag;

				query = ((Rva005C3140 *)particle)->query();
				if (query == 4)
					((void (__cdecl *)(void *, void *))ji_009fb93b)(record, (void *)bounds);
				else if (query == 2)
					((void (__cdecl *)(void *, void *))ji_009fb802)(record, (void *)bounds);
				else if (query == 3)
					((void (__cdecl *)(void *, void *))ji_009fb89e)(record, (void *)bounds);
				else if (query == 5)
				{
					record[0] = p[4];
					record[1] = p[5];
					record[2] = p[6];
					record[3] = -local[2];
					((void (__cdecl *)(void *, void *))ji_009fb9f7)(record, &record[4]);
				}
				else
				{
					record[0] = 1.0f;
					record[1] = 0.0f;
					record[2] = 0.0f;
					record[3] = 0.0f;
					record[4] = 0.0f;
					record[5] = 1.0f;
					record[6] = 0.0f;
					record[7] = 0.0f;
					record[8] = 0.0f;
					record[9] = 0.0f;
					record[10] = 1.0f;
					record[11] = 0.0f;
				}

				uv = ((Rva005C3160Owner *)particle)->Rva005C3160();
				colour = (void *)(UInt)((Rva005C3180 *)particle)->dispatch();
				corners[0] = (px - half) * matrix[0] + (py - half) * matrix[3] + pz * matrix[6] + matrix[9];
				corners[1] = (px - half) * matrix[1] + (py - half) * matrix[4] + pz * matrix[7] + matrix[10];
				corners[2] = (px - half) * matrix[2] + (py - half) * matrix[5] + pz * matrix[8] + matrix[11];
				positions[count * 4 + 0].X = corners[0];
				positions[count * 4 + 0].Y = corners[1];
				positions[count * 4 + 0].Z = corners[2];
				corners[3] = (px + half) * matrix[0] + (py - half) * matrix[3] + pz * matrix[6] + matrix[9];
				corners[4] = (px + half) * matrix[1] + (py - half) * matrix[4] + pz * matrix[7] + matrix[10];
				corners[5] = (px + half) * matrix[2] + (py - half) * matrix[5] + pz * matrix[8] + matrix[11];
				positions[count * 4 + 1].X = corners[3];
				positions[count * 4 + 1].Y = corners[4];
				positions[count * 4 + 1].Z = corners[5];
				corners[6] = (px - half) * matrix[0] + (py + half) * matrix[3] + pz * matrix[6] + matrix[9];
				corners[7] = (px - half) * matrix[1] + (py + half) * matrix[4] + pz * matrix[7] + matrix[10];
				corners[8] = (px - half) * matrix[2] + (py + half) * matrix[5] + pz * matrix[8] + matrix[11];
				positions[count * 4 + 2].X = corners[6];
				positions[count * 4 + 2].Y = corners[7];
				positions[count * 4 + 2].Z = corners[8];
				corners[9] = (px + half) * matrix[0] + (py + half) * matrix[3] + pz * matrix[6] + matrix[9];
				corners[10] = (px + half) * matrix[1] + (py + half) * matrix[4] + pz * matrix[7] + matrix[10];
				corners[11] = (px + half) * matrix[2] + (py + half) * matrix[5] + pz * matrix[8] + matrix[11];
				positions[count * 4 + 3].X = corners[9];
				positions[count * 4 + 3].Y = corners[10];
				positions[count * 4 + 3].Z = corners[11];
				for (i = 0; i != 4; ++i)
					for (j = 0; j != 4; ++j)
						((float *)&colours[count * 4 + i])[j] =
							colour ? ((float *)colour)[j] : 0.0f;
				colours[count * 4 + 0].W = uv;
				colours[count * 4 + 1].W = uv;
				colours[count * 4 + 2].W = uv;
				colours[count * 4 + 3].W = uv;
				++count;
			}
		}
		particle = *(Particle **)((char *)particle + 0x3c);
	}

	if (count <= 0)
		return count;

	{
		Char *name = *(Char **)((char *)system + 0x10);
		BFMEWaterTrackTextureHandle texture =
			BFMEGetWaterTrackTexture(name ? name + 8 : (Char *)0x0107388b, 0, 0);
		if (TheGen012F6DFC)
		{
			if (TheGen012F6DFC->m_14)
				TheGen012F6DFC->m_14->Release_Ref();
			TheGen012F6DFC->m_14 = texture.m_texture;
			switch (*(int *)((char *)system + 8) - 1)
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
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E24;
					break;
				case 5:
					TheGen012F6DFC->m_18 = *(RefCountClass **)0x012D6E28;
					break;
			}
		}
		if (TheGen012F6DFC)
		{
			((Rva0090F8C0Holder *)TheGen012F6DFC)->set(count,
				*(RefCountClass **)0x012F6DC8,
				*(RefCountClass **)0x012F6DCC, 0, 0);
			d_0090fee0(TheGen012F6DFC, arg1);
		}
		return count;
	}
}

}
