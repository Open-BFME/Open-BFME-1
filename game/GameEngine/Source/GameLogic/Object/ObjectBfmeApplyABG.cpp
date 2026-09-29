// BfmeK1094::bfmeApplyABG, retail 0x001D21F0 (159 bytes).
// Identity: the matched caller BfmeHostABG::bfmeVisitABG (0x00151560) calls
// this body through ILT 0x00006DE8; see
// targets/game/reverse/identity_evidence/bfmeapplyabg-rva001d21f0.md.
//
// Shape note (this is the whole conversion lever, keep it): retail keeps the
// receiver in EBP and the command-set pointer in EDI. Copying the final
// override into its own local before the call is what makes VC7.1 rank the
// receiver below EBX; without that copy the identical body puts `this` in EBX
// and nine non-relocation bytes differ. The copy folds away, so the emitted
// code is unchanged.
typedef int Int;

struct AsciiStringBuffer
{
	unsigned int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

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

extern ControlBar *TheControlBar;

class BfmeObjectDoCommandButton
{
public:
	void doCommandButton(const CommandButton *button, Int source, Int extra);
};

class Object : public BfmeObjectDoCommandButton
{
public:
	void *m_vtable;
	Overridable *m_template;
	unsigned char m_unmodelled_008[0x328 - 0x08];
	AsciiStringBuffer *m_commandSetFallback;
	AsciiStringBuffer *m_commandSetOverride;
};

class BfmeR1094;

class BfmeK1094 : public Object
{
public:
	BfmeR1094 *bfmeCur1094();
	void bfmeApplyABG(void *a, void *b);
};

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
		{
			const Overridable *finalTemplate = templateObject->bfmeFinalOverride();
			templateObject = finalTemplate;
		}
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
					((BfmeObjectDoCommandButton *)this)->doCommandButton(button, source, 0);
					return;
				}
			}
		}
	}
}

// @?bfmeApplyABG@BfmeK1094@@QAEXPAX0@Z 0x001D21F0
