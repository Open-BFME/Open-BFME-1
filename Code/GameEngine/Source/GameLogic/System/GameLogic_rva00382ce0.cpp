// cl: /DNDEBUG /MD /EHsc
// Retail 0x00382CE0: if the pointer at +0x118 is live, scalar-delete it,
// null it, then spin while the current thread still owns the DX8 device lock.

class Rva00382CE0Object
{
public:
	virtual ~Rva00382CE0Object();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static bool Owns_Device_Lock(void);
};

extern void BFME_DX8_Thread_Assert(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void destroyLoadScreen(void);

	char m_pad[0x118];
	Rva00382CE0Object *m_loadScreen;
};

// ?destroyLoadScreen@GameLogic@@QAEXXZ
void GameLogic::destroyLoadScreen(void)
{
	if (m_loadScreen)
	{
		delete m_loadScreen;
		m_loadScreen = 0;
		if (DX8Wrapper::Owns_Device_Lock())
		{
			do
				BFME_DX8_Thread_Assert();
			while (DX8Wrapper::Owns_Device_Lock());
		}
	}
}
