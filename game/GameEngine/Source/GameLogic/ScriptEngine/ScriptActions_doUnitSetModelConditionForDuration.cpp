// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail action-template 434, UNIT_SET_MODELCONDITION_FOR_DURATION, RVA 0x002FABE0.
// The final callee is retained under its decoded address because its owner is unresolved.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern "C" const char *bfmeGlobalTable12A6918[];

class Rva001D02C0Object
{
public:
	void callRva001D02C0(Int condition, Int frames, Int percent);
};

#pragma comment(linker, "/alternatename:?callRva001D02C0@Rva001D02C0Object@@QAEXHHH@Z=?j_00049d73@@YAXXZ")

class ScriptActions
{
protected:
	void doUnitSetModelConditionForDuration(
		const AsciiString &unitName, const AsciiString &conditionName,
		Real duration, Int percent);
};

void ScriptActions::doUnitSetModelConditionForDuration(
	const AsciiString &unitName, const AsciiString &conditionName,
	Real duration, Int percent)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	register Int condition;
	condition = 0;
	Int frames;
	for (; condition < 0x130; ++condition)
	{
		AsciiString name(bfmeGlobalTable12A6918[condition]);
		if (conditionName.compare(name) == 0)
		{
			frames = (Int)(duration * (*(const Real *)0x01075344));
			goto matched;
		}
	}
	return;

matched:
	((Rva001D02C0Object *)unit)->callRva001D02C0(
		condition, frames, percent);
}
