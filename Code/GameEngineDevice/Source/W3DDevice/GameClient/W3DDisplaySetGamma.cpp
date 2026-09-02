// cl: /DNDEBUG /MD /EHsc
// readable body of ?setGamma@W3DDisplay@@UAEXMMM_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

void __cdecl bfmeLockVHM(void);
char __cdecl bfmeUnlock1179(void);

class DX8Wrapper
{
public:
	static void Set_Gamma(float gamma, float bright, float contrast, bool calibrate, bool uselimit);
};

class BfmeDx8Lock
{
public:
	BfmeDx8Lock(void)
	{
		bfmeLockVHM();
	}

	~BfmeDx8Lock(void)
	{
		bfmeUnlock1179();
	}
};

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

	BfmeDx8Lock lock;
	DX8Wrapper::Set_Gamma(gamma, bright, contrast, calibrate, false);
}
