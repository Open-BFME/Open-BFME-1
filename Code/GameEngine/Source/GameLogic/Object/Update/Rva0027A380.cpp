// ?privateCommandButtonObject@AIUpdateInterface@@MAEXPBVCommandButton@@PAVObject@@W4CommandSourceType@@@Z
// Clean C++ reconstruction for retail 0x0027A380 (486 bytes).
// cl: /DNDEBUG /MD

typedef int Int;
typedef bool Bool;

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

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xC8 - 8];
	unsigned int m_kindOf[3];
};

class Thing
{
public:
	virtual void slot00();

	const ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	const AsciiString &getCommandSetString() const;
	const AsciiString &getName() const
	{
		return *reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(this) + 0x84);
	}

	unsigned char m_pad08[0x7C];
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

class CommandButton;

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

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI,
	CMD_FROM_DOZER,
	CMD_DEFAULT_SWITCH_WEAPON
};

class AIUpdateInterface
{
protected:
	virtual void privateCommandButtonObject(const CommandButton *commandButton,
		Object *obj, CommandSourceType commandSource);

	unsigned char m_pad04[4];
	Object * volatile m_object;
};

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
