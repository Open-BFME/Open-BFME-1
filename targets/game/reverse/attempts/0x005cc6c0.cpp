// ?update@Rva005CC6C0Particle@@QAEHXZ
// partial score=0.3240740741 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Address-qualified identity: the retail body is called through ILT 0x18F43,
// which is also claimed as Rva005CCA10Particle::update. No class identity is
// inferred from that thunk alone.

#include <math.h>

class Rva005CC6C0Module
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9( float value );
};

class Y3ResetTail_005CAB40
{
public:
	void resetAll();
};

class Particle
{
public:
	int isInvisible();
};

class Rva005CC6C0Particle
{
public:
	int update();
	unsigned char m_pad00[0x1c];
	float m_float1C;
	float m_float20;
	unsigned char m_pad24[4];
	float m_float28;
	float m_float2C;
	unsigned char m_pad30[8];
	bool m_byte38;
	unsigned char m_pad39[0x2f];
	unsigned int m_dword68;
	unsigned char m_pad6c[0x20];
	Rva005CC6C0Module *m_module8C;
	Rva005CC6C0Module *m_module90;
};

extern "C" float acosf( float );

int Rva005CC6C0Particle::update()
{
	if (m_module8C)
		m_module8C->slot1();
	if (m_module90)
		m_module90->slot1();
	char *moduleList = reinterpret_cast<char *>(this) + 0x94;
	reinterpret_cast<Y3ResetTail_005CAB40 *>(moduleList)->resetAll();

	if (m_byte38 && *reinterpret_cast<void **>(moduleList)) {
		float dx = m_float1C - m_float28;
		float dy = m_float20 - m_float2C;
		if (dy < 1.1920928955078125e-7f && dy > -1.1920928955078125e-7f) {
			float angle = dx > 0.0f ? 6.2831853071795864769f : 3.1415926535897932385f;
			Rva005CC6C0Module *module = *reinterpret_cast<Rva005CC6C0Module **>(moduleList);
			module->slot9(angle);
		} else {
			float length = static_cast<float>(sqrt(dx * dx + dy * dy));
			if (length < 1.1920928955078125e-7f) {
				Rva005CC6C0Module *module = *reinterpret_cast<Rva005CC6C0Module **>(moduleList);
				module->slot9(3.1415926535897932385f);
			} else {
				float angle = acosf(dy / length);
				angle = dx > 0.0f ? angle + 3.1415926535897932385f : 3.1415926535897932385f - angle;
				Rva005CC6C0Module *module = *reinterpret_cast<Rva005CC6C0Module **>(moduleList);
				module->slot9(angle);
			}
		}
	}

	if (m_dword68 != 0 && --m_dword68 == 0)
		return false;
	return !reinterpret_cast<Particle *>(this)->isInvisible();
}
