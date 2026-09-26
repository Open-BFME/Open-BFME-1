// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BezierProjectileBehavior module-data constructor.
//
// The named friend_newModuleData factory at retail 0x001152C0 allocates 0xAC
// bytes and calls this constructor. Landed projectile behavior bodies consume
// the kill flag at +0x18, behavior flag at +0x4A, and four effect pointers at
// +0x94..+0xA0, independently fixing the important parts of this layout.

#include <string.h>

struct BezierProjectileSixWords
{
	void clear()
	{
		memset( m_words, 0, sizeof( m_words ) );
	}

	unsigned int m_words[ 6 ];
};

class BezierProjectileBehaviorModuleData
{
public:
	BezierProjectileBehaviorModuleData();
	virtual ~BezierProjectileBehaviorModuleData();

private:
	unsigned int m_moduleData;
	unsigned int m_value08;
	unsigned int m_value0C;
	unsigned int m_value10;
	unsigned int m_value14;
	unsigned char m_killInsteadOfDestroy;
	unsigned char m_flag19;
	unsigned char m_pad1A[ 2 ];
	unsigned int m_effectFrame;
	unsigned int m_value20;
	unsigned int m_value24;
	unsigned int m_value28;
	unsigned int m_value2C;
	unsigned int m_value30;
	unsigned int m_value34;
	unsigned int m_value38;
	unsigned int m_value3C;
	unsigned int m_value40;
	unsigned int m_value44;
	unsigned char m_flag48;
	unsigned char m_enabled;
	unsigned char m_objectFire;
	unsigned char m_pad4B;
	unsigned int m_value4C;
	BezierProjectileSixWords m_firstCurve;
	BezierProjectileSixWords m_secondCurve;
	unsigned int m_value80;
	unsigned int m_value84;
	unsigned char m_flag88;
	unsigned char m_pad89[ 3 ];
	float m_minCurveFraction;
	float m_maxCurveFraction;
	void *m_effect94;
	void *m_effect98;
	void *m_effect9C;
	void *m_effectA0;
	int m_invalidA4;
	unsigned int m_valueA8;
};

// ??0BezierProjectileBehaviorModuleData@@QAE@XZ
BezierProjectileBehaviorModuleData::BezierProjectileBehaviorModuleData()
{
	m_value08 = 0;
	m_value0C = 0;
	m_value10 = 0;
	m_value14 = 0;
	m_killInsteadOfDestroy = 0;
	m_flag19 = 0;
	m_effectFrame = 0;
	m_value20 = 0;
	m_value24 = 0;
	m_value28 = 0;
	m_value2C = 0;
	m_value30 = 0;
	m_value34 = 0;
	m_value38 = 0;
	m_value3C = 0;
	m_value40 = 0;
	m_value44 = 0;
	m_flag48 = 0;
	m_enabled = 1;
	m_objectFire = 0;
	m_value4C = 0;
	m_firstCurve.clear();
	m_secondCurve.clear();
	m_value80 = 0;
	m_value84 = 0;
	m_flag88 = 0;
	m_minCurveFraction = 0.33f;
	m_maxCurveFraction = 0.66f;
	m_effect94 = 0;
	m_effect98 = 0;
	m_effect9C = 0;
	m_effectA0 = 0;
	m_invalidA4 = -1;
	m_valueA8 = 0;
}
