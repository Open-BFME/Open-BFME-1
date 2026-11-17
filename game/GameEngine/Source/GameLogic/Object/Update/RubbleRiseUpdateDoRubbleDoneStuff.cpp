// cl: /DNDEBUG /MD /EHsc
// readable body of ?doRubbleDoneStuff@RubbleRiseUpdate@@IAEXXZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StructureCollapseUpdate.cpp
//
// RubbleRiseUpdate::doRubbleDoneStuff, 0x002A38A0, 123 bytes. BFME's
// RubbleRiseUpdate is a port of StructureCollapseUpdate; this is its copy of
// Zero Hour's doCollapseDoneStuff: stop the object's BoneFXUpdate effects.
// The matched RubbleRiseStep002A3B40::update reaches it through ILT 0x0000520E
// on the RubbleRiseUpdate root, and tools/ilt_oracle.py confirms this
// decoration at 0x002A38A0 (it contradicts doCollapseDoneStuff there; that
// name's body is 0x002AE520, StructureCollapseUpdate.cpp).
//
// Layout: the owning Object at +0x08 (UpdateModule).

typedef int Int;

#include "../../ScriptEngine/game_logic_dispatch.h"



extern NameKeyGenerator *TheNameKeyGenerator;

#define NULL 0
#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdate
{
public:
	void stopAllBoneFX(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }
protected:
	Module *findModule(NameKeyType key) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class RubbleRiseUpdate
{
protected:
	void doRubbleDoneStuff(void);
	Object *getObject() const { return m_object; }
private:
	char m_unmodelled000[0x08];
	Object *m_object;						// +0x08
};

void RubbleRiseUpdate::doRubbleDoneStuff()
{
	static NameKeyType key_BoneFXUpdate = NAMEKEY("BoneFXUpdate");
	BoneFXUpdate *bfxu = (BoneFXUpdate *)getObject()->findUpdateModule(key_BoneFXUpdate);
	if (bfxu != NULL)
	{
		bfxu->stopAllBoneFX();
	}
}
