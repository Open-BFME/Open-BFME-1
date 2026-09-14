// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenSpellStore scalar-deleting destructor at retail RVA
// 0x005996C0 (30 bytes). The exact SpellStore.apt constructor at 0x00599FE0
// installs primary vtable 0x0110C3EC and secondary vtable 0x0110C3E8; the
// matched complete destructor at 0x00599330 resets both views and tears down
// the twelve registered spell-button entries.

class BfmeAptScreenSpellStore
{
public:
	virtual ~BfmeAptScreenSpellStore();
};

void forceBfmeAptScreenSpellStoreDeletingDestructor()
{
	BfmeAptScreenSpellStore value;
}
