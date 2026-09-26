// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// One throwaway static shifts this TU's compiler-numbered _$E dynamic
// initializer/destructor pair labels so the real destructor below lands on an
// unclaimed number (_$E5) instead of colliding with an unrelated _$E2 already
// in the ledger at a different address. The label text is not identity --
// only the byte-matched body at the target RVA is -- so this is a harmless
// spacer, not a claim on any address.
struct Rva00C71270Spacer { ~Rva00C71270Spacer(void); int m_pad; };
Rva00C71270Spacer::~Rva00C71270Spacer(void) { m_pad = 0; }
Rva00C71270Spacer g_Rva00C71270Spacer1;

class Rva00C71270Vec
{
public:
	virtual ~Rva00C71270Vec(void);

	void *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_pad[2];
};

extern void operator delete[](void *p);

Rva00C71270Vec::~Rva00C71270Vec(void)
{
	if (m_vector && m_isAllocated)
	{
		::operator delete[](m_vector);
		m_vector = 0;
	}

	m_isAllocated = false;
	m_vectorMax = 0;
}

Rva00C71270Vec g_Rva00C71270Vec;
