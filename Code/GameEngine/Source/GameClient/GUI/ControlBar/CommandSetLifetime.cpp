// cl: /DNDEBUG /MD /EHsc
// readable body of ??0CommandSet@@QAE@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?newCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?newCommandSetOverride@ControlBar@@IAEPAVCommandSet@@PAV2@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
//
// How a command set comes into existence: the constructor at 0x0049C680, the
// two allocators that put a new set or button on the control bar's list at
// 0x0049CD10 and 0x0049DDB0, and the override allocator at 0x0049DE40 that
// clones one without listing it.
//
// The four bodies described CommandSet three different ways -- a named layout
// on Overridable, an opaque m_retailLayout[100], and Overridable plus a name
// plus 0x54 unexplained bytes -- and the three fit together exactly. The
// pushed allocation size is 0x64, and the named layout fills it: the pool
// object's vptr, the two Overridable fields, the name at +0x0C where the
// override body's `lea ecx,[edi+0x0C]` reaches it, twenty button slots, and
// the list link the allocators write. One statement now, not three.

typedef int Int;
typedef bool Bool;

// Raised only while an override is being copied over its original.
extern Bool TheBfmeOverrideCopyInProgress;			// 0x012ED611

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	AsciiString &operator =(const AsciiString &that);

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();					// pool object vptr, this+0x00

	void markAsOverride(void) { m_isOverride = true; }
	void setNextOverride(Overridable *nextOverride) { m_nextOverride = nextOverride; }

protected:
	Overridable *m_nextOverride;				// this+0x04
	Bool m_isOverride;					// this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	CommandButton();

	void setName(const AsciiString &name)
	{
		*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(this) + 0x0C) = name;
	}

	void friend_addToList(CommandButton **list)
	{
		*reinterpret_cast<CommandButton **>(reinterpret_cast<char *>(this) + 0x14) = *list;
		*list = this;
	}

private:
	unsigned char m_retailLayout[472];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet : public Overridable
{
public:
	CommandSet(const AsciiString &name);
	virtual ~CommandSet();
	CommandSet &operator=(const CommandSet &that);		// ILT 0x00007F95

	const AsciiString &getName(void) const { return m_name; }
	void friend_addToList(CommandSet **list);

private:
	AsciiString m_name;					// this+0x0C
	const CommandButton *m_command[20];			// this+0x10
	CommandSet *m_next;					// this+0x60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CommandButton *newCommandButton(const AsciiString &name);
	CommandSet *newCommandSet(const AsciiString &name);
	CommandSet *newCommandSetOverride(CommandSet *setToOverride);

private:
	unsigned char m_prefix[0x28];
	CommandButton *m_commandButtons;
	CommandSet *m_commandSets;
};

// ??0CommandSet@@QAE@ABVAsciiString@@@Z
// Retail 0x0049C680, 147 bytes. Every button slot starts empty.
CommandSet::CommandSet(const AsciiString &name) :
	m_name(name),
	m_next(0)
{
	for (Int i = 0; i < 20; ++i)
		m_command[i] = 0;
}

// ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z
// Retail 0x0049CD10, 104 bytes.
CommandSet *ControlBar::newCommandSet(const AsciiString & name)
{
	CommandSet *set = new CommandSet(name);
	set->friend_addToList(&m_commandSets);
	return set;
}

// ?newCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z
// Retail 0x0049DDB0, 113 bytes. The button is named after construction, not
// through it.
CommandButton *ControlBar::newCommandButton(const AsciiString &name)
{
	CommandButton *button = new CommandButton;
	button->setName(name);
	button->friend_addToList(&m_commandButtons);
	return button;
}

// ?newCommandSetOverride@ControlBar@@IAEPAVCommandSet@@PAV2@@Z
// Retail 0x0049DE40, 147 bytes. The same shape as newCommandSet down to the
// register assignment, less the listing: an override belongs to the set it
// overrides, not to the control bar. The byte at 0x012ED611 is raised across
// the copy assignment and dropped straight after, the same guard
// CrateSystem::newCrateTemplateOverride uses.
CommandSet *ControlBar::newCommandSetOverride( CommandSet *setToOverride )
{
	if (!setToOverride) {
		return 0;
	}

	// allocate a new set
	CommandSet *set = new CommandSet( setToOverride->getName() );

	// it's an override; DON'T add it to the main list.

	TheBfmeOverrideCopyInProgress = true;
	*set = *setToOverride;
	TheBfmeOverrideCopyInProgress = false;

	set->markAsOverride();

	setToOverride->setNextOverride(set);

	return set;
}
