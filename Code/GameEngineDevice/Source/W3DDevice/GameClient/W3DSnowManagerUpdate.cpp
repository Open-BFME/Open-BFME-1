// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?update@W3DSnowManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp

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

class BFMEWeatherOverride : public BfmeOverridable
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

extern BFMEWeatherOverride *g_bfmeGlo012F15F8;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int SyncTime;
	static unsigned int PreviousSyncTime;
	static unsigned int Get_Frame_Time(void)
	{
		return SyncTime - PreviousSyncTime;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DSnow.h
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

static const BFMEWeatherOverride *walkSnowOverride(const BFMEWeatherOverride *d)
{
	if (d && d->m_nextOverride)
		return (const BFMEWeatherOverride *)d->m_nextOverride->getFinalOverride();
	return d;
}

static const BFMEWeatherOverride *walkSnowOverride3(const BFMEWeatherOverride *d)
{
	const BFMEWeatherOverride *f;
	if (d == 0)
		f = 0;
	else if (d->m_nextOverride)
		f = (const BFMEWeatherOverride *)d->m_nextOverride->getFinalOverride();
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

void W3DSnowManager::extraAfterFmod(void)
{
	const BFMEWeatherOverride *ov = walkSnowOverride(g_bfmeGlo012F15F8);
	if (ov->m_flag58 == 0)
		return;

	if (m_98 != 0)
	{
		int state = m_98;
		int frame;
		int state94 = 2;
		if (state == 1 || state == 3)
			--m_4c;
		sibling();
		if (m_94 == state94)
		{
			frame = g_bfmeGlo012F0FE0->m_frame;
			if (frame != state94)
			{
				m_98 = 3;
				ov = walkSnowOverride(g_bfmeGlo012F15F8);
				m_4c = (int)((g_bfmeDefaultBU - m_54) * ov->m_5c);
				m_94 = frame;
			}
		}
	}
	else
	{
		int frame = g_bfmeGlo012F0FE0->m_frame;
		if (frame == 2 && m_94 != 2)
		{
			m_94 = frame;
			copyFromOverride();
		}
	}
}

// ?extraTail@W3DSnowManager@@QAEXXZ
void W3DSnowManager::extraTail(void)
{
	register const BFMEWeatherOverride *d = g_bfmeGlo012F15F8;
	float slot;
	register const BFMEWeatherOverride *f;
	if (d && d->m_nextOverride)
		d = (const BFMEWeatherOverride *)d->m_nextOverride->getFinalOverride();
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
	d = g_bfmeGlo012F15F8;
	if (d && d->m_nextOverride)
		d = (const BFMEWeatherOverride *)d->m_nextOverride->getFinalOverride();
	if (!(slot < d->m_54Override))
		return;
	m_flag44 = 1;
	d = g_bfmeGlo012F15F8;
	f = walkSnowOverride3(d);
	m_48 = (int)((WWMath::Random_Float() * g_bfmeK1121004 + g_bfmeK075C6C) * f->m_50 + g_bfmeK07533C);
}

void W3DSnowManager::transitionTBA(void)
{
	BFMEWeatherOverride *f = g_bfmeGlo012F15F8;
	const BFMEWeatherOverride *d = walkSnowOverride(f);
	const BFMEWeatherOverride *next;
	const BFMEWeatherOverride *from;
	const BFMEWeatherOverride *to;
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
		next = (const BFMEWeatherOverride *)f->m_nextOverride;
		if (next == 0)
		{
			from = f;
			to = f;
		}
		else
		{
			from = (const BFMEWeatherOverride *)next->getFinalOverride();
			to = (const BFMEWeatherOverride *)next->getFinalOverride();
		}
	}
	fraction = (float)(from->m_5c - m_4c) / (float)to->m_5c;
	if (fraction > *(const float *)0x01075334)
	{
		// The real method is the same class's override reset operation.
		copyFromOverride();
		return;
	}

	if (fraction > m_54)
	{
		m_98 = 3;
		float blend = (fraction - m_54) /
			(*(const float *)0x01075334 - m_54);
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

	if (fraction <= *(const float *)0x01075350)
	{
		copyFromOverride();
		return;
	}

	m_98 = 1;
	float blend = m_50 > *(const float *)0x0112100C ?
		fraction / m_50 : *(const float *)0x01075334;
	m_38f = m_58f + (m_5cf - m_58f) * blend;
	m_10f = m_60 + (m_64 - m_60) * blend;
}
