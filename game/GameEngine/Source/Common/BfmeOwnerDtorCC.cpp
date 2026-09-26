// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x0073A4E0, 109 bytes.  Both vftable
// stores are compiler-generated, which is what puts the first one ahead of the
// unwind state rather than after it.

class BfmeElemCC
{
public:
	~BfmeElemCC(void);

	char m_bfmePadECC[0x14];
};

class BfmeRegistryCC
{
public:
	void bfmeForgetCC(void *owner);
};

extern BfmeRegistryCC *g_bfmeRegistryCC;			// retail 0x012F1270

class BfmeBaseCC
{
public:
	virtual ~BfmeBaseCC(void)
	{
	}
};

class BfmeOwnerCC : public BfmeBaseCC
{
public:
	virtual ~BfmeOwnerCC(void);

	void bfmeCleanupCC(void);

	char m_bfmePadCC[0x28];
	BfmeElemCC m_bfmeElemsCC[1];
};

BfmeOwnerCC::~BfmeOwnerCC(void)
{
	bfmeCleanupCC();

	if (g_bfmeRegistryCC != 0)
		g_bfmeRegistryCC->bfmeForgetCC(this);
}
