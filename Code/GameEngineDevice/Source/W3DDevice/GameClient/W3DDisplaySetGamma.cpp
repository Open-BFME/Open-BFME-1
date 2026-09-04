// cl: /DNDEBUG /MD /EHsc
// readable body of ?setGamma@W3DDisplay@@UAEXMMM_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Gamma(float gamma, float bright, float contrast, bool calibrate, bool uselimit);
};

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	virtual void setGamma(float gamma, float bright, float contrast, bool calibrate);

private:
	unsigned char m_unmodelled[0x10];
	unsigned char m_windowed;
};

// ?setGamma@W3DDisplay@@UAEXMMM_N@Z
void W3DDisplay::setGamma(float gamma, float bright, float contrast, bool calibrate)
{
	if (m_windowed)
		return;

	W3DRadarResetGuard lock;
	DX8Wrapper::Set_Gamma(gamma, bright, contrast, calibrate, false);
}
