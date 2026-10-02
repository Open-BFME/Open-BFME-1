// Retail vtable at 0x010E75B0 is LatchRestore<Player *>'s; __identifier is how
// this tree spells a compiler-emitted vftable (cf. WeaponCopyConstructor.cpp).
extern "C" void *__identifier("??_7?$LatchRestore@PAVPlayer@@@@6B@")[];

void bfmeFreeVC(void *what);

class BfmeThingVC
{
public:
	void *bfmeKillVC(int flags);
	void *m_bfmeVft;
	void *m_bfmeWhat;
	void **m_bfmeSlot;
};

void *BfmeThingVC::bfmeKillVC(int flags)
{
	void **slot = m_bfmeSlot;
	void *what = m_bfmeWhat;
	m_bfmeVft = __identifier("??_7?$LatchRestore@PAVPlayer@@@@6B@");
	*slot = what;
	if ((flags & 1) != 0)
		bfmeFreeVC(this);
	return this;
}
