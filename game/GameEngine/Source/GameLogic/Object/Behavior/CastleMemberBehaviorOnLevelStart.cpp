// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "Common/Debug.h"
#ifndef DEBUG_ASSERTCRASH
#define DEBUG_ASSERTCRASH(condition, message) ((void)0)
#ifndef DEBUG_CRASH
#define DEBUG_CRASH(message) ((void)0)
#endif

#endif

#include "Common/AsciiString.h"
#include "Common/NameKeyGenerator.h"

class Module;

#define BFME_HAVE_ASCIISTRING
#define OBJECT_TU_MEMBERS Module *findModule(NameKeyType) const;
#include "object.h"
#undef OBJECT_TU_MEMBERS
#undef BFME_HAVE_ASCIISTRING

class Dict;
extern const StaticNameKey g_012A7838;

struct Rva00374610StringData
{
	Int m_references;
	UnsignedShort m_length;
	UnsignedShort m_padding;
	Char m_text[1];
};

class BfmeStringPresenceValue
{
public:
	~BfmeStringPresenceValue();

	Int compare(const BfmeStringPresenceValue &other) const
	{
		const Int otherLength = other.m_data ? other.m_data->m_length : 0;
		const Char *otherText = other.m_data ? other.m_data->m_text : "";
		const Int thisLength = m_data ? m_data->m_length : 0;
		const Char *thisText = m_data ? m_data->m_text : "";
		const Int length = thisLength < otherLength ? thisLength : otherLength;
		const Int result = memcmp(thisText, otherText, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	Bool operator!=(const BfmeStringPresenceValue &other) const
	{
		return compare(other) != 0;
	}

private:
	Rva00374610StringData *m_data;
};

class BfmeStringPresenceDict
{
public:
	BfmeStringPresenceValue getAsciiString(Int key, Bool *exists) const;
};

class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

class CastleBehavior
{
public:
	void registerOwnedObject(Object *object);
};

class CastleMemberBehavior
{
public:
	virtual void onLevelStart(Dict *properties);
};

static __forceinline Int &rva00374610Field(Int *base, Int offset)
{
	return *(Int *)((Char *)base + offset);
}

void CastleMemberBehavior::onLevelStart(Dict *properties)
{
	if (!properties)
		return;

	Bool exists = false;
	BfmeStringPresenceValue name =
		((const BfmeStringPresenceDict *)properties)->getAsciiString(
			g_012A7838.key(), &exists);
	if (!exists)
		return;

	Object *object = TheGameLogic->getFirstObject();
	while (object)
	{
		if (((const BfmeStringPresenceValue *)&object->m_name)->compare(name) == 0)
			break;
		object = object->m_next;
	}
	if (!object)
		return;

	static NameKeyType castleBehaviorKey =
		TheNameKeyGenerator->nameToKey("CastleBehavior");
	CastleBehavior *behavior = (CastleBehavior *)object->findModule(castleBehaviorKey);
	if (behavior)
	{
		Object *owner = *(Object **)((Char *)this - 4);
		if (owner)
		{
			behavior->registerOwnedObject(owner);
			rva00374610Field((Int *)behavior, 0x9C) = 4;
		}
	}
}
