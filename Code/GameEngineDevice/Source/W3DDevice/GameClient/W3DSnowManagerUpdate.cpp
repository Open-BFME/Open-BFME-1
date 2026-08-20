// cl: /DNDEBUG /MD /EHsc

// Retail 0x00725AC0. W3DSnowManager::update -- ZH's
//   m_time += WW3D::Get_Frame_Time() / 1000.0f;
//   m_time = fmod(m_time, m_fullTimePeriod);
// plus two extra BFME thiscalls on the same object (thunks 0x00008F2B /
// 0x000092AF to 0x00725620 and 0x00723B60). m_time is at +0xC and
// m_fullTimePeriod at +0x14, four bytes below ZH (BFME SubsystemInterface
// is wider).

extern "C" double __cdecl fmod(double, double);

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

class W3DSnowManager
{
public:
	virtual void update(void);
	void extraAfterFmod(void);
	void extraTail(void);

private:
	unsigned char m_unmodelled_04[0xC - 4];
	float m_time;				// +0xC
	float m_velocity;			// +0x10
	float m_fullTimePeriod;		// +0x14
};

// ?update@W3DSnowManager@@UAEXXZ
void W3DSnowManager::update(void)
{
	m_time += WW3D::Get_Frame_Time() / 1000.0f;
	m_time = fmod(m_time, m_fullTimePeriod);
	extraAfterFmod();
	extraTail();
}
