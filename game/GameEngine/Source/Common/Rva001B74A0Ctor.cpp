// cl: /O2 /Ob0

class LocomotorSet
{
	void *m_vptr;
	int m_locomotors;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;

public:
	LocomotorSet(int dummy);
};

// Retail vtable VA 0x0109DF3C, symbol ??_7Gen_001BA9E0@@6B@; that name is
// not spellable in C++, so reference it verbatim.
extern "C" void *__identifier("??_7Gen_001BA9E0@@6B@")[];

LocomotorSet::LocomotorSet(int)
{
	m_vptr = __identifier("??_7Gen_001BA9E0@@6B@");
	m_locomotors = 0;
	m_08 = 0;
	m_0C = 0;
	m_18 = 0;
	m_1C = 0;
}
