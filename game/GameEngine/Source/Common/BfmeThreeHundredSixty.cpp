// Retail vtable at 0x010E75B0 is LatchRestore<Player *>'s; __identifier is how
// this tree spells a compiler-emitted vftable (cf. WeaponCopyConstructor.cpp).
//
// STILL OPEN after the operator-delete respelling below: `operator delete` now
// resolves (mem_ops.cpp defines ??3@YAXPAX@Z), but this vftable name is
// referenced and defined nowhere in the tree - no header declares LatchRestore,
// and the only LatchRestore vftable the tree emits is the H instantiation
// (??_7?$LatchRestore@H@@6B@ in Rva00337640LatchRestoreInt.cpp). The same
// reference is open in R2SmallMemberOps.cpp and Rva00337720Set.cpp, so it needs
// one TU that really defines `??_7?$LatchRestore@PAVPlayer@@@@6B@` plus its
// ledger data row; it is not fixable from this file alone.
extern "C" void *__identifier("??_7?$LatchRestore@PAVPlayer@@@@6B@")[];

// Retail releases the object through the global operator delete (0x00881EB0,
// ??3@YAXPAX@Z in game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp); declared
// here only, never defined.
void __cdecl operator delete(void *what);

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
		operator delete(this);
	return this;
}
