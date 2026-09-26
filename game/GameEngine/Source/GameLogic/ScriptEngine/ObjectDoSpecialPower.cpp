// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *state, int index);

#include "ascii_string.h"

class Rva002E64C0Name : public AsciiString
{
public:
	Rva002E64C0Name(const char *text) : AsciiString(text) {}
};

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum SpecialPowerType
{
	SPECIAL_POWER_TYPE_UNKNOWN = 0
};

class SpecialPowerTemplate
{
public:
	SpecialPowerType getSpecialPowerType() const;
};

class SpecialPowerModuleInterface
{
public:
	virtual Bool isModuleForPower(const SpecialPowerTemplate *) const = 0;
	virtual Bool isReady() const = 0;
	virtual void slot02() const = 0;
	virtual void slot03() const = 0;
	virtual void slot04() const = 0;
	virtual void slot05() const = 0;
	virtual void slot06() const = 0;
	virtual void slot07() const = 0;
	virtual void slot08() const = 0;
	virtual void slot09() const = 0;
	virtual void slot10() const = 0;
	virtual void doSpecialPower(UnsignedInt commandOptions) = 0;
};

class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheAudioClientUpdate (*(void **)0x012ED668)
#define TheSpecialPowerStore (*(SpecialPowerStore **)0x012ED80C)

// ?ObjectDoSpecialPower@@YAHPAUlua_State@@@Z
int ObjectDoSpecialPower(lua_State *state)
{
	if (lua_gettop(state) < 2 || !TheAudioClientUpdate)
		return 0;
	unsigned id = Rva00990030Lookup(state, 1);
	if (!id && lua_type(state, 1) != 1)
		return 0;
	Object *object = TheGameLogic->findObjectByID(id);
	if (!object)
		return 0;
	const SpecialPowerTemplate *power =
		TheSpecialPowerStore->findSpecialPowerTemplate(lua_tostring(state, 2));
	if (!power)
		return 0;
	SpecialPowerModuleInterface *module =
		object->findSpecialPowerModuleInterface(power->getSpecialPowerType());
	if (!module)
		return 0;
	if (module->isReady())
		module->doSpecialPower(0);
	return 1;
}
