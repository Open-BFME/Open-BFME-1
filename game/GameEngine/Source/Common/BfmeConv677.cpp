// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BfmeOtherDCG only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

extern "C" unsigned char bfmeInfoDCG[];

class BfmeThingDCG;

class BfmeOtherDCG;

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);
};

void BfmeThingDCG::bfmeGoDCG(BfmeOtherDCG *other)
{
	reinterpret_cast<INI *>(other)->initFromINI(this, (const FieldParse *)bfmeInfoDCG);
}
