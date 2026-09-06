// ?initiateUnpack@CastleBehavior@@QAEX_NPBVThingTemplate@@@Z
// partial score=0.95 date=2026-09-06
// ?initiateUnpack@CastleBehavior@@QAEX_NPBVThingTemplate@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
#pragma optimize("a", on)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class ObjectStatus
{
public:
	UnsignedInt operator&(UnsignedInt mask) const { return m_value & mask; }
	void operator|=(UnsignedInt mask) { m_value |= mask; }

private:
	UnsignedInt m_value;
};

class UnicodeString
{
public:
	void set(const UnicodeString &that);

private:
	void *m_data;
};

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

class Player
{
public:
	unsigned char m_pad00[0x1c];
	AsciiString m_playerName;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x18];
	AsciiString m_name;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Int getID() const { return m_id; }
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x6c];
	volatile Int m_id;
	unsigned char m_pad78[0xb0];
	ObjectStatus m_status;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	Int m_frame;
	unsigned char m_pad40[0x160];
	Int m_packUnpackGate;
};

extern void j_00047c58(void);
struct OwnedObjectNode;
struct OwnedObjectTree;
typedef void (OwnedObjectTree::*EraseCall)(OwnedObjectNode *);

struct OwnedObjectNode
{
	void *m_pad00;
	OwnedObjectNode *m_field04;
	OwnedObjectNode *m_field08;
	OwnedObjectNode *m_field0c;
};

struct OwnedObjectTree
{
	OwnedObjectNode *m_header;
	Int m_size;

	void clear()
	{
		if (m_size != 0)
		{
			EraseCall eraseCall;
			union { void *asVoid; EraseCall asMember; } eraseCast;
			eraseCast.asVoid = (void *)j_00047c58;
			(this->*eraseCast.asMember)(m_header->m_field04);
			m_header->m_field08 = m_header;
			m_header->m_field04 = 0;
			m_header->m_field0c = m_header;
			m_size = 0;
		}
	}
};

class CastleBehaviorModuleData
{
};

class CastleBehavior
{
public:
	void initiateUnpack(Bool, const ThingTemplate *);

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x90];
	Int m_state;
	unsigned char m_pad_a0[0x60];
	UnicodeString m_objectName;
	Int m_objectNameKey;
	OwnedObjectTree m_ownedObjects;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define g_012ED4FC (*(void **)0x012ED4FC)
extern void j_000084d6(void);
extern void j_0002191d(void);
extern void j_000022bb(void);
extern void j_00020824(void);
extern void j_0003a17a(void);

typedef void (CastleBehavior::*BoolCall)(Int);
typedef void (Object::*NotifyCall)();
typedef Player *(Object::*ControllingPlayerCall)() const;
typedef const Overridable *(Overridable::*FinalOverrideCall)() const;
typedef void (__cdecl *DebugLogFunction)(void *, const char *, ...);

void CastleBehavior::initiateUnpack(Bool unpack,
	const ThingTemplate *thingTemplate)
{
	Object *object = m_object;
	if (thingTemplate)
	{
		m_objectName.set(*(const UnicodeString *)((const unsigned char *)thingTemplate + 0x20));
	}

	if (unpack)
	{
		BoolCall unpackCall;
		union { void *asVoid; BoolCall asMember; } unpackCast;
		unpackCast.asVoid = (void *)j_000084d6;
		(this->*unpackCast.asMember)(1);

		if ((object->m_status & 0x8000) == 0)
		{
			object->m_status |= 0x8000;
			NotifyCall notifyCall;
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			(object->*notifyCast.asMember)();
		}

		m_state = 4;
	}
	else
	{
		m_state = 1;
	}

	m_ownedObjects.clear();

	GameLogic *logic = TheBfmeGameLogic;
	if (logic->m_packUnpackGate > 0)
	{
		void *crcParameterCheck = g_012ED4FC;
		if (!crcParameterCheck)
			return;

			ControllingPlayerCall controllingPlayerCall;
			union { void *asVoid; ControllingPlayerCall asMember; } controllingPlayerCast;
			controllingPlayerCast.asVoid = (void *)j_00020824;
			const char *callerName = (object->*controllingPlayerCast.asMember)()->m_playerName.str();
			const Int castleID = object->getID();
			const ThingTemplate *castleTemplate = object->m_template;
			const ThingTemplate *finalTemplate = castleTemplate;
			if (castleTemplate == 0)
			{
				finalTemplate = (const ThingTemplate *)0;
			}
			else
			{
				if (castleTemplate->m_nextOverride)
				{
					FinalOverrideCall finalOverrideCall;
					union { void *asVoid; FinalOverrideCall asMember; } finalOverrideCast;
					finalOverrideCast.asVoid = (void *)j_000022bb;
					finalTemplate = (const ThingTemplate *)
						(castleTemplate->m_nextOverride->*finalOverrideCast.asMember)();
				}
				else
					finalTemplate = castleTemplate;
			}
			const char *castleName = (const char *)0x0107388B;
			if (finalTemplate)
				castleName = finalTemplate->m_name.str();

			((DebugLogFunction)j_0003a17a)(g_012ED4FC,
				(const char *)0x010E9D90, logic->m_frame,
				castleName, castleID, callerName);
	}
}
