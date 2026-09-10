// ?rva003C9CB0@LivingWorldRegionManager@@QAEXPAX000@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x003C9CB0 (230 bytes).  The named caller at 0x003BDA10 loads the
// LivingWorldRegionManager from Glo012F1028Type and passes four pointers to
// this member.  The manager lookup at 0x003C8A50 and its vtable/constructor
// family establish the receiver; the 0x003C9CB0 body then updates the found
// 0xF4-byte region, appends it to the manager's pointer vector, and registers
// its two-word coordinate pair with the 0x012F706C singleton.

#include <vector>

template <typename Type>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<Type> &source);

private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	void set(const AsciiString &source)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&source);
	}

	void clearForC9CB0()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
};

struct Gen003BC9C0Pair
{
	int m_a;
	int m_b;
};

class Gen003C9470Owner
{
public:
	void fill(void *source, Gen003BC9C0Pair *result);
};

class LivingWorldRegion
{
};

class Rva0061AF80Region
{
public:
	char m_pad00[0xAC];
	int m_handle;
	char m_padB0[0x8];
	AsciiString m_fieldB8;
	int m_fieldBC;
	int m_fieldC0;
	char m_padC4[0x1C];
	int m_fieldE0;
	int m_fieldE4;
};

class Gen_003BEA30;

class BfmeSinkAM
{
public:
	void registerItem(int handle, Gen_003BEA30 *item, int variant);
};

extern BfmeSinkAM *g_bfmeSinkAM;

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &regionName);
	void rva003C9CB0(void *first, void *second, void *third, void *fourth);

private:
	char m_pad00[0x14];
	std::vector<Rva0061AF80Region *> m_regions;
	int m_nextHandle;
};

// ?rva003C9CB0@LivingWorldRegionManager@@QAEXPAX000@Z
void LivingWorldRegionManager::rva003C9CB0(void *first, void *second,
	void *third, void *fourth)
{
	Rva0061AF80Region *region =
		(Rva0061AF80Region *)rva003C8A50(*(const AsciiString *)first);
	if (region == 0)
		return;

	if (second != 0)
		region->m_fieldB8.set(*(const AsciiString *)second);
	else
		region->m_fieldB8.clearForC9CB0();

	if (fourth != 0)
	{
		region->m_fieldBC = ((Gen003BC9C0Pair *)fourth)->m_a;
		region->m_fieldC0 = ((Gen003BC9C0Pair *)fourth)->m_b;
	}

	m_regions.push_back(region);

	Gen003BC9C0Pair pair;
	if (third != 0)
		pair = *(Gen003BC9C0Pair *)third;
	else
		((Gen003C9470Owner *)this)->fill(first, &pair);

	region->m_fieldE0 = pair.m_a;
	region->m_fieldE4 = pair.m_b;

	int handle = ++m_nextHandle;
	region->m_handle = handle;
	g_bfmeSinkAM->registerItem(handle, (Gen_003BEA30 *)&pair, 0);
}
