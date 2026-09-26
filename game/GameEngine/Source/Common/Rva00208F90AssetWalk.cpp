// Address-derived asset walker at retail RVA 0x00208F90.
// The owner identity is unresolved; its offsets and helper ABIs are decoded.

// cl: /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

template <typename T>
class StringBase
{
public:
	StringBase() {}
	StringBase(const StringBase<T> &other);

	char *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}

	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}
};

AsciiString operator+(AsciiString left, const char *right);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

void *bfmeGoEMEb(void *name);
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

struct AssetList00208F90
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;

	AssetList00208F90 &operator <<(const AsciiString &name)
	{
		if (m_prototypes.insert(
			((FindPrototypeFn)bfmeGoEMEb)(name.str())).second)
		{
			m_changed = true;
		}
		return *this;
	}
};

class BfmeSubBNC
{
public:
	void bfmeDoBNC(void *one, void *two);
};

class Gen_002DDCC0Target
{
public:
	void bfmeForward(void *one, void *two);
};

class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *one, void *two);
};

template <typename T>
struct Rva00208F90Range
{
	T **m_begin;
	T **m_end;
	T **m_capacity;

	T **begin() const { return m_begin; }
	T **end() const { return m_end; }
};

struct Rva00208F90Owner
{
	unsigned char m_padding00[0x58];
	Rva00208F90Range<Gen_002DDCC0Target> m_second[4];
	Rva00208F90Range<BfmeSubBNC> m_first[4];
	Rva00208F90Range<Gen_001D5EE0Target> m_third[4];
	unsigned char m_paddingE8[0x84];
	AsciiString m_shadowTextureName;
};

// ?collectAssets00208F90@@YAXABURva00208F90Owner@@AAUAssetList00208F90@@PAX@Z
void collectAssets00208F90(
	const Rva00208F90Owner &owner, AssetList00208F90 &assets, void *context)
{
	for (int i = 0; i < 4; ++i)
	{
		for (BfmeSubBNC **it = owner.m_first[i].begin();
			it != owner.m_first[i].end(); ++it)
		{
			if (*it)
				(*it)->bfmeDoBNC(&assets, context);
		}

		for (Gen_002DDCC0Target **it = owner.m_second[i].begin();
			it != owner.m_second[i].end(); ++it)
		{
			if (*it)
				(*it)->bfmeForward(&assets, context);
		}

		for (Gen_001D5EE0Target **it = owner.m_third[i].begin();
			it != owner.m_third[i].end(); ++it)
		{
			if (*it)
				(*it)->bfmeForward(&assets, context);
		}
	}

	if (owner.m_shadowTextureName.isNotEmpty())
	{
		assets << (owner.m_shadowTextureName + ".tga");
	}
}
