// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@W3DSnowManager@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp

// Retail 0x00725AC0. W3DSnowManager::update -- ZH's
//   m_time += WW3D::Get_Frame_Time() / 1000.0f;
//   m_time = fmod(m_time, m_fullTimePeriod);
// plus two extra BFME thiscalls on the same object (thunks 0x00008F2B /
// 0x000092AF to 0x00725620 and 0x00723B60). m_time is at +0xC and
// m_fullTimePeriod at +0x14, four bytes below ZH (BFME SubsystemInterface
// is wider).

extern "C" double __cdecl fmod(double, double);

class BFMEWeatherOverride
{
public:
	const BFMEWeatherOverride *getFinalOverride() const;

	void *m_vtable;
	const BFMEWeatherOverride *m_nextOverride;
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
	void copyFromOverride(void);
	void sibling(void);

private:
	unsigned char m_unmodelled_04[0xC - 4];
	float m_time;				// +0xC
	float m_velocity;			// +0x10
	float m_fullTimePeriod;		// +0x14
	unsigned char m_unmodelled_18[0x38 - 0x18];
	int m_38;
	char m_unmodelled_3c;
	char m_flag3d;
	unsigned char m_unmodelled_3e[0x4c - 0x3e];
	int m_4c;
	unsigned char m_unmodelled_50[0x54 - 0x50];
	float m_54;
	int m_58;
	int m_5c;
	unsigned char m_unmodelled_60[0x94 - 0x60];
	int m_94;
	int m_98;
};

static const BFMEWeatherOverride *walkSnowOverride(const BFMEWeatherOverride *d)
{
	if (d && d->m_nextOverride)
		return d->m_nextOverride->getFinalOverride();
	return d;
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
		if (state == 1 || state == 3)
			--m_4c;
		sibling();
		int state94 = m_94;
		if (state94 == 2)
		{
			int frame = g_bfmeGlo012F0FE0->m_frame;
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
			m_94 = 2;
			copyFromOverride();
		}
	}
}
