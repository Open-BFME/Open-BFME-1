// cl: /DNDEBUG /MD /EHs-c- /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug
//
// Retail 0x00723B60 (184 bytes, ret at 0x00723C17). W3DSnowManager::update
// (0x00725AC0) ends by tail-calling it on the same receiver through ILT
// 0x000092AF, which proves the owner; no evidence names the method, so the
// name keeps the address. It counts down the lightning flash while one is
// active, otherwise rolls LightningChance and starts a new flash lasting
// LightningDuration scaled by Random_Float(0.7f, 1.2f) -- retail's multiplier
// 0x3f000001 is 1.2f - 0.7f folded, the inline WWMath overload.

#include "wwmath.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// Retail calls the out-of-line copy through ILT 0x000022BB (body 0x00087A80).
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	__inline const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

// Offsets and names from retail's WeatherSetting FieldParse table (RVA 0x00CF6540):
// LightningEnabled +0x40, LightningDuration +0x50, LightningChance +0x54.
class WeatherSetting : public Overridable
{
public:
	char m_unmodelled_08[0x40 - 0x08];
	bool m_lightningEnabled;
	char m_unmodelled_41[0x50 - 0x41];
	int m_lightningDuration;
	float m_lightningChance;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class W3DSnowManager
{
public:
	void rva00723B60(void);

private:
	char m_unmodelled_00[0x44];
	bool m_byte44;
	char m_unmodelled_45[0x48 - 0x45];
	int m_dword48;
};

void W3DSnowManager::rva00723B60(void)
{
	if (!TheWeatherSetting->m_lightningEnabled)
		return;
	if (m_byte44)
	{
		if (--m_dword48 > 0)
			return;
		m_dword48 = 0;
		m_byte44 = false;
		return;
	}
	float chance = WWMath::Random_Float();
	if (chance < TheWeatherSetting->m_lightningChance)
	{
		m_byte44 = true;
		m_dword48 = (int)(WWMath::Random_Float(0.7f, 1.2f) * TheWeatherSetting->m_lightningDuration + 0.5f);
	}
}
