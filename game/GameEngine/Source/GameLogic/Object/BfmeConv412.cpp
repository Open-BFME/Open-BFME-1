// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BfmeSinkANB only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

// bfmeTagANB is the FieldParse table; the other name is the pinned empty-string
// literal (symbols.csv ?g_Rva0107301CEmptyString@@3QBDB, RVA 0x00C7301C), for
// which the census alias _bfmeEmptyANB was a placeholder.
extern "C" unsigned char bfmeTagANB[];
extern const char g_Rva0107301CEmptyString[];

class BfmeSlotANB
{
public:
	void bfmeSetANB(void *text, int flag);
	unsigned char m_bfmeHead[4];
};

class BfmeSinkANB;
class ThingTemplate;

class LocomotorSet
{
public:
	void setLocomotorAndBaseSpeed(INI *ini, ThingTemplate *thing);
	void bfmeInitANB(BfmeSinkANB *sink, void *what);
	unsigned char m_bfmeHead[0x18];
	BfmeSlotANB m_bfmeA;
	BfmeSlotANB m_bfmeB;
	int m_bfmeFlag;
};

void LocomotorSet::bfmeInitANB(BfmeSinkANB *sink, void *what)
{
	m_bfmeA.bfmeSetANB((void *)g_Rva0107301CEmptyString, 0);
	m_bfmeB.bfmeSetANB((void *)g_Rva0107301CEmptyString, 0);
	m_bfmeFlag = 0;
	reinterpret_cast<INI *>(sink)->initFromINI(this, (const FieldParse *)bfmeTagANB);
	setLocomotorAndBaseSpeed(reinterpret_cast<INI *>(sink), (ThingTemplate *)what);
}
