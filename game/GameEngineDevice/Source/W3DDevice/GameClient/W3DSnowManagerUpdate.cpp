// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?update@W3DSnowManager@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp

// Retail 0x00725AC0. W3DSnowManager::update -- ZH's
//   m_time += WW3D::Get_Frame_Time() / 1000.0f;
//   m_time = fmod(m_time, m_fullTimePeriod);
// plus two extra BFME thiscalls on the same object (thunks 0x00008F2B /
// 0x000092AF to 0x00725620 and 0x00723B60). m_time is at +0xC and
// m_fullTimePeriod at +0x14, four bytes below ZH (BFME SubsystemInterface
// is wider).

extern "C" double __cdecl fmod(double, double);

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;

	void *m_vtable;
	const BfmeOverridable *m_nextOverride;
	};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Snow.h
class WeatherSetting : public BfmeOverridable
{
public:
	unsigned char m_unmodelled_08[0x30 - 8];
	int m_30;
	int m_34;
	unsigned char m_unmodelled_38[0x3a - 0x38];
	char m_flag3a;
	unsigned char m_unmodelled_3b[0x40 - 0x3b];
	char m_flag40;
	unsigned char m_unmodelled_41[0x50 - 0x41];
	int m_50;
	float m_54Override;
	char m_flag58;
	unsigned char m_unmodelled_59[3];
	int m_5c;
};

class BFMEFrameState
{
public:
	unsigned char m_unmodelled_00[0x0c];
	int m_frame;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	T *ptr;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern BFMEFrameState *g_bfmeGlo012F0FE0;
extern "C" float g_bfmeDefaultBU;
extern "C" float g_bfmeK1121004;
extern "C" float g_bfmeK075C6C;
extern "C" float g_bfmeK07533C;

class WWMath
{
public:
	static float Random_Float();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Frame_Time(void)
	{
		return SyncTime - PreviousSyncTime;
	}

private:
	static unsigned int SyncTime;
	static unsigned int PreviousSyncTime;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DSnow.h
class W3DSnowManager
{
public:
	virtual void update(void);
	void extraAfterFmod(void);
	void extraTail(void);
	void transitionTBA(void);
	void copyFromOverride(void);
	void sibling(void);

private:
	unsigned char m_unmodelled_04[0xC - 4];
	float m_time;				// +0xC
	union { float m_velocity; float m_10f; };	// +0x10
	float m_fullTimePeriod;		// +0x14
	unsigned char m_unmodelled_18[0x38 - 0x18];
	union { int m_38; float m_38f; };
	char m_unmodelled_3c;
	char m_flag3d;
	unsigned char m_unmodelled_3e[0x44 - 0x3e];
	char m_flag44;
	unsigned char m_unmodelled_45[3];
	int m_48;
	int m_4c;
	float m_50;
	float m_54;
	union { int m_58; float m_58f; };
	union { int m_5c; float m_5cf; };
	float m_60;
	float m_64;
	unsigned char m_unmodelled_68[0x94 - 0x68];
	int m_94;
	int m_98;
};

static const WeatherSetting *walkSnowOverride(const WeatherSetting *d)
{
	if (d && d->m_nextOverride)
		return (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	return d;
}

static const WeatherSetting *walkSnowOverride3(const WeatherSetting *d)
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

// ?update@W3DSnowManager@@UAEXXZ
void W3DSnowManager::update(void)
{
	m_time += WW3D::Get_Frame_Time() / 1000.0f;
	m_time = fmod(m_time, m_fullTimePeriod);
	extraAfterFmod();
	extraTail();
}

// The byte-verified extraAfterFmod definition belongs to
// W3DSnowManagerExtraAfterFmod.cpp.

// ?extraTail@W3DSnowManager@@QAEXXZ present-unmatched (retail 0x00723B60 via thunk
// 0x000092AF, still held by the ?d_00723b60 gen-dump row)
void W3DSnowManager::extraTail(void)
{
	register const WeatherSetting *d = TheWeatherSetting.ptr;
	float slot;
	register const WeatherSetting *f;
	if (d && d->m_nextOverride)
		d = (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	if (d->m_flag40 == 0)
		return;
	if (m_flag44)
	{
		--m_48;
		if (m_48 > 0)
			return;
		m_48 = 0;
		m_flag44 = 0;
		return;
	}
	slot = WWMath::Random_Float();
	d = TheWeatherSetting.ptr;
	if (d && d->m_nextOverride)
		d = (const WeatherSetting *)d->m_nextOverride->getFinalOverride();
	if (!(slot < d->m_54Override))
		return;
	m_flag44 = 1;
	d = TheWeatherSetting.ptr;
	f = walkSnowOverride3(d);
	m_48 = (int)((WWMath::Random_Float() * g_bfmeK1121004 + g_bfmeK075C6C) * f->m_50 + g_bfmeK07533C);
}

// ?transitionTBA@W3DSnowManager@@QAEXXZ present-unmatched (retail address not yet assigned)
void W3DSnowManager::transitionTBA(void)
{
	WeatherSetting *f = TheWeatherSetting.ptr;
	const WeatherSetting *d = walkSnowOverride(f);
	const WeatherSetting *next;
	const WeatherSetting *from;
	const WeatherSetting *to;
	float fraction;

	if (d->m_flag58 == 0 || m_98 == 0)
		return;

	if (f == 0)
	{
		from = 0;
		to = 0;
	}
	else
	{
		next = (const WeatherSetting *)f->m_nextOverride;
		if (next == 0)
		{
			from = f;
			to = f;
		}
		else
		{
			from = (const WeatherSetting *)next->getFinalOverride();
			to = (const WeatherSetting *)next->getFinalOverride();
		}
	}
	fraction = (float)(from->m_5c - m_4c) / (float)to->m_5c;
	if (fraction > 1.0f)
	{
		// The real method is the same class's override reset operation.
		copyFromOverride();
		return;
	}

	if (fraction > m_54)
	{
		m_98 = 3;
		float blend = (fraction - m_54) /
			(g_bfmeDefaultBU - m_54);
		m_38f = m_5cf - (m_5cf - m_58f) * blend;
		m_10f = m_64 - (m_64 - m_60) * blend;
		return;
	}

	if (fraction > m_50)
	{
		m_98 = 2;
		m_38f = m_5cf;
		m_10f = m_64;
		return;
	}

	if (fraction <= 0.0f)
	{
		copyFromOverride();
		return;
	}

	m_98 = 1;
	float blend = m_50 > 1e-5f ?
		fraction / m_50 : 1.0f;
	m_38f = m_58f + (m_5cf - m_58f) * blend;
	m_10f = m_60 + (m_64 - m_60) * blend;
}
