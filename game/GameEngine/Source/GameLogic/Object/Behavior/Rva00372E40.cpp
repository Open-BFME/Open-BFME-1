// ?Rva00372E40@@YAHPAXHPBX_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /I.
// stlport
//
// Retail 0x00372E40, 280B. Identity: not a matched caller, but the string
// literal at the nameToKey call site reads "CastleMemberBehavior" (retail
// .rdata 0x01090D8C), and one callee is pinned to CastleBehavior::
// isPendingObjectUnavailable (0x00372090), matching the same
// local-static-key module lookup idiom already landed in
// CastleMemberBehaviorFind.cpp. Address-derived name kept per naming rules
// since no caller/vtable/name-key proves the enclosing function's own
// identity.

typedef bool Bool;

// Canonical direct callees and native override lifetime.

#define __PLACEMENT_VEC_NEW_INLINE
#define BFME_GAMELOGIC_LOOKUP_VISIBLE 1
#include "game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

#include "Common/GameMemory.h"
#include "Common/Overridable.h"
#include "Common/Override.h"
enum NameKeyType {};
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Player;
class ProjectileUpdateInterfaceView;
class ProjectileUpdateInterface;
class CastleBehavior { public: Bool isPendingObjectUnavailable() const; };
class ThingTemplate : public Overridable {
public:
 unsigned char m_pad0C[0xCC];
 unsigned int m_kindOf0xd8;
};
#define OBJECT_TU_MEMBERS public: Module *findModule(NameKeyType) const; Player *getControllingPlayer() const; ProjectileUpdateInterface *getProjectileUpdateInterface() const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"

// Inherited bank view for the two witnessed virtual slots. This does not
// establish EA slot names or a match to the differently shaped ZH interface.
class ProjectileUpdateInterfaceView
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual Bool queryStatus();
	virtual int fireAt(Object *object, const void *cArg, void *posAddr, int zero,
		void *player, bool flag);
};

// RET at00372F57; INT3 at00372F58. Caller00372FA0 tests the full EAX result.
// Its cArg is a pointer (caller reads +CC), forwarded without interpretation.
int Rva00372E40(void *unused, int id, const void *cArg, bool flag)
{
	GameLogic *gameLogic = TheGameLogic;
	Object *object = (Object *)gameLogic->findObjectByID(id);
	if (!object)
		return 0;

	const ThingTemplate *finalTemplate = OVERRIDE<ThingTemplate>(object->m_template);
	if (finalTemplate->m_kindOf0xd8 & 0x00200000)
		return 0;

	static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	Module *module = object->findModule(key);

	if (!flag)
	{
		if (module)
		{
			if (*(int *)((char *)module + 0x14))
			{
				if (((CastleBehavior *)module)->isPendingObjectUnavailable())
					return 0;
			}
		}
	}

	ProjectileUpdateInterfaceView *interface =
		(ProjectileUpdateInterfaceView *)object->getProjectileUpdateInterface();
	if (interface && !interface->queryStatus())
	{
		return interface->fireAt(object, cArg, object->m_cachedPos, 0,
			object->getControllingPlayer(), flag);
	}
	return 0;
}
