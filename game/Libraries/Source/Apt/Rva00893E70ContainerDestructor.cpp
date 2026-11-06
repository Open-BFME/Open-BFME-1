// cl: /DNDEBUG /MD /EHsc

struct BfmeStringData3AF0
{
	unsigned short m_refs;
};

struct BfmeStringPool3AF0
{
	void *m_pad;
	void (__cdecl *m_destroy)(BfmeStringData3AF0 *);
};

class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;	// shared empty string block 0x012D5298
static inline BfmeStringData3AF0 *sharedEmptyString012D5298()
{
	return (BfmeStringData3AF0 *)&g_rva012D5298Empty;
}
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

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

// The resize body at 0x00893B30 (Rva00895050InlineContainerSwap.cpp); retail
// calls it directly with (data, 0, 0).
extern Rva00892640Item *Rva00893B30ResizeItems(
	Rva00892640Item *data, int logical_count, int new_capacity);

Gen_uw_00893e70::~Gen_uw_00893e70()
{
	if (m_data != m_inline)
		Rva00893B30ResizeItems(m_data, 0, 0);
}
