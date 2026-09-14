// cl: /DNDEBUG /MD /EHsc
// The caller at 0x008969F7 loads the receiver from 0x013377F0.  This body
// builds the same inline-two-element container whose destructor is already
// owned at 0x00893E70, passes it to the same-layout body at 0x00895050, and
// then destroys the temporary.

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

struct BfmeStringPool3AF0
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct Rva00892640Item
{
	Rva00892640Item();
	Rva00892640Item &operator=(const Rva00892640Item &other);
	~Rva00892640Item();

	BfmeStringData3AF0 *m_handle;
	void *m_extra;
};

class Gen_uw_00893e70
{
public:
	Gen_uw_00893e70();
	~Gen_uw_00893e70();

	void Rva00895050(Gen_uw_00893e70 *other);
	void Rva00895340();

private:
	unsigned int m_count;
	unsigned int m_capacity;
	Rva00892640Item *m_data;
	Rva00892640Item m_inline[2];
};

// Its 46-byte out-of-line copy is uniquely located at 0x00892C30 after
// relocation-aware whole-image verification.
inline Gen_uw_00893e70::Gen_uw_00893e70()
	: m_count(0), m_capacity(0), m_data(m_inline)
{
}

void Gen_uw_00893e70::Rva00895340()
{
	Gen_uw_00893e70 empty;
	Rva00895050(&empty);
}
