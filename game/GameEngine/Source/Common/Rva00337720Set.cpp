// cl: /O2 /Ob0

// Retail vtable at 0x010E75B0 is LatchRestore<Player *>'s; __identifier is how
// this tree spells a compiler-emitted vftable (cf. WeaponCopyConstructor.cpp).
extern "C" void *__identifier("??_7?$LatchRestore@PAVPlayer@@@@6B@")[];

class Rva00337720
{
	void *m_00;
	int m_04;
	int *m_08;

public:
	Rva00337720 &set(int *p, int *q);
};

Rva00337720 &Rva00337720::set(int *p, int *q)
{
	m_00 = __identifier("??_7?$LatchRestore@PAVPlayer@@@@6B@");
	m_08 = p;
	m_04 = *p;
	*p = *q;
	return *this;
}