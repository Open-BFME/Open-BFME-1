// cl: /DNDEBUG /MD /EHsc
// readable body of ?newCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator =(const AsciiString &that);
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
class CommandSet
{
public:
	CommandSet(const AsciiString & name);
	void friend_addToList(CommandSet **list);

private:
	unsigned char m_retailLayout[100];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CommandButton *newCommandButton(const AsciiString & name);
	CommandSet *newCommandSet(const AsciiString & name);

private:
	unsigned char m_prefix[0x28];
	CommandButton *m_commandButtons;
	CommandSet *m_commandSets;
};

CommandButton *ControlBar::newCommandButton(const AsciiString &name)
{
	CommandButton *button = new CommandButton;
	button->setName(name);
	button->friend_addToList(&m_commandButtons);
	return button;
}

CommandSet *ControlBar::newCommandSet(const AsciiString & name)
{
	CommandSet *set = new CommandSet(name);
	set->friend_addToList(&m_commandSets);
	return set;
}
