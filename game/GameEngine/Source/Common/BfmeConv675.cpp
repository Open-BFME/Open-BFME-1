// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BfmeOtherDCE only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

extern "C" unsigned char bfmeInfoDCE[];

class BfmeThingDCE;

class BfmeOtherDCE;

class BfmeThingDCE
{
public:
	void bfmeGoDCE(BfmeOtherDCE *other);
};

void BfmeThingDCE::bfmeGoDCE(BfmeOtherDCE *other)
{
	reinterpret_cast<INI *>(other)->initFromINI(this, (const FieldParse *)bfmeInfoDCE);
}
