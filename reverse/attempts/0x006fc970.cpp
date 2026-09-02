// ??0EMPUpdateModuleData@@QAE@XZ
// partial score=0.81 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

#include <string.h>

class UpdateModuleData
{
public:
	UpdateModuleData();
	virtual void moduleDataAnchor();

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

class EMPUpdateModuleData : public UpdateModuleData, public SixZeroWords
{
public:
	EMPUpdateModuleData();
	virtual void empModuleDataAnchor();

private:
	float m_startScale;               // +0x88
	float m_targetScaleMax;           // +0x8c
	volatile int m_zero90;
	volatile int m_zero94;
	volatile int m_zero98;
	float m_startColor[3];             // +0x9c
	int m_zeroA8[10];
	float m_effectRadius;              // +0xd0
	unsigned char m_gapD4[0x10];
	float m_targetScaleMin;            // +0xe4
	volatile int m_disabledDuration;            // +0xe8
	float m_angle;                     // +0xec
	unsigned char m_gapF0[0x48];
	int m_zero138[5];
	unsigned char m_gap14C[0x0c];
	int m_victimGrid[2500];            // +0x158
};

EMPUpdateModuleData::EMPUpdateModuleData()
{
	m_startScale = 1.0f;
	m_targetScaleMax = 1.0f;
	m_zero90 = 0;
	m_zero94 = 0;
	m_zero98 = 0;
	m_startColor[0] = 0.9f;
	m_startColor[1] = 0.9f;
	m_startColor[2] = 0.9f;
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
	m_zero138[0] = 0;
	m_zero138[1] = 0;
	m_zero138[2] = 0;
	m_zero138[3] = 0;
	m_zero138[4] = 0;
	m_effectRadius = 10.0f;
	m_targetScaleMin = 1.0f;
	m_disabledDuration = 0;
	m_angle = 0.5235988f;
	memset( m_victimGrid, 0, sizeof( m_victimGrid ) );
}
