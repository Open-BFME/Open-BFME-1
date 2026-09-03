// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// cache-refresh: exact retail module-check candidate

typedef int ObjectID;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#pragma comment(linker, "/alternatename:?notify@Module@@QAEXPAX@Z=?j_00008f7b@@YAXXZ")

class Module
{
public:
	void notify(void *argument);
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

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
	if (value->m_value > *(float *)0x01075350) {
		Object *object = ((GameLogic *)*(GameLogic **)0x012f0898)->findObjectByID(
			m_objectID);
		if (object != 0) {
			static volatile NameKeyType key =
				TheNameKeyGenerator->nameToKey((const char *)0x01083c50);
			NameKeyType lookup = key;
			Module *module = object->findModule(lookup);
			if (module != 0)
				module->notify(argument);
		}
	}
}
