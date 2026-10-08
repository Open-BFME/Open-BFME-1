// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Native module-group reset layout follows Y3Reset_005CC0B0.
// The owner remains address-qualified; see the retained identity evidence.

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
	Rva005CC6C0Module *m_h0;
	Rva005CC6C0Module *m_h1;
	char m_gap[8];
	Rva005CC6C0Module *m_h2;
	Rva005CC6C0Module **m_begin;
	Rva005CC6C0Module **m_end;
};

class Rva005CC6C0Modules
{
public:
    Rva005CC6C0Module *m_h0;
    Rva005CC6C0Module *m_h1;
    Y3ResetTail_005CAB40 m_tail;

    // ?resetAll@Rva005CC6C0Modules@@QAEXXZ absent-from-retail
    __forceinline void resetAll()
    {
        Rva005CC6C0Module *head = m_h0;
        if (head)
            head->slot1();
        head = m_h1;
        if (head)
            head->slot1();
        m_tail.resetAll();
    }
};

class Particle
{
public:
	bool isInvisible();
};

class Rva005CC6C0Particle
{
public:
	bool update();
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
	Rva005CC6C0Modules m_modules8C;
};

float ACos( float );

// ?update@Rva005CC6C0Particle@@QAE_NXZ
bool Rva005CC6C0Particle::update()
{
	m_modules8C.resetAll();

	if (m_byte38 && m_modules8C.m_tail.m_h0) {
		float direction[2];
		direction[0] = m_float1C - m_float28;
		direction[1] = m_float20 - m_float2C;
		if (direction[1] < 1.1920928955078125e-7f && direction[1] > -1.1920928955078125e-7f) {
			float angle = direction[0] > 0.0f ? 6.2831853071795864769f : 3.1415926535897932385f;
			Rva005CC6C0Module *module = m_modules8C.m_tail.m_h0;
			module->slot9(angle);
		} else {
			float length = static_cast<float>(sqrt(direction[0] * direction[0] + direction[1] * direction[1]));
			if (length < 1.1920928955078125e-7f) {
				Rva005CC6C0Module *module = m_modules8C.m_tail.m_h0;
				module->slot9(3.1415926535897932385f);
			} else {
				float angle = ACos(direction[1] / length);
				angle = direction[0] > 0.0f ? angle + 3.1415926535897932385f : 3.1415926535897932385f - angle;
				Rva005CC6C0Module *module = m_modules8C.m_tail.m_h0;
				module->slot9(angle);
			}
		}
	}

	if (m_dword68 != 0 && --m_dword68 == 0)
		return false;
	return !reinterpret_cast<Particle *>(this)->isInvisible();
}
