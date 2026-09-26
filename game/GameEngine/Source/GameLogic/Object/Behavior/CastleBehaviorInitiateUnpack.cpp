// ?initiateUnpack@CastleBehavior@@QAEX_NPBVThingTemplate@@@Z
// CastleBehavior's pack/unpack state transition and retail CRC trace.
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

class Thing
{
public:
	void *m_vtable;
	ThingTemplate * volatile m_template;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Int getID() const { return m_id; }

private:
	unsigned char m_pad08[0x6c];
	volatile Int m_id;

public:
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

struct OwnedObjectNode
{
	void *m_pad00;
	OwnedObjectNode *m_field04;
	OwnedObjectNode * volatile m_field08;
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
			typedef void (OwnedObjectTree::*EraseCall)(OwnedObjectNode *);
			union { void *asVoid; EraseCall asMember; } eraseCast;
			eraseCast.asVoid = (void *)j_00047c58;
			OwnedObjectNode *header = m_header;
			(this->*eraseCast.asMember)(header->m_field04);
			m_header->m_field08 = m_header;
			*(volatile Int *)((char *)*(OwnedObjectNode * volatile *)((char *)this) + 4) = 0;
			OwnedObjectNode *tail = *(OwnedObjectNode * volatile *)((char *)this);
			tail->m_field0c = tail;
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

	if (TheBfmeGameLogic->m_packUnpackGate > 0)
	{
		void *crcParameterCheck = g_012ED4FC;
		if (!crcParameterCheck)
			return;

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
			{
				FinalOverrideCall finalOverrideCall;
				union { void *asVoid; FinalOverrideCall asMember; } finalOverrideCast;
				finalOverrideCast.asVoid = (void *)j_000022bb;
				finalTemplate = (const ThingTemplate *)
					(thingTemplate->m_nextOverride->*finalOverrideCast.asMember)();
			}
			else
				finalTemplate = thingTemplate;
		}

		const char *castleName = finalTemplate->m_name.str();

		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			(const char *)0x010E9D90, TheBfmeGameLogic->m_frame,
			castleName, castleID, callerName);
	}
}
