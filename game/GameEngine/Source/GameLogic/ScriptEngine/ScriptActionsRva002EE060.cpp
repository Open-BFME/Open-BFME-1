// cl: /DNDEBUG /MD /EHsc
// readable body of ?rva002EE060@ScriptActions@@IAEXABVAsciiString@@MMMMH@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Retail 0x002EE060, 118 bytes (ret 0x18). The body is Zero Hour's
// ScriptActions::doRotateCameraTowardObject: look up the named unit and, if
// it exists, ask TheTacticalView to rotate toward it with the time and hold
// converted to integer milliseconds and the two ease values scaled to
// milliseconds as Reals.
//
// BFME takes a sixth argument that is forwarded untouched to the view's
// rotate call (View vtable slot 51, +0xCC). ret 0x18 proves the arity, so
// the ledger's five-argument doRotateCameraTowardObject decoration cannot
// be this body, and tools/ilt_oracle.py contradicts every six-argument
// spelling tried (int, float, bool, pointer and enum tails; protected,
// private, public, static and stdcall forms). The EA name is unproven, so
// the method keeps its address. The sixth argument is declared Int: it is
// only copied as a dword. Evidence:
// targets/game/reverse/identity_evidence/002ee060-rotate-camera-toward-object.md
//
// Layout: Object id +0x74; ScriptEngine::getUnitNamed is vtable slot 26
// (+0x68).
#include "../../../Include/Common/ScalarTypes.h"

#include "../../../Include/Common/ObjectID.h"
class AsciiString;

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();
#define BFME_VIRTUAL_SLOT10(n) BFME_VIRTUAL_SLOT(n##0) BFME_VIRTUAL_SLOT(n##1) \
	BFME_VIRTUAL_SLOT(n##2) BFME_VIRTUAL_SLOT(n##3) BFME_VIRTUAL_SLOT(n##4) \
	BFME_VIRTUAL_SLOT(n##5) BFME_VIRTUAL_SLOT(n##6) BFME_VIRTUAL_SLOT(n##7) \
	BFME_VIRTUAL_SLOT(n##8) BFME_VIRTUAL_SLOT(n##9)

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_unmodelled000[0x74];
	ObjectID m_id;							// +0x74
};

class ScriptEngine
{
public:
	BFME_VIRTUAL_SLOT10(0) BFME_VIRTUAL_SLOT10(1)
	BFME_VIRTUAL_SLOT(20) BFME_VIRTUAL_SLOT(21) BFME_VIRTUAL_SLOT(22)
	BFME_VIRTUAL_SLOT(23) BFME_VIRTUAL_SLOT(24) BFME_VIRTUAL_SLOT(25)
	virtual Object *getUnitNamed(const AsciiString &unitName);	// slot 26, +0x68
};
extern ScriptEngine *TheScriptEngine;

class View
{
public:
	BFME_VIRTUAL_SLOT10(0) BFME_VIRTUAL_SLOT10(1) BFME_VIRTUAL_SLOT10(2)
	BFME_VIRTUAL_SLOT10(3) BFME_VIRTUAL_SLOT10(4)
	BFME_VIRTUAL_SLOT(50)
	virtual void rotateCameraTowardObject(ObjectID id, Int milliseconds, Int holdMilliseconds,
		Real easeIn, Real easeOut, Int extra);			// slot 51, +0xCC
};
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void rva002EE060(const AsciiString &unitName, Real sec, Real holdSec, Real easeIn, Real easeOut, Int extra);
};

void ScriptActions::rva002EE060(const AsciiString &unitName, Real sec, Real holdSec, Real easeIn, Real easeOut, Int extra)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (unit)
	{
		TheTacticalView->rotateCameraTowardObject(unit->getID(), sec*1000.0f, holdSec*1000.0f,
			easeIn*1000.0f, easeOut*1000.0f, extra);
	}
}
