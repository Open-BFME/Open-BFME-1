// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// Open-BFME5 conversions.

// This TU reaches the singleton at 0x012F706C only through the vtable
// slot bfmeTick976C; BfmeGameCW is its local vtable view.
class BfmeGameCW
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeTick976C();
};

struct BfmeProbe976;

struct BfmeProbeTab976
{
	char m_bfmePad[0xc];
	int (__stdcall *m_bfmeAsk)(BfmeProbe976 *p);
};

struct BfmeProbe976
{
	BfmeProbeTab976 *m_bfmeTab;
};

class BfmeEndC976
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeEnd976C();
};

// Retail's global at 0x012F706C is LivingWorldManager *TheLivingWorldManager
// (data_rows.csv, LivingWorldManager.cpp); the pointee keeps this TU's view.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

// Retail's global at 0x012F64BC is ParticleSystemManager *TheParticleSystemManager;
// only the global's spelling matters to the link, so the pointee keeps this
// TU's own vtable view (BfmeEndC976) and is cast at the use.
class ParticleSystemManager;

extern ParticleSystemManager *TheParticleSystemManager;

void bfmeGo976C(void)
{
	reinterpret_cast<BfmeGameCW *>(TheLivingWorldManager)->bfmeTick976C();

	BfmeProbe976 *p = reinterpret_cast<BfmeProbe976 *>(DX8Wrapper::_Get_D3D_Device8());

	if (p && !p->m_bfmeTab->m_bfmeAsk(p))
		((BfmeEndC976 *)TheParticleSystemManager)->bfmeEnd976C();
}

class BfmeDev976
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeV5976();
	virtual void bfmeV6976();
	virtual void bfmeV7976();
	virtual void bfmeV8976();
	virtual void bfmeV9976();
	virtual void bfmeV10976();
	virtual void bfmeV11976();
	virtual char bfmeReady976E();
	virtual void bfmeGap976E();
	virtual void bfmeStop976E(int a);
	virtual void bfmeFinish976E();
};

class BfmeE976
{
public:
	void bfmeGo976E();

	char m_bfmePad[4];
	BfmeDev976 *m_bfmeDev;
	char m_bfmePad2[0x10];
	char m_bfmeOn;
};

void BfmeE976::bfmeGo976E()
{
	if (m_bfmeOn) {
		m_bfmeOn = 0;
		m_bfmeDev->bfmeStop976E(0);

		if (m_bfmeDev->bfmeReady976E())
			m_bfmeDev->bfmeFinish976E();
	}
}
