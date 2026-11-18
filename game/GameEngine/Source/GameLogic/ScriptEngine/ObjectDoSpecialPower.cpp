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

#include "../../../Include/Common/Enums/SpecialPowerType.h"




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

class AudioManager;
extern GameLogic *TheGameLogic;
extern AudioManager *TheAudio;
extern SpecialPowerStore *TheSpecialPowerStore;

// Retail calls ILT 0x00020F04, which jumps to the lookup at 0x000BA930.
// Preserve that route instead of selecting an unrelated inline COMDAT copy.
extern void j_00020f04();

#define TheAudioClientUpdate ((void *)TheAudio)

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
	const SpecialPowerTemplate *power;
	{
		typedef const SpecialPowerTemplate *(SpecialPowerStore::*Function)(AsciiString);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_00020f04;
		power = (TheSpecialPowerStore->*fn.member)(lua_tostring(state, 2));
	}
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
