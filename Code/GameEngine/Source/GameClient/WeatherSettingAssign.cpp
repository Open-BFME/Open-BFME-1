// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/sweep

// BFME WeatherSetting assignment.  The retail body is the same concrete
// ScienceInfoBase-headed layout used by the neighboring setting assignments:
// base assignment, AsciiString assignment at +0x0C, then the BFME weather
// fields through the 0x78-byte object extent.

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other); // retail 0x00887C90

private:
	void *m_bfmeData;
};

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other); // retail ILT 0x00048725

private:
	char m_bfmeHead[0x0C];
};

struct BFMELightningRandomVariable
{
	Real m_low;
	Real m_high;
	Int m_distribution;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Snow.h
class WeatherSetting : public ScienceInfoBase
{
public:
	WeatherSetting &operator=(const WeatherSetting &other);

private:
	AsciiString m_snowTexture;                 // +0x0C
	volatile Real m_snowFrequencyScaleX;       // +0x10
	volatile Real m_snowFrequencyScaleY;       // +0x14
	volatile Real m_snowAmplitude;             // +0x18
	volatile Real m_snowPointSize;             // +0x1C
	volatile Real m_snowMaxPointSize;          // +0x20
	volatile Real m_snowMinPointSize;          // +0x24
	volatile Real m_snowQuadSize;              // +0x28
	volatile Real m_snowBoxDimensions;         // +0x2C
	volatile Real m_snowBoxDensity;            // +0x30
	volatile Real m_snowVelocity;              // +0x34
	volatile Bool m_usePointSprites;           // +0x38
	volatile Bool m_snowEnabled;               // +0x39
	volatile Bool m_isSnowing;                 // +0x3A
	char m_pad3B;
	volatile Int m_numberTiles;                // +0x3C
	volatile Bool m_lightningEnabled;          // +0x40
	char m_pad41[3];
	BFMELightningRandomVariable m_lightningFactor; // +0x44
	volatile Int m_lightningDuration;          // +0x50
	volatile Real m_lightningChance;           // +0x54
	volatile Bool m_spellEnabled;              // +0x58
	char m_pad59[3];
	volatile Int m_spellDuration;               // +0x5C
	volatile Real m_rampControl[2];             // +0x60
	volatile Real m_rampSpeed[2];               // +0x68
	volatile Real m_rampSpacing[2];             // +0x70
};

WeatherSetting &WeatherSetting::operator=(const WeatherSetting &other)
{
	ScienceInfoBase::operator=(other);
	m_snowTexture = other.m_snowTexture;
	m_snowFrequencyScaleX = other.m_snowFrequencyScaleX;
	m_snowFrequencyScaleY = other.m_snowFrequencyScaleY;
	m_snowAmplitude = other.m_snowAmplitude;
	m_snowPointSize = other.m_snowPointSize;
	m_snowMaxPointSize = other.m_snowMaxPointSize;
	m_snowMinPointSize = other.m_snowMinPointSize;
	m_snowQuadSize = other.m_snowQuadSize;
	m_snowBoxDimensions = other.m_snowBoxDimensions;
	m_snowBoxDensity = other.m_snowBoxDensity;
	m_snowVelocity = other.m_snowVelocity;
	m_usePointSprites = other.m_usePointSprites;
	m_snowEnabled = other.m_snowEnabled;
	m_isSnowing = other.m_isSnowing;
	m_numberTiles = other.m_numberTiles;
	m_lightningEnabled = other.m_lightningEnabled;
	m_lightningFactor = other.m_lightningFactor;
	m_lightningDuration = other.m_lightningDuration;
	m_lightningChance = other.m_lightningChance;
	m_spellEnabled = other.m_spellEnabled;
	m_spellDuration = other.m_spellDuration;
	m_rampControl[0] = other.m_rampControl[0];
	m_rampControl[1] = other.m_rampControl[1];
	m_rampSpeed[0] = other.m_rampSpeed[0];
	m_rampSpeed[1] = other.m_rampSpeed[1];
	m_rampSpacing[0] = other.m_rampSpacing[0];
	m_rampSpacing[1] = other.m_rampSpacing[1];
	return *this;
}
