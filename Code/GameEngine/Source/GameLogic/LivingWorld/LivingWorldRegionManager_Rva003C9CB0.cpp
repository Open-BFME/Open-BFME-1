// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x003C9CB0 (230 bytes).  The named caller at 0x003BDA10 loads the
// LivingWorldRegionManager from Glo012F1028Type and passes four pointers to
// this member.  The manager lookup at 0x003C8A50 (landed as
// LivingWorldRegionManager_Rva003C8A50.cpp) and its 0x003C8880
// constructor/vtable family establish the receiver; the 0x003C9CB0 body then
// updates the found 0xF4-byte region, appends it to the manager's pointer
// vector, and registers its two-word coordinate pair with the 0x012F706C
// singleton.  The method name stays address-derived: the owner is proven, the
// semantic method name is not.
//
// Shape note for the tail (the residue that held this body at 228/230 bytes
// through twelve earlier passes): retail copies the new handle into TWO
// registers -- `mov ecx,ebx; mov edi,ebx; mov [esi+0xac],edi; push ecx` --
// where a plain `region->m_handle = handle; registerItem(handle, ...)` keeps
// one.  The second copy is the inline ACCESSOR PAIR: the store goes through an
// inline setter (its by-value parameter is the first temporary) and the call
// argument is the inline getter reading the field back (store-forwarded to a
// second temporary).  Direct field access, the local-copy, member-re-read,
// assignment-expression, helper-wrapper and integer-type-conversion spellings
// all collapse the two temporaries back into one.

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
	// +0xAC is the handle the 0x006176A0 sink is told about; the pinned
	// ?registerItem@BfmeSinkAM@@QAEXHPAVGen_003BEA30@@H@Z takes it as its
	// "handle key" first parameter.  The rest keep offset names.
	void setHandle(int handle) { m_handle = handle; }
	int getHandle() const { return m_handle; }

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

// 0x012F706C.  reverse/symbols.csv holds the C++ COFF spelling of this
// singleton as ?g_bfmeGameCW@@3PAVBfmeGameCW@@A; the sink member above is
// pinned under the BfmeSinkAM view of the same object.
class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;

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

	region->setHandle(++m_nextHandle);
	reinterpret_cast<BfmeSinkAM *>(g_bfmeGameCW)->registerItem(
		region->getHandle(), (Gen_003BEA30 *)&pair, 0);
}
