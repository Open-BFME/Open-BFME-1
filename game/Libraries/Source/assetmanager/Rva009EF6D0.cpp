// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <string.h>
#include <set>
#include <windows.h>

// ABI views at retail 0x009EF6D0 (existing body) and 0x009EBF90 (wrapper).
// AssetManagerImpl reuses the canonical global's existing C++ receiver spelling;
// the original native class and method declarations are not recovered.
// Rva009EF6D0 retains its address because no native method name is witnessed.
// The result is a 12-byte STLport tree, a word at +0x0C and a byte at +0x10.
// Evidence: targets/game/reverse/identity_evidence/009ebf90-result-view.md.
// Sibling: targets/game/reverse/identity_evidence/009ebff0-result-view.md.

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &other);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &other);
};

typedef _STL::_Rb_tree<
	Gen_t_009ee8e0_k4,
	Gen_t_009ee8e0_k4,
	_STL::_Identity<Gen_t_009ee8e0_k4>,
	_STL::less<Gen_t_009ee8e0_k4>,
	_STL::allocator<Gen_t_009ee8e0_k4> > Rva009EF6D0Tree;

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

struct Rva009EF6D0Output
{
	__forceinline Rva009EF6D0Output()
	{
		memset(&m_value, 0, sizeof(m_value));
		m_active = true;
	}
	Rva009EF6D0Output(const Rva009EF6D0Tree &source) : m_tree(source)
	{
		m_value = 0;
		_ReadWriteBarrier(); // Existing compiler barrier preserves native store order.
		m_active = true;
	}
	Rva009EF6D0Tree m_tree;
	int m_value;
	bool m_active;
};

typedef char Rva009EF6D0TreeSizeCheck[sizeof(Rva009EF6D0Tree) == 12 ? 1 : -1];
typedef char Rva009EF6D0OutputSizeCheck[sizeof(Rva009EF6D0Output) == 20 ? 1 : -1];
typedef char Rva009EF6D0LockSizeCheck[sizeof(CRITICAL_SECTION) == 24 ? 1 : -1];

class AssetManagerImpl
{
public:
	Rva009EF6D0Output Rva009EF6D0();
	Rva009EF6D0Output Rva009EF750();

private:
	unsigned char m_unmodelled_000[0x2C];
	CRITICAL_SECTION m_critical_section;
	unsigned char m_unmodelled_044[0x14C];
	Rva009EF6D0Tree m_tree190;
	unsigned char m_unmodelled_19c[0x30];
	Rva009EF6D0Tree m_tree;
};

// ?Rva009EF6D0@AssetManagerImpl@@QAE?AURva009EF6D0Output@@XZ
Rva009EF6D0Output AssetManagerImpl::Rva009EF6D0()
{
	CriticalSectionLock lock(&m_critical_section);
	return Rva009EF6D0Output(m_tree);
}

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

// ?Rva009EBF90@@YA?AURva009EF6D0Output@@XZ
Rva009EF6D0Output Rva009EBF90()
{
	if (g_theAssetRegistry == NULL)
		return Rva009EF6D0Output();
	return ((AssetManagerImpl *)g_theAssetRegistry)->Rva009EF6D0();
}

// ?Rva009EF750@AssetManagerImpl@@QAE?AURva009EF6D0Output@@XZ
Rva009EF6D0Output AssetManagerImpl::Rva009EF750()
{
	CriticalSectionLock lock(&m_critical_section);
	return Rva009EF6D0Output(m_tree190);
}

// ?Rva009EBFF0@@YA?AURva009EF6D0Output@@XZ
Rva009EF6D0Output Rva009EBFF0()
{
	if (g_theAssetRegistry == NULL)
		return Rva009EF6D0Output();
	return ((AssetManagerImpl *)g_theAssetRegistry)->Rva009EF750();
}
