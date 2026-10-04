// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5 conversions.

// Retail's 0x00046538 ILT thunk routes every BfmeKeyLC::bfmeFindLC call to
// GameWindow::winGetUserData (body 0x00478C70), and 0x0000A3DF / 0x00010857
// route the two tail calls to GadgetListBoxReset (0x004B7880) and
// GadgetListBoxGetNumEntries (0x004B77C0). Spelled under their real names the
// three references resolve; the scaffold spellings defined nothing.

#include "GameClient/GameWindow.h"
#include "GameClient/GadgetListBox.h"

struct BfmeNodeLC
{
	virtual void bfmeSlot92500();
	virtual void bfmeSlot92501();
	virtual void bfmeSlot92502();
	virtual void bfmeSlot92503();
	virtual void bfmeSlot92504();
	virtual void bfmeSlot92505();
	virtual void bfmeSlot92506();
	virtual void bfmeTail925B();
	char m_bfmePad0[4];
	void *m_bfmeP;
	char m_bfmePad1[0x10];
	unsigned short m_bfmeU;
	unsigned short m_bfmeV;
	char m_bfmePad2[0xc];
	void *m_bfmeQ;
	char m_bfmePad3[4];
	void *m_bfmeR;
};

class BfmeKeyLC
{
};

void bfmeGo925B(BfmeKeyLC *k)
{
	if (!k)
		return;
	BfmeNodeLC *o = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
	if (!o)
		return;
	o->bfmeTail925B();
}

class BfmeThing925C
{
public:
	void bfmeGo925C();
	BfmeKeyLC *m_bfmeKey;
};

void BfmeThing925C::bfmeGo925C()
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
		GadgetListBoxReset((GameWindow *)o->m_bfmeP);
	}
}

class BfmeThing925D
{
public:
	void bfmeGo925D(void *v);
	BfmeKeyLC *m_bfmeKey;
};

void BfmeThing925D::bfmeGo925D(void *v)
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
		BfmeNodeLC *p = (BfmeNodeLC *)((GameWindow *)o->m_bfmeP)->winGetUserData();
		p->m_bfmeR = v;
	}
}

class BfmeThing925E
{
public:
	int bfmeGo925E();
	BfmeKeyLC *m_bfmeKey;
};

int BfmeThing925E::bfmeGo925E()
{
	BfmeKeyLC *k = m_bfmeKey;
	if (!k)
		return 0;
	BfmeNodeLC *o = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
	return GadgetListBoxGetNumEntries((GameWindow *)o->m_bfmeP);
}