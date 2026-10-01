// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BfmeSinkANB only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

extern "C" unsigned char bfmeEmptyANB[];
extern "C" unsigned char bfmeTagANB[];

class BfmeSlotANB
{
public:
	void bfmeSetANB(void *text, int flag);
	unsigned char m_bfmeHead[4];
};

class BfmeThingANB;

class BfmeSinkANB;

class BfmeThingANB
{
public:
	void bfmeFinishANB(BfmeSinkANB *sink, void *what);
	void bfmeInitANB(BfmeSinkANB *sink, void *what);
	unsigned char m_bfmeHead[0x18];
	BfmeSlotANB m_bfmeA;
	BfmeSlotANB m_bfmeB;
	int m_bfmeFlag;
};

void BfmeThingANB::bfmeInitANB(BfmeSinkANB *sink, void *what)
{
	m_bfmeA.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeB.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeFlag = 0;
	reinterpret_cast<INI *>(sink)->initFromINI(this, (const FieldParse *)bfmeTagANB);
	bfmeFinishANB(sink, what);
}
