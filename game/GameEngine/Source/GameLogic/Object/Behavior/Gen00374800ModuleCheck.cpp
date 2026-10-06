// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// cache-refresh: exact retail module-check candidate

typedef int ObjectID;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

extern void j_00008f7b();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	// Retail's Object::findModule (0x001BEE60) is a protected member, so the
	// mangled call name carries that access; only the friend may call it here.
protected:
	Module *findModule(NameKeyType key) const;
	friend class Gen_00374800;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

class Gen_00374800
{
public:
	void check(void *argument);

private:
	unsigned char m_pad00[8];
	ObjectID m_objectID;
};

struct Gen00374800Argument
{
	unsigned char m_pad00[0x50];
	float m_value;
};

void Gen_00374800::check(void *argument)
{
	Gen00374800Argument *value = (Gen00374800Argument *)argument;
	if (value->m_value > 0.0f) {
		Object *object = TheGameLogic->findObjectByID(
			m_objectID);
		if (object != 0) {
			static volatile NameKeyType key =
				TheNameKeyGenerator->nameToKey("CastleBehavior");
			NameKeyType lookup = key;
			Module *module = object->findModule(lookup);
			if (module != 0) {
				union { void (*fn)(); void (Module::*call)(void *); } notify = { j_00008f7b };
				(module->*notify.call)(argument);
			}
		}
	}
}
