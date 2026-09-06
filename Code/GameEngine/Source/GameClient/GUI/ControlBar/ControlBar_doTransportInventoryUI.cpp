// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class CommandButton;
class CommandSet;
class GameWindow;
class Image;
class OpenContain;

typedef void (*ContainIterateFunc)(Object *, void *);

class ContainModuleInterface
{
public:
	virtual OpenContain *asOpenContain() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual Int getContainMax() const = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual Int getExtraSlotsInUse() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63(ContainIterateFunc, void *, Bool) = 0;
	virtual Int getContainCount(Bool countRiders) const = 0;
};

class Object
{
public:
	ContainModuleInterface *getContain() const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1fc);
	}

	Bool isDisabledByType(Int type) const
	{
		return (*(const unsigned char *)((const char *)this + 0x1a4) & (1 << type)) != 0;
	}
};

class CommandButton
{
public:
	Int getCommandType() const
	{
		return *(const Int *)((const char *)this + 0x10);
	}

	Bool hasOverlayStatus() const
	{
		return *(const unsigned char *)((const char *)this + 0x14d) != 0;
	}
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class GameWindow
{
public:
	void bfmeClose(Bool hide);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
};

class BfmeUnit1013
{
public:
	void bfmeStop1013(char enable);
};

void GadgetButtonDrawOverlayImage(GameWindow *window, const Image *image);

struct PopulateInvButtonData
{
	Int currIndex;
	Int maxIndex;
	GameWindow **controls;
	Object *transport;
};

class ControlBar
{
public:
	void setControlCommand(GameWindow *window, const CommandButton *commandButton);

protected:
	void doTransportInventoryUI(Object *transport, const CommandSet *commandSet);

	char m_pad00[0x70];
	UnsignedInt m_lastRecordedInventoryCount;
	char m_pad74[0x8c];
	GameWindow *m_commandWindows[20];
};

void ControlBar::doTransportInventoryUI(Object *transport, const CommandSet *commandSet)
{
	if (transport == 0 || commandSet == 0)
		return;

	ContainModuleInterface *contain = transport->getContain();
	if (contain == 0)
		return;

	OpenContain *openContain = contain->asOpenContain();
	if (openContain != 0 && !*(const unsigned char *)((const char *)openContain + 0xb6))
		return;

	Int transportMax = contain->getContainMax();
	transportMax -= contain->getExtraSlotsInUse();

	Int firstInventoryIndex = -1;
	Int lastInventoryIndex = -1;
	Int inventoryCommandCount = 0;

	for (Int i = 0; i < 20; ++i)
	{
		const CommandButton *commandButton = commandSet->getCommandButton(i);
		if (commandButton == 0 || commandButton->getCommandType() != 0xf)
			continue;

		if (firstInventoryIndex == -1)
			firstInventoryIndex = i;
		lastInventoryIndex = i;
		++inventoryCommandCount;

		if (m_commandWindows[i] == 0)
			continue;

		m_commandWindows[i]->bfmeClose(false);
		((BfmeUnit1013 *)m_commandWindows[i])->bfmeStop1013(0);
		GadgetButtonDrawOverlayImage(m_commandWindows[i], 0);

		if (transport->isDisabledByType(5))
			m_commandWindows[i]->bfmeClose(true);

		if (inventoryCommandCount > transportMax)
			m_commandWindows[i]->bfmeClose(true);

		setControlCommand(m_commandWindows[i], commandButton);
		if (commandButton->hasOverlayStatus())
			m_commandWindows[i]->winSetStatus(0x4000000);
		else
			m_commandWindows[i]->winClearStatus(0x4000000);
	}

	if (lastInventoryIndex >= 0)
	{
		PopulateInvButtonData data;
		data.controls = m_commandWindows;
		data.currIndex = firstInventoryIndex;
		data.maxIndex = lastInventoryIndex;
		data.transport = transport;
		contain->slot63((ContainIterateFunc)0x0043fd5f, &data, true);
	}

	m_lastRecordedInventoryCount = contain->getContainCount(false);
}
