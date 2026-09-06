// ?_M_lower_bound@?$_Rb_tree@UGen_t_004f1fd0_m12cd@@U1@U?$_Identity@UGen_t_004f1fd0_m12cd@@@_STL@@U?$less@UGen_t_004f1fd0_m12cd@@@3@V?$allocator@UGen_t_004f1fd0_m12cd@@@3@@_STL@@ABEPAU?$_Rb_tree_node@UGen_t_004f1fd0_m12cd@@@2@ABUGen_t_004f1fd0_m12cd@@@Z
// partial score=0.15 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Open-BFME: STLport _Rb_tree<Gen_t_004f1fd0_m12cd>::_M_lower_bound and its
// twin over Gen_t_004f2240_m12cd (both 12-byte "setmd" family values declared
// in Code/gen_small/fam_013.cpp: int a[3], with an AsciiString-shaped compare
// at +0x0 that this file spells out). Unlike the fully-inlined AsciiString
// _M_lower_bound bodies elsewhere (145B, memcmp all the way down), this body
// is 237B because the compiler emitted real out-of-line calls: two
// AsciiString copy constructions (folded, at retail, into the same COMDAT as
// StringBase<char>'s and several unrelated classes' copy ctors -- string_base.cpp)
// followed by a strcmp-based compare-and-release call.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);
extern "C" int __cdecl strcmp(const char *, const char *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &stringSrc) : m_data(stringSrc.m_data)
	{
		if (m_data)
			InterlockedIncrement((long volatile *)&m_data->m_refCount);
	}
	~AsciiString()
	{
		if (m_data)
		{
			InterlockedDecrement((long volatile *)&m_data->m_refCount);
			if (!m_data->m_refCount)
				freeBytes();
		}
	}
	AsciiString &operator=(const AsciiString &stringSrc);
	const char *str() const { return m_data ? (const char *)(m_data + 1) : ""; }

private:
	void freeBytes();

	struct Data
	{
		long m_refCount;
	};

	Data *m_data;
};

__declspec(noinline) bool operator<(const AsciiString &s1, const AsciiString &s2)
{
	return strcmp(s1.str(), s2.str()) < 0;
}

struct Gen_t_004f1fd0_m12cd
{
	AsciiString m_key;
	int m_unused;
	AsciiString m_value;
};

__declspec(noinline) bool operator<(const Gen_t_004f1fd0_m12cd &a, const Gen_t_004f1fd0_m12cd &b)
{
	return a.m_key < b.m_key;
}

typedef _STL::set<Gen_t_004f1fd0_m12cd> Gen004f1fd0Tree;

// lower_bound is public; the _M_ helper it calls is not, so reaching it
// through the public entry point is what emits it.
bool BfmeTreeLowerBoundAnchor004f1fd0(const Gen004f1fd0Tree &tree, const Gen_t_004f1fd0_m12cd &key)
{
	return tree.lower_bound(key) != tree.end();
}

struct Gen_t_004f2240_m12cd
{
	AsciiString m_key;
	int m_unused;
	AsciiString m_value;
};

__declspec(noinline) bool operator<(const Gen_t_004f2240_m12cd &a, const Gen_t_004f2240_m12cd &b)
{
	return a.m_key < b.m_key;
}

typedef _STL::set<Gen_t_004f2240_m12cd> Gen004f2240Tree;

// lower_bound is public; the _M_ helper it calls is not, so reaching it
// through the public entry point is what emits it.
bool BfmeTreeLowerBoundAnchor004f2240(const Gen004f2240Tree &tree, const Gen_t_004f2240_m12cd &key)
{
	return tree.lower_bound(key) != tree.end();
}
