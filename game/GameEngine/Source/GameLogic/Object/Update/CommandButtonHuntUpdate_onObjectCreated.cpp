// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0028ADA0 performs the command-button lookup used by the hunt module.
// Its address-derived owner keeps the BFME-only source identity explicit.

typedef bool Bool;

struct FlagPair2B2080
{
	Bool first;
	Bool second;
};

class AsciiString
{
public:
	int compare(const AsciiString &other) const;
	bool isEmpty() const
	{
		return m_text == 0 || m_text->length == 0;
	}

private:
	struct StringData
	{
		char m_prefix[4];
		unsigned short length;
	};
	StringData *m_text;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual Bool slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Bool slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void applyFlags(const FlagPair2B2080 &flags) = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void writeCommandSet(AsciiString *name) = 0;
	const AsciiString &getCommandSetString() const;
};

class CommandButton
{
public:
	char m_padding00[0x0c];
	AsciiString m_name;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

class Gen002B2080
{
public:
	void handle(class FlagPairTarget *source);
};

class FlagPairTarget
{
public:
	virtual void slot00() = 0;
	virtual Bool slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Bool slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void applyFlags(const FlagPair2B2080 &flags) = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void updateValue(void *value) = 0;
};

#define TheControlBar (*(ControlBar **)0x012F33F8)

class CommandButtonHuntUpdate
{
public:
	virtual void onObjectCreated(Object *source);

private:
	char m_base00[4];
	Object *m_object;
	char m_base0c[0x14];
	AsciiString m_commandButtonName;
	const CommandButton *m_commandButton;
};

void CommandButtonHuntUpdate::onObjectCreated(Object *source)
{
	((Gen002B2080 *)this)->handle((FlagPairTarget *)source);
	if (source->slot10())
		return;

	FlagPair2B2080 flags;
	flags.first = true;
	flags.second = true;
	source->applyFlags(flags);
	source->writeCommandSet(&m_commandButtonName);
	if (!source->slot04())
		return;

	m_commandButton = 0;
	if (m_commandButtonName.isEmpty())
		return;
	const CommandSet *commandSet =
		TheControlBar->findCommandSet(m_object->getCommandSetString());
	if (commandSet == 0)
		return;

	for (int index = 0; index < 20; ++index)
	{
		const CommandButton *commandButton = commandSet->getCommandButton(index);
		if (commandButton == 0)
			continue;
		if (commandButton->m_name.compare(m_commandButtonName) == 0)
		{
			m_commandButton = commandButton;
			break;
		}
	}
}
