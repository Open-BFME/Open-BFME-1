// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// Retail 0x0043E510 is slot 20 in the InGameUI and W3DInGameUI vtables.
// The slot converts an AsciiString label through TheGameText and forwards the
// resulting UnicodeString and duration to slot 19. The ledger's proved
// militarySubtitle(AsciiString const&, int) identity belongs to this slot.
// Keep the emitted method name address-qualified because InGameUI.cpp also
// defines the present-unmatched method; object-symbol selects this emitter.

#include "StringInline.h"

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	virtual void slot00() = 0;
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
	virtual void slot19Rva00441D30(UnicodeString text, int duration) = 0;
	virtual void subtitleLabelRva0043E510(const AsciiString &label, int duration);
};

void InGameUI::subtitleLabelRva0043E510(const AsciiString &label, int duration)
{
	UnicodeString text = TheGameText->fetch(label);
	slot19Rva00441D30(text, duration);
}
