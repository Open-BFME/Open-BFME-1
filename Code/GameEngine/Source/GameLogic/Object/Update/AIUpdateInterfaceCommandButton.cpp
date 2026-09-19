// cl: /DNDEBUG /MD
//
// Open-BFME: the two AIUpdateInterface command-button handlers.
//
//   ?privateCommandButtonPosition@  0x0027A2F0, 104 bytes
//   ?privateCommandButtonObject@    0x0027A380, 486 bytes
//
// Adjacent in the retail image and the same opening: reject a null button, take
// the owning object out of m_object, walk its template's override chain, refuse
// if the template carries kind-of bit 25 (KINDOF_PROJECTILE), then ask
// TheControlBar for the owner's command set and walk its first twenty buttons.
// What retail does inside that loop is the whole difference between the two:
// the position handler does nothing with the button it finds, which is why it
// is 104 bytes, while the object handler builds four AsciiStrings from the two
// templates and the two objects' names and then drops them -- 486 bytes of
// debug-print scaffolding whose format call was removed and whose string
// construction was not.
//
// Both files declared the object pointer as `Object * volatile m_object` and
// both reached the template through a volatile byte cast rather than through
// Thing::m_template. That is not two coincidences: it is one body's shape,
// written twice, and the volatile is what keeps the reload where retail put it.
//
// The two accounts of Object were disjoint and neither was wrong: the position
// handler modelled the AIUpdateInterface back-pointer at +0x204 and stopped
// there, the object handler modelled the name at +0x84 and stopped there. Both
// are below. So is CommandSourceType, which the position handler declared as a
// single `COMMAND_SOURCE_UNKNOWN = 0` -- neither body reads the value, and the
// object handler's file already carried the real list.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class CommandButton;
struct Coord3D;
class AIUpdateInterface;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI,
	CMD_FROM_DOZER,
	CMD_DEFAULT_SWITCH_WEAPON
};

enum KindOfType
{
	KINDOF_PROJECTILE = 25				// the 0x02000000 both bodies test
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString text, ...);
	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
	Bool isNotEmpty() const
	{
		return m_data != 0 && m_data->m_length != 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xC8 - 8];
	UnsignedInt m_kindOf[3];					// +0xC8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual void slot00();

	ThingTemplate *m_template;					// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	const AsciiString &getCommandSetString() const;
	const AsciiString &getName() const
	{
		return *reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(this) + 0x84);
	}

	unsigned char m_pad08[0x204 - 8];
	AIUpdateInterface *m_ai;					// +0x204
};

static ThingTemplate *getObjectTemplate(Object *object)
{
	volatile unsigned char *objectBytes =
		reinterpret_cast<volatile unsigned char *>(object);
	objectBytes += 4;
	ThingTemplate *objectTemplate =
		*reinterpret_cast<ThingTemplate * volatile *>(objectBytes);
	if (objectTemplate == 0)
		return 0;
	if (objectTemplate->m_nextOverride != 0)
		objectTemplate =
			(ThingTemplate *)objectTemplate->m_nextOverride->getFinalOverride();
	return objectTemplate;
}

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateCommandButtonPosition(const CommandButton *commandButton,
		const Coord3D *position, CommandSourceType commandSource);
	virtual void privateCommandButtonObject(const CommandButton *commandButton,
		Object *obj, CommandSourceType commandSource);

	unsigned char m_pad04[4];
	Object * volatile m_object;					// +0x08
};

void AIUpdateInterface::privateCommandButtonPosition(const CommandButton *commandButton,
                                                      const Coord3D *position,
                                                      CommandSourceType commandSource)
{
    if (commandButton == 0)
    {
        return;
    }

    Object *owner = reinterpret_cast<Object *>(reinterpret_cast<unsigned int>(m_object) + 0);
    volatile unsigned char *objectBytes = reinterpret_cast<volatile unsigned char *>(owner);
    objectBytes += 4;
    ThingTemplate *objectTemplate = *reinterpret_cast<ThingTemplate * volatile *>(objectBytes);
    if (objectTemplate != 0 && objectTemplate->m_nextOverride != 0)
    {
        objectTemplate = (ThingTemplate *)objectTemplate->m_nextOverride->getFinalOverride();
    }

    if ((objectTemplate->m_kindOf[0] & 0x02000000) != 0)
    {
        return;
    }

    if (owner == 0)
    {
        return;
    }

    AIUpdateInterface *ai = owner->m_ai;
    if (ai == 0)
    {
        return;
    }

    const CommandSet *commandSet = TheControlBar->findCommandSet(owner->getCommandSetString());
    if (commandSet != 0)
    {
        for (Int index = 0; index < 20; ++index)
        {
            commandSet->getCommandButton(index);
        }
    }
}

void AIUpdateInterface::privateCommandButtonObject(const CommandButton *commandButton,
	Object *obj, CommandSourceType commandSource)
{
	if (!commandButton)
		return;

	Object *owner = reinterpret_cast<Object *>(reinterpret_cast<unsigned int>(m_object) + 0);
	ThingTemplate *ownerTemplate = getObjectTemplate(owner);

	if ((ownerTemplate->m_kindOf[0] & 0x02000000) != 0)
		return;

	if (owner == 0)
		return;

	const CommandSet *commandSet = TheControlBar->findCommandSet(owner->getCommandSetString());
	if (commandSet != 0)
	{
		for (Int i = 0; i < 20; ++i)
		{
			const CommandButton *aCommandButton = commandSet->getCommandButton(i);
			if (commandButton == aCommandButton)
			{
				ThingTemplate *myTemplate = getObjectTemplate(owner);
				AsciiString myName =
					(reinterpret_cast<const AsciiString *>(
						reinterpret_cast<const char *>(myTemplate) + 0x20))->str();
				AsciiString myNickname;
				ThingTemplate *targetTemplate = getObjectTemplate(obj);
				AsciiString targetName =
					(reinterpret_cast<const AsciiString *>(
						reinterpret_cast<const char *>(targetTemplate) + 0x20))->str();
				AsciiString targetNickname;

				if (owner->getName().isNotEmpty())
					myNickname.format("('%s')", owner->getName().str());

				if (obj->getName().isNotEmpty())
					targetNickname.format("('%s')", obj->getName().str());
			}
		}
	}
}
