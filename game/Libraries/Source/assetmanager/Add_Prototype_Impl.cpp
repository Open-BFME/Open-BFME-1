// ?Add_Prototype_Impl@AssetManagerImpl@@QAEXPAX@Z
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x009EF1A0, 224 bytes. This file used to hold a naked __emit copy of
// the retail bytes under this name (an Open-BFME5 lift); the body below is the
// C++ they stood for, and the naked function is gone.
//
// IDENTITY. The name is not inherited from the lift, it is proved: the matched
// free wrapper ?Add_Prototype@@YAXPAX@Z at 0x009EBA40 (Add_Prototype.cpp) is
// nothing but `if (g_theAssetRegistry) ((AssetManagerImpl *)g_theAssetRegistry)->Add_Prototype_Impl(proto)`,
// a thiscall on AssetManagerImpl with one void* argument -- this body.
//
// EXTENT. 224 bytes, ending at the `ret 4` at +0xDD. Ghidra runs 0x009EF1A0
// through 0x009EF6CF, but 0x009EF280 is a separate body: carved.csv gives it
// 1102 bytes from a ghidra-start, and the matched ?bfmeGo1024E@BfmeE1024@@QAEXXZ
// at 0x009EB8D0 calls it directly (symbols.csv pins
// ?bfmeReg1024@BfmeP1024@@QAEXPAVBfmeE1024@@@Z there), so a 1326-byte claim
// would over-claim two functions.
//
// LAYOUT, as the landed siblings Find_Asset.cpp (0x009EEC60) and
// Get_Current_Asset.cpp (0x009EEF10) and the landed registry constructor
// ??0Gen_dtor_009eb9e0@@QAE@XZ already carry: the critical section at +0x2C,
// the hash_map<int, Gen_t_009f14c0_p12cd> at +0x44, the cursor into it at
// +0x58, and the name-key generator at +0x1F0. That map type is what makes
// the out-of-line find 0x009EE6D0 and begin 0x009EE0F0 resolve; operator[] at
// 0x009EEFF0 is the same byte-identical STLport template body, pinned for this
// instantiation by tools/unresolved_pins.py from this row's own call site.
//
// WHAT IT DOES. Under the lock: the asset's name (vtable slot +0) becomes a
// name key, a zero key returns, the key is looked up in the map and a hit
// returns, and otherwise the asset's count at +4 is bumped, the entry is
// created with the asset in its first word, the key is written at the asset's
// +8, and the persistent cursor is reset to begin().
//
// THE ONE SPELLING THAT DECIDED IT. The residue that survived every other
// attempt was 14 bytes of pure register naming: retail holds the lock address
// in EBX and the map address in EBP, this build swapped the two names while
// keeping every save POSITION, the whole instruction stream and the unwind map
// (one state, funclet `lea ecx,[ebp-0x1c]; jmp <guard dtor>` at 0x00C61A48)
// identical. It is decided by ONE word: the guard's constructor must enter on
// its PARAMETER, `EnterCriticalSection(lock)`, not on the member it has just
// copied, `EnterCriticalSection(m_lock)`. The destructor keeps the member
// (`LeaveCriticalSection(m_lock)`), and the argument the ctor was handed is
// the value the allocator then keeps in EBX for the whole guarded region.
// Insensitive (measured, all 14 bytes): local definition order, the guard
// spelling (raw pointer/int/reference/extra member/nested block), the map
// spelling (member, &member, cast, before or after the guard), prefix vs
// postfix refcount, a NameKeyType key, a merged `if (it._M_cur == 0)` tail, a
// null-first `if (proto != 0)` wrap, _ReadWriteBarrier placements, and the
// /G5 /G6 /G7 /GB /Ob1 /Os /Ot /Op /Oi /O1 /Oy- sweep.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

struct CRITICAL_SECTION
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

// The enter deliberately takes the ctor PARAMETER, not m_lock: see the header.
class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *name);
};

// The asset Find_Asset.cpp's AssetReference counts: the raw-pointer
// constructor bumps the sixteen-bit count at +4 without a null test. Slot 0 is
// the name this body hands to nameToLowercaseKey; +8 is where it stores the
// key it computed.
class CountedAsset
{
public:
	virtual const char *Get_Name();

	unsigned short m_refcount;
	unsigned short m_unmodelled_006;
	unsigned int m_name_key;
};

struct Gen_t_009f14c0_p12cd
{
	void *m_asset;
	int a[2];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> GenAssetHash;

class AssetManagerImpl
{
public:
	void Add_Prototype_Impl(void *proto);

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock;
	GenAssetHash m_map44;
	GenAssetHash::iterator m_iterator58;
	unsigned char m_unmodelled_060[0x190];
	NameKeyGenerator *m_hash_context;
};

// ?Add_Prototype_Impl@AssetManagerImpl@@QAEXPAX@Z
void AssetManagerImpl::Add_Prototype_Impl(void *proto)
{
	if (proto == 0)
		return;

	CriticalSectionLock lock(&m_lock);
	int key = (int)m_hash_context->nameToLowercaseKey(
		((CountedAsset *)proto)->Get_Name());
	if (key == 0)
		return;

	GenAssetHash::iterator it = m_map44.find(key);
	if (it._M_cur != 0)
		return;

	++((CountedAsset *)proto)->m_refcount;
	m_map44[key].m_asset = proto;
	((CountedAsset *)proto)->m_name_key = (unsigned int)key;
	m_iterator58 = m_map44.begin();
}
