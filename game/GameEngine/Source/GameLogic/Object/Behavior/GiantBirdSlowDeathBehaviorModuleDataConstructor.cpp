// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// This constructor also emits the exact 30-byte scalar-deleting wrapper
// at 0x001FFF20, whose ILT 0x0001CE0E call reaches the complete destructor
// at 0x001FFF50. Keep it here so the separate wrapper forcing TU does not
// emit a competing, vptr-only constructor for this class.
// Retail 001FFE40: initializes the 24-byte block, then clears it again in the body.
// Base ILT 76DA routes to SlowDeathBehaviorModuleData constructor 002093F0.
// AudioEventRTS is 0x70 bytes; ILT 25306 routes to its two-argument ctor B2CC0.

#include <string.h>

#include "ascii_string.h"

extern AsciiString TheBfmeCrateNameDefault;		// 0x01336E50

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int field28);	// 0x000B2CC0
	virtual ~AudioEventRTS();						// 0x000B31F0

private:
	unsigned char m_body[0x6c];	// +0x04..+0x6F; vptr at +0x00
};

class SixDwordBlock00224
{
public:
	SixDwordBlock00224() { memset(this, 0, sizeof(*this)); }

private:
	volatile unsigned int m_word[6];
};

class SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();		// 0x000076DA
	virtual ~SlowDeathBehaviorModuleData();	// 0x00015645

private:
	unsigned char m_body[0x1a4];
};

class GiantBirdSlowDeathBehaviorModuleData
	: public SlowDeathBehaviorModuleData
{
public:
	GiantBirdSlowDeathBehaviorModuleData();
	virtual ~GiantBirdSlowDeathBehaviorModuleData();

private:
	volatile unsigned int m_field1A8;
	volatile unsigned int m_field1AC;
	volatile unsigned int m_field1B0;
	AudioEventRTS m_1B4;				// +0x1B4
	SixDwordBlock00224 m_224;				// +0x224
	volatile float m_field23C;
	volatile float m_field240;
	volatile unsigned char m_field244;
};

GiantBirdSlowDeathBehaviorModuleData::GiantBirdSlowDeathBehaviorModuleData()
	: m_1B4(TheBfmeCrateNameDefault, 0)
{
	m_field1A8 = 0;
	m_field1AC = 0;
	m_field1B0 = 0;
	memset(&m_224, 0, sizeof(m_224));
	m_field244 = 0;
	m_field23C = 800.0f;
	m_field240 = 0.1f;
}
