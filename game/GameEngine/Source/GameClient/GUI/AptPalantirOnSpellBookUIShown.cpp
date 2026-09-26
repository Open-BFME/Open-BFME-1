class AptPalantirSpellBook
{
public:
	void onShown();
};

class AptPalantir
{
public:
	unsigned char m_unmodelled00[ 0x17c ];
	AptPalantirSpellBook m_spellBook;
};

extern AptPalantir *TheAptPalantir;

// ?aptPalantirOnSpellBookUIShown@@YAXXZ
void aptPalantirOnSpellBookUIShown()
{
	TheAptPalantir->m_spellBook.onShown();
}
