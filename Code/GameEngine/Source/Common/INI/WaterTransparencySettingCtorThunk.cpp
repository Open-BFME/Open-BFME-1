// cl: /DNDEBUG /MD /EHsc

// Overridable base, nine floats, a layout string and a bool.
//
// The exception frame has two states and they count up, 0 then 1: the base is
// built first, then the string at 0x30. The string's constructor is inlined --
// `lea ecx,[esi+0x30]` then one zeroed word -- and the same register is still the
// this for the set() call further down, which is why the lea appears so early.
//
// Two details the shim header gets right and a naive reading would not. Retail
// never writes the two words at 0x38 and 0x3c: they take no INI field and the
// constructor leaves them alone. And it assigns the river multiplier at 0x34
// before the blend flag at 0x2c, which is the opposite of declaration order, so
// the body has to say it that way round.
class RetailLayoutString
{
public:
	RetailLayoutString()
	{
		m_data = 0;
	}

	~RetailLayoutString();

	void set(const char *text, int length);

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable()
	{
		m_next = 0;
		m_isOverride = false;
	}

	virtual ~Overridable();

private:
	Overridable *m_next;
	bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Water.h
class WaterTransparencySetting : public Overridable
{
public:
	WaterTransparencySetting();

private:
	float m_transparentWaterDepth;
	float m_minWaterOpacity;
	float m_standingWaterRed;
	float m_standingWaterGreen;
	float m_standingWaterBlue;
	float m_radarRed;
	float m_radarGreen;
	float m_radarBlue;
	bool m_additiveBlend;
	RetailLayoutString m_standingWaterTexture;
	float m_riverTransparencyMultiplier;
	int m_38;
	int m_3c;
};

// ??0WaterTransparencySetting@@QAE@XZ
WaterTransparencySetting::WaterTransparencySetting()
{
	m_transparentWaterDepth = 3.0f;
	m_minWaterOpacity = 1.0f;
	m_standingWaterRed = 1.0f;
	m_standingWaterGreen = 1.0f;
	m_standingWaterBlue = 1.0f;
	m_radarRed = 140.0f;
	m_radarGreen = 140.0f;
	m_radarBlue = 255.0f;
	m_standingWaterTexture.set("TWWater01.tga", 13);
	m_riverTransparencyMultiplier = 1.0f;
	m_additiveBlend = false;
}
