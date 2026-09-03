// cl: /DNDEBUG /MD /EHsc

enum NameKeyType { };
typedef int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual void moduleSlot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateSlot();
};
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GateOpenAndCloseBehavior : public UpdateModule, public Module { };

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00128780GateBehaviorOwner
{
public:
	bool resolveGateBehavior();

private:
	char m_pad0[0x24];
	ObjectID m_objectID;
	char m_pad28[0x24];
	GateOpenAndCloseBehavior *m_gateBehavior;
};

bool Rva00128780GateBehaviorOwner::resolveGateBehavior()
{
	if (m_objectID == 0)
		return false;

	Object *object = TheGameLogic->findObjectByID(m_objectID);
	if (object == 0)
		return false;

	static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	m_gateBehavior = static_cast<GateOpenAndCloseBehavior *>(object->findModule(gateKey));
	if (m_gateBehavior != 0)
		return true;

	return false;
}
