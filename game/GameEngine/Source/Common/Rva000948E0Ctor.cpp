// cl: /O2 /Ob0

// 0x0107FCB0 is Overridable's vftable: the base's slot 0 is its scalar
// deleting destructor at 0x00094940. The store is therefore Overridable's
// own vftable, not a derived one, so the class is named directly rather than
// through a linker alias.
extern "C" const char __identifier("??_7Overridable@@6B@")[];

class Rva000948E0
{
	void *m_vptr;
	int m_04;
	char m_08;

public:
	Rva000948E0(int dummy);
};

Rva000948E0::Rva000948E0(int)
{
	m_vptr = (void *)__identifier("??_7Overridable@@6B@");
	m_04 = 0;
	m_08 = 0;
}
