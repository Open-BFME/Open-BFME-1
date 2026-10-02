// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// Open-BFME5 conversions.

extern void *g_bfmeVftTDA[];

class BfmeSinkTDA
{
public:
	virtual void bfmeV0TDA() = 0;
	virtual void bfmeV1TDA() = 0;
	virtual void bfmeV2TDA() = 0;
	virtual void bfmeDropTDA(void *p, int f) = 0;
};

void *bfmeGo929C(void);

class BfmeThingTDA
{
public:
	void bfmeGoTDA();
	void *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeItem;
};

void BfmeThingTDA::bfmeGoTDA()
{
	m_bfmeVft = g_bfmeVftTDA;
	((BfmeSinkTDA *)bfmeGo929C())->bfmeDropTDA(m_bfmeItem, 0);
}

struct BfmeCallsTDB;

struct BfmeObjTDB
{
	BfmeCallsTDB *m_bfmeCalls;
};

struct BfmeCallsTDB
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	void *m_bfmeSlot7;
	void *m_bfmeSlot8;
	void *m_bfmeSlot9;
	void *m_bfmeSlot10;
	void *m_bfmeSlot11;
	void *m_bfmeSlot12;
	void *m_bfmeSlot13;
	void *m_bfmeSlot14;
	void *m_bfmeSlot15;
	void *m_bfmeSlot16;
	void *m_bfmeSlot17;
	void *m_bfmeSlot18;
	void *m_bfmeSlot19;
	void *m_bfmeSlot20;
	void *m_bfmeSlot21;
	void *m_bfmeSlot22;
	void *m_bfmeSlot23;
	void *m_bfmeSlot24;
	void *m_bfmeSlot25;
	void *m_bfmeSlot26;
	void *m_bfmeSlot27;
	void *m_bfmeSlot28;
	void *m_bfmeSlot29;
	void *m_bfmeSlot30;
	void *m_bfmeSlot31;
	void *m_bfmeSlot32;
	void *m_bfmeSlot33;
	void *m_bfmeSlot34;
	void *m_bfmeSlot35;
	void *m_bfmeSlot36;
	void *m_bfmeSlot37;
	void *m_bfmeSlot38;
	void *m_bfmeSlot39;
	void *m_bfmeSlot40;
	void *m_bfmeSlot41;
	void *m_bfmeSlot42;
	void *m_bfmeSlot43;
	void *m_bfmeSlot44;
	void *m_bfmeSlot45;
	void *m_bfmeSlot46;
	void *m_bfmeSlot47;
	void *m_bfmeSlot48;
	void *m_bfmeSlot49;
	void *m_bfmeSlot50;
	void *m_bfmeSlot51;
	void *m_bfmeSlot52;
	void *m_bfmeSlot53;
	void *m_bfmeSlot54;
	void *m_bfmeSlot55;
	void *m_bfmeSlot56;
	void *m_bfmeSlot57;
	void *m_bfmeSlot58;
	void *m_bfmeSlot59;
	void *m_bfmeSlot60;
	void *m_bfmeSlot61;
	void *m_bfmeSlot62;
	void *m_bfmeSlot63;
	void *m_bfmeSlot64;
	void *m_bfmeSlot65;
	void *m_bfmeSlot66;
	void *m_bfmeSlot67;
	void *m_bfmeSlot68;
	void *m_bfmeSlot69;
	void *m_bfmeSlot70;
	void *m_bfmeSlot71;
	void *m_bfmeSlot72;
	void *m_bfmeSlot73;
	void *m_bfmeSlot74;
	void *m_bfmeSlot75;
	void *m_bfmeSlot76;
	void *m_bfmeSlot77;
	void *m_bfmeSlot78;
	void *m_bfmeSlot79;
	void *m_bfmeSlot80;
	void *m_bfmeSlot81;
	void *m_bfmeSlot82;
	void *m_bfmeSlot83;
	void *m_bfmeSlot84;
	void *m_bfmeSlot85;
	void *m_bfmeSlot86;
	void *m_bfmeSlot87;
	void *m_bfmeSlot88;
	void *m_bfmeSlot89;
	void *m_bfmeSlot90;
	void *m_bfmeSlot91;
	void (__stdcall *m_bfmeRunTDB)(BfmeObjTDB *o, int f);
};

extern int g_bfmeCountTDB;
extern char g_bfmeDoneTDB;

void bfmeStepTDB(void);

void bfmeGoTDB(void)
{
	reinterpret_cast<BfmeObjTDB *>(DX8Wrapper::_Get_D3D_Device8())->m_bfmeCalls->m_bfmeRunTDB(reinterpret_cast<BfmeObjTDB *>(DX8Wrapper::_Get_D3D_Device8()), 0);
	++g_bfmeCountTDB;
	bfmeStepTDB();
	g_bfmeDoneTDB = 1;
}
