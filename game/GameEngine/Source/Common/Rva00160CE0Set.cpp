// cl: /O2 /Ob0

class Rva00160CE0
{
	void *m_00;
	int m_04;
	int m_08;
	char m_0C;
	int m_10;

public:
	Rva00160CE0 &set(int a, int b, char c);
};

// Retail vtable VA 0x0109689C is ??_7PartitionFilterPlayerAffiliation@@6B@
// (targets/game/reverse/symbols.csv), defined by the class's own deleting
// destructor TU.  The declaration carries no C++ name: __identifier spells the
// retail symbol exactly, so the store below references the defining name.
extern "C" void *__identifier("??_7PartitionFilterPlayerAffiliation@@6B@")[];

Rva00160CE0 &Rva00160CE0::set(int a, int b, char c)
{
	m_08 = a;
	m_04 = 0;
	m_00 = __identifier("??_7PartitionFilterPlayerAffiliation@@6B@");
	m_0C = c;
	m_10 = b;
	return *this;
}
