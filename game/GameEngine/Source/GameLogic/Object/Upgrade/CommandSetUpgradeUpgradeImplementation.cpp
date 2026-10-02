// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// CommandSetUpgrade::upgradeImplementation at retail 0x002D4310: slot 9 of the UpgradeMux table
// 0x010CC330, reached only through ILT 0x00017AE9. CommandSetUpgrade's registered
// constructor 0x002D41A0 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
//
// Open-BFME5: the label-propagating notifier at retail 0x002D4310, 109 bytes.
// A secondary-base body: both objects it works on are read from slots ahead of
// this, at -0x08 and -0x0C.  The copied label is a temporary, destroyed once
// set has consumed it, and the global flag is raised afterwards.

class AsciiStringXC
{
public:
	AsciiStringXC(const AsciiStringXC &other);
	~AsciiStringXC(void);

	void set(const AsciiStringXC &other);

private:
	char *m_bfmeData;
};

class BfmeStrXC : private AsciiStringXC
{
public:
	void bfmeSetXC(const AsciiStringXC &other)
	{
		set(other);
	}
};

class BfmeOwnerXC
{
public:
	char m_bfmePad00[0x70];					// +0x00
	AsciiStringXC m_bfmeLabel;				// +0x70
};

class BfmeTargetXC
{
public:
	char m_bfmePad000[0x328];				// +0x000
	BfmeStrXC m_bfmeLabel;					// +0x328
};

class BfmeStateXC
{
public:
	char m_bfmePad00[0x24];					// +0x00
	bool m_bfmeDirty;					// +0x24
};

class ControlBar;

extern ControlBar *TheControlBar;				// retail 0x012F33F8

class CommandSetUpgrade
{
protected:
	virtual void upgradeImplementation();
};

// ?upgradeImplementation@CommandSetUpgrade@@MAEXXZ
void CommandSetUpgrade::upgradeImplementation()
{
	BfmeTargetXC *target = *(BfmeTargetXC **)((char *)this - 8);
	BfmeOwnerXC *owner = *(BfmeOwnerXC **)((char *)this - 0xC);

	{
		AsciiStringXC label(owner->m_bfmeLabel);

		BfmeStrXC *slot = &target->m_bfmeLabel;

		slot->bfmeSetXC(label);
	}

	((BfmeStateXC *)TheControlBar)->m_bfmeDirty = true;
}
