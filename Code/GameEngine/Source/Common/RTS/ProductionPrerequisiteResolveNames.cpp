// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ProductionPrerequisite::resolveNames uses the BFME one-argument factory
// facade and releases each source name through the retail AsciiString body.
// The ABI views below are deliberately local to this TU: the tagged string
// release symbol is pinned only to the retail 0x00887940 body and does not
// reuse ProductionPrerequisite::PrereqUnitRec's distinct weak destructor
// instances used by the existing vector callers.

#include "PreRTS.h"

#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

void ProductionPrerequisite::resolveNames()
{
	for (Int i = 0; i < m_prereqUnits.size(); i++)
	{
		m_prereqUnits[i].unit =
			((BfmeThingFactory *)TheThingFactory)->findTemplate(m_prereqUnits[i].name);
		((BFMERetailAsciiString *)&m_prereqUnits[i].name)->releaseBuffer();
	}
}
