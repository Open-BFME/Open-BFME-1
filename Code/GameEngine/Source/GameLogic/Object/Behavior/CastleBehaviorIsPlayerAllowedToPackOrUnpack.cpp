// ?isPlayerAllowedToPackOrUnpack@CastleBehavior@@QAE_NPAVPlayer@@_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
#pragma optimize("a", on)

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) :
			(const char *)0x0107388B;
	}

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_pad00[0x1c];
	AsciiString m_playerName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x18];
	AsciiString m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void *m_vtable;
	ThingTemplate * volatile m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Int getID() const { return m_id; }

private:
	unsigned char m_pad08[0x6c];
	volatile Int m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	Int m_frame;
	unsigned char m_pad40[0x160];
	Int m_packUnpackGate;
};

class CastleBehaviorModuleData
{
};

class CastleBehavior
{
public:
	Bool isPlayerAllowedToPackOrUnpack(Player *player,
		Bool playerAllowedToPackOrUnpack);

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;
	Object *m_object;
};

extern void *g_012ED4FC;
extern GameLogic *TheGameLogic;
extern void b_0036fd20(void);
extern "C" void bfmeRetailCritterDesyncLog(void *context,
	const char *format, ...);

typedef Bool (CastleBehavior::*AllowedCall)(Player *, Bool);
typedef void (__cdecl *DebugLogFunction)(void *, const char *, ...);

Bool CastleBehavior::isPlayerAllowedToPackOrUnpack(Player *player,
	Bool playerAllowedToPackOrUnpack)
{
	Object *object = m_object;
	Bool alreadyMyCastle = player == object->getControllingPlayer();

	AllowedCall allowedCall;
	union { void *asVoid; AllowedCall asMember; } allowedCast;
	allowedCast.asVoid = (void *)b_0036fd20;
	Bool allowed = (this->*allowedCast.asMember)(player,
		playerAllowedToPackOrUnpack);

	GameLogic *logic = TheGameLogic;
	if (logic->m_packUnpackGate > 0 && g_012ED4FC)
	{
		const char *callerName = object->getControllingPlayer()->m_playerName.str();
		const Int castleID = object->getID();
		const ThingTemplate *thingTemplate = object->m_template;
		const ThingTemplate *finalTemplate = thingTemplate;
		if (thingTemplate == 0)
		{
			finalTemplate = (const ThingTemplate *)0;
		}
		else
		{
			if (thingTemplate->m_nextOverride)
				finalTemplate = (const ThingTemplate *)
					thingTemplate->m_nextOverride->getFinalOverride();
			else
				finalTemplate = thingTemplate;
		}
		const char *castleName =
			finalTemplate->m_name.str();

		((DebugLogFunction)bfmeRetailCritterDesyncLog)(g_012ED4FC,
			(const char *)0x010E9A68, TheGameLogic->m_frame,
			castleName, castleID, callerName, alreadyMyCastle,
			allowed);
	}

	return alreadyMyCastle ? true : allowed;
}
