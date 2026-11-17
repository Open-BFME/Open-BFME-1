// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x001F8AB0, 155 bytes (cdecl, one argument): find an object's
// "DynamicPortalBehaviour" behavior module. The function-static name key is
// compared against each behavior module's getModuleNameKey (vtable +0x10)
// over the object's NULL-terminated behavior list at +0x1F0; the matching
// module or NULL is returned. It sits beside DynamicPortalBehaviour's own
// bodies (destructor 0x001F8D10) and is called through ILT 0x0002FC7A by
// Weapon::isGoalPosWithinAttackRange, the SiegeDeploy code and others.
//
// A naked lift named it WorkerAIUpdate::getModuleNameKey, a const no-argument
// virtual, which the body (an object argument read from the stack, ecx never
// used) refutes. Its EA name is not proven, so it keeps its address.
// Evidence: targets/game/reverse/identity_evidence/001f8ab0-dynamic-portal-lookup.md
#include "../../ScriptEngine/game_logic_dispatch.h"

extern NameKeyGenerator *TheNameKeyGenerator;
#define NULL 0
#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

class BehaviorModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual NameKeyType getModuleNameKey() const;	// +0x10
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
private:
	char m_unmodelled000[0x1f0];
	BehaviorModule **m_behaviors;			// +0x1F0
};

BehaviorModule *rva001F8AB0(Object *obj)
{
	static NameKeyType key_DynamicPortalBehaviour = NAMEKEY("DynamicPortalBehaviour");
	for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
	{
		if ((*m)->getModuleNameKey() == key_DynamicPortalBehaviour)
			return *m;
	}
	return NULL;
}
