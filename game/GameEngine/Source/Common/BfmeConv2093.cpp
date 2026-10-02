// cl: /DNDEBUG /MD /Igame/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#include "../../Include/GameLogic/Module/UpdateModule.h"
#include "../GameLogic/Object/object.h"

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadXW[0x3c];
	int m_bfme3CXW;
};

// Rva00367E30Logic exposes the frame read from the game-logic singleton.
class GameLogic;

extern GameLogic *TheGameLogic;

class ObjectHelper : public UpdateModule
{
public:
	void sleepUntil(UnsignedInt when);
};

struct Rva00256CD0Helper
{
	unsigned char m_unmodelled[8];
	Object *m_object;
};

void ObjectHelper::sleepUntil(UnsignedInt when)
{
	Object *obj = reinterpret_cast<Rva00256CD0Helper *>(this)->m_object;

	if (reinterpret_cast<const unsigned char *>(obj->m_status)[0] & 1)
		return;

	UpdateSleepTime wakeDelay;

	if (when != 0 && when != 0x3fffffff)
		wakeDelay = UPDATE_SLEEP(when - ((Rva00367E30Logic *)TheGameLogic)->m_bfme3CXW);
	else
		wakeDelay = UPDATE_SLEEP_FOREVER;

	setWakeFrame(obj, wakeDelay);
}
