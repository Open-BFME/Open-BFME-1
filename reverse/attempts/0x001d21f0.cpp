// ?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z
// partial score=0.94 date=2026-09-11
typedef int Int;

struct AsciiStringBuffer
{
	unsigned int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

class AsciiString
{
private:
	AsciiStringBuffer *m_buffer;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	const Overridable *bfmeFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class CommandButton
{
public:
	Int getCommandType() const { return m_commandType; }

private:
	unsigned char m_unmodelled_000[0x10];
	Int m_commandType;
};

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

class Object
{
public:
	void doCommandButton(const CommandButton *button, Int source, Int extra);

	void *m_vtable;
	Overridable *m_template;
	unsigned char m_unmodelled_008[0x328 - 0x08];
	AsciiStringBuffer *m_commandSetFallback;
	AsciiStringBuffer *m_commandSetOverride;
};

extern ControlBar *TheControlBar;

class BfmeR1094;

class BfmeK1094 : public Object
{
public:
	BfmeR1094 *bfmeCur1094();
	void doCommandButton(const CommandButton *button, Int source, Int extra);
	void bfmeApplyABG(void *a, void *b);
};

struct BfmeNodeABG
{
	BfmeNodeABG *m_bfmeNextABG;
	BfmeNodeABG *m_bfmePrevABG;
	BfmeK1094 *m_bfme08ABG;
};

class BfmeHostABG
{
public:
	void bfmeVisitABG(void *a, void *b);

	unsigned char m_bfmeHeadABG[4];
	BfmeNodeABG *m_bfme04ABG;
};

void BfmeHostABG::bfmeVisitABG(void *a, void *b)
{
	for (BfmeNodeABG *n = m_bfme04ABG->m_bfmeNextABG; n != m_bfme04ABG; n = n->m_bfmeNextABG)
	{
		BfmeK1094 *it = n->m_bfme08ABG;

		if (it->bfmeCur1094() != 0)
		{
			it->bfmeApplyABG(a, b);
			return;
		}
	}
}

void BfmeK1094::bfmeApplyABG(void *a, void *b)
{
	Int commandIndex = reinterpret_cast<Int>(a);
	Int source = reinterpret_cast<Int>(b);
	const AsciiString *commandSetName;
	if (m_commandSetOverride && m_commandSetOverride->m_length != 0)
	{
		commandSetName = reinterpret_cast<const AsciiString *>(
			&m_commandSetOverride);
	}
	else if (m_commandSetFallback && m_commandSetFallback->m_length != 0)
	{
		commandSetName = reinterpret_cast<const AsciiString *>(
			&m_commandSetFallback);
	}
	else
	{
		const Overridable *templateObject = m_template;
		if (templateObject)
			templateObject = templateObject->bfmeFinalOverride();
		commandSetName = reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(templateObject) + 0x2c);
	}

	const CommandSet *commandSet =
		TheControlBar->findCommandSet(*commandSetName);
	if (commandSet)
	{
		for (Int index = 0; index < 20; ++index)
		{
			const CommandButton *button = commandSet->getCommandButton(index);
			if (button->getCommandType() == 0x2c)
			{
				if (commandIndex != 0)
				{
					--commandIndex;
				}
				else
				{
					doCommandButton(button, source, 0);
					return;
				}
			}
		}
	}
}
