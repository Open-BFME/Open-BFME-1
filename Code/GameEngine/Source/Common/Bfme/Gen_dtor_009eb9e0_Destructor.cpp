// ??1Gen_dtor_009eb9e0@@QAE@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail RVA 0x009F23C0, 563 bytes: the complete-object destructor of the
// object at global 0x0134FAAC (pins ??1Gen_dtor_009eb9e0 on this row; callers
// Rva009EB960::~Rva009EB960 and the generated
// ??_GGen_dtor_009eb9e0). Its constructor ??0Gen_dtor_009eb9e0 at 0x009F2140
// (Rva009EB960Ctor.cpp) fixes the 0x1F4-byte layout used here,
// and the retail member-destructor order matches it: four set groups
// (+0x1CC..+0x190) through ILT 0x00015D7A, the seven deques through the EH
// vector destructor with 0x009EDFE0, then the hash maps at +0x44 (0x009EE750)
// and +0x0C (0x009EE630). Identity beyond that is address-derived.
//
// Body: reset the +0x1B8 group from an empty one, push it through the
// receiver methods 0x009F0E50 and 0x009F19E0, drain while any deque is
// non-empty (0x009F19E0, worker 0x009F1510, Sleep(1)), clear the global,
// raise the +0x08 flag and wait for the thread from the constructor, mark
// every +0x44 map object delete-on-release and release it, clear the map,
// delete the +0x1F0 worker and delete both critical sections.
// The receiver methods are reached through their pinned address-derived
// views of this same object (Q1Receiver0134FAAC, Gen009F1510). The group
// type is viewed as BfmeThingBVA, whose pinned bfmeStepBVA (ILT 0x00015280
// -> 0x00135DF0) is the pointer-set tree assignment the landed m009F19E0
// uses in the same guarded group copy.

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

class BfmeThingBVA
{
public:
	BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

// The shared release leaf 0x009EB7A0 decrements the low word at +4 and, once
// it reaches zero with bit 24 set, dispatches through the vtable at +0.
class Rva009EB7A0RefOwner
{
public:
	void Release_Ref();

	void *m_vtable;
	unsigned int m_refs : 16;
	unsigned int m_bits16 : 8;
	unsigned int m_deleteOnRelease : 1;
	unsigned int m_bits25 : 7;
};

struct Gen_t_009ee630_p12cd
{
	int a[3];
};

struct Gen_t_009ee750_p12cd
{
	Rva009EB7A0RefOwner *m_object;
	int m_unmodelled[2];
};

struct Gen_t_009edfe0_p12cd
{
	int a[3];
};

class Rva009EEA70CleanupDeleting
{
public:
	virtual ~Rva009EEA70CleanupDeleting();
};

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

class Q1Receiver0134FAAC
{
public:
	void m009F0E50(int value);
	void m009F19E0(int value);
};

class Gen009F1510
{
public:
	void handle();
};

typedef _STL::hash_map<int, Gen_t_009ee630_p12cd> GenHashMap0C;
typedef _STL::hash_map<int, Gen_t_009ee750_p12cd> GenHashMap44;
typedef _STL::deque<Gen_t_009edfe0_p12cd> GenDeque;

class Gen_dtor_009eb9e0
{
public:
	~Gen_dtor_009eb9e0();

private:
	uintptr_t m_thread;
	void *m_unknown04;
	bool m_active;
	unsigned char m_pad09[3];
	GenHashMap0C m_map0c;
	unsigned int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	GenHashMap44 m_map44;
	GenHashMap44::iterator m_iterator58;
	CRITICAL_SECTION m_lock60;
	GenDeque m_deques78[7];
	BfmeThingBVA m_set190;
	BfmeThingBVA m_set1a4;
	BfmeThingBVA m_set1b8;
	BfmeThingBVA m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_pad1e8[4];
	bool m_flag1ec;
	bool m_flag1ed;
	bool m_flag1ee;
	unsigned char m_pad1ef;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(Gen_dtor_009eb9e0) == 0x1f4 ? 1 : -1];

Gen_dtor_009eb9e0::~Gen_dtor_009eb9e0()
{
	Q1Receiver0134FAAC *receiver = (Q1Receiver0134FAAC *)this;

	{
		BfmeThingBVA empty;
		m_set1b8 = empty;
	}
	receiver->m009F0E50((int)&m_set1b8);
	receiver->m009F19E0((int)&m_set1b8);

	m_field24 = 0;
	for (;;)
	{
		int i;
		for (i = 0; i < 7; ++i)
		{
			if (!m_deques78[i].empty())
				break;
		}
		if (i >= 7)
			break;
		receiver->m009F19E0((int)&m_set1b8);
		((Gen009F1510 *)this)->handle();
		Sleep(1);
	}

	g_theAssetRegistry = 0;
	m_active = true;
	WaitForSingleObject((HANDLE)m_thread, INFINITE);

	for (GenHashMap44::iterator it = m_map44.begin(); it != m_map44.end(); ++it)
	{
		it->second.m_object->m_deleteOnRelease = 1;
		it->second.m_object->Release_Ref();
	}
	m_map44.clear();

	delete m_hashContext;
	DeleteCriticalSection(&m_lock2c);
	DeleteCriticalSection(&m_lock60);
}
