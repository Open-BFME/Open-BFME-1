// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// Retail 0x00138520 (278 bytes, ret 0x10) is ThingFactory::newObject. The
// retail "newObj %s id %i" string, the ThingFactory.cpp assert path and
// thirteen named callers prove that identity.
// BFME keeps the Zero Hour shape: pick a build variation, have GameLogic create
// the Object, run each behavior's create module, then initObject. It returns 0
// for a null template, adds a Sleep(0) debug hook and logs the new object.
// Calls: GetGameLogicRandomValue via ILT 0x00001BAE; findTemplate via ILT
// 0x00028560 -> 0x00137E80; GameLogic::friend_createObject via ILT 0x000168DD
// -> 0x003830C0; the CRCParameterCheck logger via ILT 0x0003A17A -> 0x00065C80.
// The build variations must be the real std::vector read through the ZH
// getBuildVariations()/empty()/size()/operator[] inlines. Raw begin/end
// pointers compile to the same variation code but rotate the registers of the
// friend_createObject argument shuttle (extra/team/statusBits).
// The status mask is three DWORDs, as both hub calls independently witness.

#define _STLP_NO_EXCEPTIONS 1

#include "StringInline.h"
#include <vector>

typedef unsigned int UnsignedInt;

template <int N>
class BitFlags
{
public:
	UnsignedInt m_words[3];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object;
class Team;
class CRCParameterCheck;

class ThingTemplate
{
public:
	const std::vector<AsciiString> &getBuildVariations() const
	{
		return m_buildVariations;
	}

	unsigned char m_pad00[0x20];
	AsciiString m_name;
	unsigned char m_pad24[0x2ac];
	std::vector<AsciiString> m_buildVariations;
};

class GameLogic
{
public:
	Object *friend_createObject(const ThingTemplate *thing,
		const ObjectStatusMaskType &statusBits, Team *team, UnsignedInt extra);
};

class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

private:
	UnsignedInt m_data[2];
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
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
	virtual void initObject() = 0;

	unsigned char m_pad04[0x70];
	UnsignedInt m_id;
	unsigned char m_pad78[0x178];
	BehaviorModule **m_behaviors;
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const ObjectStatusMaskType &statusBits, UnsignedInt extra);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

extern unsigned char g_Va012EF1DC;
extern GameLogic *TheGameLogic;
extern CRCParameterCheck *TheCRCParameterCheck;

Object *ThingFactory::newObject(const ThingTemplate *thingTemplate, Team *team,
	const ObjectStatusMaskType &statusBits, UnsignedInt extra)
{
	if (thingTemplate == 0)
		return 0;

	if (g_Va012EF1DC)
		Sleep(0);

	const std::vector<AsciiString> &buildVariations = thingTemplate->getBuildVariations();
	if (!buildVariations.empty())
	{
		int variationIndex = GetGameLogicRandomValue(0, buildVariations.size() - 1,
			"F:\\bfme\\Code\\gameengine\\Source\\Common\\Thing\\ThingFactory.cpp",
			0x184);
		const ThingTemplate *variationTemplate = findTemplate(buildVariations[variationIndex]);
		if (variationTemplate != 0)
			thingTemplate = variationTemplate;
	}

	Object *createdObject = TheGameLogic->friend_createObject(
		thingTemplate, statusBits, team, extra);

	for (BehaviorModule **behaviorModule = createdObject->m_behaviors; *behaviorModule != 0; ++behaviorModule)
	{
		if (g_Va012EF1DC)
			Sleep(0);
		CreateModuleInterface *createModule = (*behaviorModule)->getCreate();
		if (createModule != 0)
			createModule->onCreate();
	}

	if (g_Va012EF1DC)
		Sleep(0);
	createdObject->initObject();

	if (g_Va012EF1DC)
		Sleep(0);
	if (TheCRCParameterCheck != 0)
	{
		UnsignedInt objectID = createdObject->m_id;
		const char *templateName = thingTemplate->m_name.str();
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "newObj %s id %i",
			templateName, objectID);
	}

	return createdObject;
}
