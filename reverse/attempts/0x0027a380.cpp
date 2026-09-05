// ?Rva0027A380@Rva0027A380Owner@@QAEXPBVCommandButton@@PAVRva0027A380Entity@@@Z
// partial score=0.35 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: address-derived body at retail 0x0027A380, 486 bytes.
// The owner, the entity it points at, and BfmeSubBIA are all still
// dump-only (no ZH twin -- BfmeSubBIA is BFME original), so this body is
// landed under an address-derived name per IDENTITY POLICY.
//
// Shape: given a target CommandButton and a secondary entity, find the
// CommandSet named by the primary entity's command-set string, walk its
// MAX_COMMANDS_PER_SET=20 buttons, and for the one matching the target
// button build two "('%s')" debug strings from each entity's dynamic name.

class BfmeAskResult
{
public:
	unsigned char m_pad0[0x20];
	char *m_name;                  // +0x20
	unsigned char m_pad1[0xA4];    // pad to +0xC8
	unsigned int m_flags;          // +0xC8
};

class BfmeSubBIA
{
public:
	int ask(void);                  // ILT 0x000022BB

	unsigned char m_pad0[4];
	BfmeSubBIA *m_next;              // +0x04
};

static BfmeAskResult *bfmeGetAskResult(BfmeSubBIA *a)
{
	if (a) {
		BfmeSubBIA *b = a->m_next;
		if (b) {
			return (BfmeAskResult *)b->ask();
		}
	}

	return 0;
}

class OverrideNode
{
public:
	unsigned char m_pad0[4];
	unsigned short m_kind;          // +0x04
};

class AsciiString
{
public:
	AsciiString(void);
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString(void);
	void __cdecl format(AsciiString text, ...);

private:
	char *m_data;
};

class CommandButton;

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;      // ILT 0x00003F80
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);   // ILT 0x00048CCA
};

extern ControlBar *TheControlBar;

class Rva0027A380Entity
{
public:
	const AsciiString &getCommandSetString(void) const;      // ILT 0x00029DC0

	unsigned char m_pad0[4];
	BfmeSubBIA *m_bia;                // +0x04
	unsigned char m_pad1[0x7C];       // pad to +0x84
	OverrideNode *m_override;         // +0x84
};

class Rva0027A380Owner
{
public:
	void Rva0027A380(const CommandButton *targetButton, Rva0027A380Entity *other);

	unsigned char m_pad0[8];
	Rva0027A380Entity *m_entity;      // +0x08
};

void Rva0027A380Owner::Rva0027A380(const CommandButton *targetButton, Rva0027A380Entity *other)
{
	if (!targetButton) {
		return;
	}

	Rva0027A380Entity *entity = m_entity;

	if (bfmeGetAskResult(entity->m_bia)->m_flags & 0x02000000) {
		return;
	}

	if (!entity) {
		return;
	}

	const CommandSet *set = TheControlBar->findCommandSet(entity->getCommandSetString());
	if (!set) {
		return;
	}

	for (int i = 0; i < 20; ++i) {
		const CommandButton *button = set->getCommandButton(i);
		if (button != targetButton) {
			continue;
		}

		BfmeAskResult *askResult = bfmeGetAskResult(entity->m_bia);
		const char *entityName = askResult->m_name ? askResult->m_name + 8 : "";
		AsciiString entityText(entityName);

		OverrideNode *override_ = other->m_override;
		const char *otherName = "";
		if (override_ && override_->m_kind != 0) {
			otherName = override_ ? (const char *)override_ + 8 : "";
		}
		AsciiString otherText(otherName);

		AsciiString entityLine;
		entityLine.format(AsciiString("('%s')"), (const char *)&entityText);

		AsciiString otherLine;
		otherLine.format(AsciiString("('%s')"), (const char *)&otherText);
	}
}
