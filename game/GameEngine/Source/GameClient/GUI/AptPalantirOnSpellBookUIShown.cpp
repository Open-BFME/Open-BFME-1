class AptPalantirSpellBook
{
public:
};

class AptPalantir
{
public:
	unsigned char m_unmodelled00[ 0x17c ];
	AptPalantirSpellBook m_spellBook;
};

extern AptPalantir *TheAptPalantir;

// Retail ILT35F85 reaches matched Rva00597F30::init, a void no-stack
// thiscall with a plain RET. Keep the spell-book member receiver at+17C.
extern "C" void __identifier("?j_00035f85@@YAXXZ")();

// ?aptPalantirOnSpellBookUIShown@@YAXXZ
void aptPalantirOnSpellBookUIShown()
{
	union {
		void (*raw)();
		void (AptPalantirSpellBook::*member)();
	} shown = { __identifier("?j_00035f85@@YAXXZ") };
	(TheAptPalantir->m_spellBook.*shown.member)();
}
