// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversions.
// ghidra: FUN_00b23c50 retail @ 0x00723C50 size 124
// Sibling of BfmeA1137::copyFromOverride: two override walks of
// g_bfmeGlo012F15F8; both +0x40 and this+0x44 set => tail-call
// GameClientRandomVariable::getValue at override+0x44, else return 1.0f.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
	float getValue() const;
};

class WeatherSetting : public Overridable
{
public:
	char m_unmodelled_08[0x40 - 8];
	char m_flag40;
	char m_unmodelled_41[3];
	GameClientRandomVariable m_random;
};

template <class T> class OVERRIDE
{
public:
	T *ptr;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class BfmeA1137
{
public:
	float cachedRandom();

private:
	char m_unmodelled_00[0x44];
	char m_flag44;
};

static const WeatherSetting *walk3(const WeatherSetting *d)
{
	const WeatherSetting *f;
	if (d == 0)
		f = 0;
	else if (d->m_nextOverride)
		f = (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	else
		f = d;
	return f;
}

float BfmeA1137::cachedRandom()
{
	int one_bits = 0x3F800000;
	const WeatherSetting *d = TheWeatherSetting.ptr;
	const WeatherSetting *f = walk3(d);
	if (f->m_flag40 == 0 || m_flag44 == 0)
		return *(float *)&one_bits;
	f = walk3(d);
	return f->m_random.getValue();
}
