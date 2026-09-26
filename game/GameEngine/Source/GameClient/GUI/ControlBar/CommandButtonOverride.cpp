// cl: /DNDEBUG /MD /EHsc
// stlport
// ?newCommandButtonOverride@ControlBar@@IAEPAVCommandButton@@PAV2@@Z
// Retail 0x004A3710.  The parser caller, ILT 0x00027CC3, and the paired
// CommandSet override allocator establish this as the CommandButton clone.

typedef bool Bool;

extern Bool TheBfmeOverrideCopyInProgress; // 0x012ED611

class BfmeOverridable
{
public:
	virtual ~BfmeOverridable();

	void markAsOverride()
	{
		m_isOverride = true;
	}

	void setNextOverride(BfmeOverridable *nextOverride)
	{
		m_nextOverride = nextOverride;
	}

protected:
	BfmeOverridable *m_nextOverride;
	Bool m_isOverride;
};

class CommandButton : public BfmeOverridable
{
public:
	CommandButton();

private:
	unsigned char m_retailLayout[0x1cc];
};

class Rva004A32E0Record
{
public:
	Rva004A32E0Record &operator=(const Rva004A32E0Record &other);
};

class ControlBar
{
protected:
	CommandButton *newCommandButtonOverride(CommandButton *buttonToOverride);
};

// ?newCommandButtonOverride@ControlBar@@IAEPAVCommandButton@@PAV2@@Z
CommandButton *ControlBar::newCommandButtonOverride(CommandButton *buttonToOverride)
{
	if (!buttonToOverride)
		return 0;

	CommandButton *newOverride = new CommandButton;
	TheBfmeOverrideCopyInProgress = true;
	(*(Rva004A32E0Record *)newOverride) =
		*(const Rva004A32E0Record *)buttonToOverride;
	TheBfmeOverrideCopyInProgress = false;
	newOverride->markAsOverride();
	buttonToOverride->setNextOverride(newOverride);
	return newOverride;
}
