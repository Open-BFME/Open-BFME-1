// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <algorithm>
#include <vector>

enum ScienceType {};

struct Gen_t_004353c0_p8cd
{
	int m_data[2];
	Gen_t_004353c0_p8cd();
	Gen_t_004353c0_p8cd(const Gen_t_004353c0_p8cd &other);
	~Gen_t_004353c0_p8cd();
	Gen_t_004353c0_p8cd &operator=(const Gen_t_004353c0_p8cd &other);
};

template class _STL::vector<Gen_t_004353c0_p8cd>;

class Rva0048EC80Manager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void release(void *item);
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class BfmeItemKA
{
};

extern BfmeItemKA **g_bfmeBegKA;
extern BfmeItemKA **g_bfmeEndKA;

extern "C" __declspec(dllimport) void *u2_import_0135945C(
	void *destination, const void *source, unsigned int bytes);

class Gen0000D33C
{
public:
	~Gen0000D33C();

private:
	void *m_owned;
	char m_padding04[4];
	_STL::vector<Gen_t_004353c0_p8cd> m_entries;
	char m_padding14[0x10];
	int m_count;
	char m_padding28[0xc];
	BfmeItemKA **m_items;
};

Gen0000D33C::~Gen0000D33C()
{
	Rva0048EC80Manager *manager = Rva0048EC80TheManager;
	if (manager != 0)
	{
		for (int i = 0; i < m_count; ++i)
			Rva0048EC80TheManager->release(m_items[i]);

		if (m_owned != 0)
			Rva0048EC80TheManager->release(m_owned);
	}

	BfmeItemKA **items = m_items;
	m_owned = 0;
	delete[] items;

	BfmeItemKA **begin = g_bfmeBegKA;
	BfmeItemKA **end = g_bfmeEndKA;
	ScienceType value = (ScienceType)(unsigned int)this;
	const ScienceType *found = std::find(
		(const ScienceType *)begin, (const ScienceType *)end, value);
	if (found != (const ScienceType *)end)
	{
		const ScienceType *next = found + 1;
		if (next != (const ScienceType *)end)
		{
			u2_import_0135945C(
				(void *)found, next, (unsigned int)((char *)end - (char *)next));
		}

		--g_bfmeEndKA;
	}
}
