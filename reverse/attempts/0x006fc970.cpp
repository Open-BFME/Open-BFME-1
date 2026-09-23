// ??0Rva006FC970@@QAE@XZ
// partial score=0.93 date=2026-09-23
// Opaque constructor candidate at 0x006FC970; vtable 0x011207C0.
// The prior EMPUpdateModuleData label is refuted by its vtable and destructor.
// Only witnessed field offsets are named here; semantic member identities are unknown.
// cl: /DNDEBUG /MD /EHsc

#include <string.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0060A000Base
{
public:
	Rva0060A000Base();
	volatile unsigned m_vtable;

private:
	unsigned char m_unmodelled_04[ 0x70 - 4 ];
};

class SixZeroWords
{
public:
	SixZeroWords()
	{
		for( int i = 0; i < 6; ++i )
			m_words[i] = 0;
	}

private:
	int m_words[6];
};

class Rva006FC970 : public Rva0060A000Base, public SixZeroWords
{
public:
	Rva006FC970();


private:
	volatile float m_field88;               // +0x88
	volatile float m_field8C;           // +0x8c
	volatile int m_zero90;
	volatile int m_zero94;
	volatile int m_zero98;
	volatile float m_field9C[3];             // +0x9c
	volatile int m_zeroA8[10];
	volatile float m_fieldD0;              // +0xd0
	unsigned char m_gapD4[0x10];
	volatile float m_fieldE4;            // +0xe4
	volatile int m_fieldE8;            // +0xe8
	volatile float m_fieldEC;                     // +0xec
	unsigned char m_gapF0[0x48];
	volatile int m_zero138[5];
	unsigned char m_gap14C[0x0c];
	int m_field158[2500];            // +0x158
};

Rva006FC970::Rva006FC970()
{
	m_vtable = 0x011207C0u;
	_ReadWriteBarrier();
	m_field88 = 1.0f;
	m_field8C = 1.0f;
	m_zero90 = 0;
	m_zero94 = 0;
	m_zero98 = 0;
	_ReadWriteBarrier();
	m_field9C[0] = 0.9f;
	m_field9C[1] = 0.9f;
	m_field9C[2] = 0.9f;
	m_zeroA8[0] = 0;
	m_zeroA8[1] = 0;
	m_zeroA8[2] = 0;
	m_zeroA8[3] = 0;
	m_zeroA8[4] = 0;
	m_zeroA8[5] = 0;
	m_zeroA8[6] = 0;
	m_zeroA8[7] = 0;
	m_zeroA8[8] = 0;
	m_zeroA8[9] = 0;
	m_fieldE8 = 0;
	m_zero138[0] = 0;
	m_zero138[1] = 0;
	m_zero138[2] = 0;
	m_zero138[3] = 0;
	m_zero138[4] = 0;
	m_fieldD0 = 10.0f;
	m_fieldE4 = 1.0f;
	m_fieldEC = 0.5235988f;
	memset( m_field158, 0, sizeof( m_field158 ) );
}
