// cl: /DNDEBUG /MD /EHsc
// readable body of ?newCommandSetOverride@ControlBar@@IAEPAVCommandSet@@PAV2@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Open-BFME: ControlBar::newCommandSetOverride, retail 0x0049DE40, 147 bytes.
//
// The reference's body, and the same override-copy guard
// CrateSystem_newCrateTemplateOverride.cpp landed: the byte at 0x012ED611 is
// raised across the copy assignment and dropped straight after.
//
// The two functions are otherwise the same shape down to the register
// assignment; this one differs only in constructing the new set from the
// original's name -- the `lea ecx, [edi+0x0C]` that reaches m_name past the
// Overridable fields -- and in the size it allocates, 0x64.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// Raised only while an override is being copied over its original.
extern Bool TheBfmeOverrideCopyInProgress;			// 0x012ED611

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();					// pool object vptr, this+0x00

	void markAsOverride(void) { m_isOverride = true; }
	void setNextOverride(Overridable *nextOverride) { m_nextOverride = nextOverride; }

protected:
	Overridable *m_nextOverride;				// this+0x04
	Bool m_isOverride;					// this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet : public Overridable
{
public:
	CommandSet(const AsciiString &name);			// ILT 0x000428CA
	CommandSet &operator=(const CommandSet &that);		// ILT 0x00007F95

	const AsciiString &getName(void) const { return m_name; }

private:
	AsciiString m_name;					// this+0x0C
	char m_bfme_body[0x64 - 0x10];				// sizeof(CommandSet) is the pushed 0x64
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CommandSet *newCommandSetOverride(CommandSet *setToOverride);
};

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
