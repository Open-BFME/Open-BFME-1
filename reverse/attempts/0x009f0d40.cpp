// ?m009F0D40@Q1Receiver0134FAAC@@QAEXH@Z
// partial score=0.62 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Q1Receiver0134FAAC::m009F0D40, retail 0x009F0D40, 265 bytes.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

struct Q1ReceiverSetNode : public _STL::_Rb_tree_node_base
{
	int m_key;
};

struct Q1ReceiverHashNode
{
	Q1ReceiverHashNode *m_next;
	int m_key;
};

struct Q1ReceiverHashTable
{
	unsigned char m_unmodelled_000[4];
	Q1ReceiverHashNode **m_buckets;
	Q1ReceiverHashNode **m_bucketsEnd;
	unsigned char m_unmodelled_00C[0x10];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	void *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	void *lock);

namespace _STL
{
template <class Dummy>
class _Rb_global;
}

class Q1Receiver0134FAAC
{
public:
	void m009F0D40(int value);
	void prepare(Q1ReceiverSet *set);

private:
	unsigned char m_unmodelled_000[0x2C];
	unsigned char m_lock_02C[0x18];
	Q1ReceiverHashTable m_table;
	unsigned char m_lock_060[0x18];
};

void Q1Receiver0134FAAC::m009F0D40(int value)
{
	Q1ReceiverSet set(*(Q1ReceiverSet *)value);
	prepare(&set);

	void *lock60 = m_lock_060;
	void *lock2c = m_lock_02C;
	EnterCriticalSection(lock60);
	EnterCriticalSection(lock2c);

	Q1ReceiverSetNode *sentinel =
		*(Q1ReceiverSetNode **)(void *)&set;
	Q1ReceiverSetNode *node =
		*(Q1ReceiverSetNode **)((unsigned char *)sentinel + 8);
	Q1ReceiverHashTable *table = &m_table;
	while (node != sentinel)
	{
		int key = node->m_key;
		unsigned int bucketCount =
			(unsigned int)(table->m_bucketsEnd - table->m_buckets);
		Q1ReceiverHashNode *bucket =
			table->m_buckets[(unsigned int)key / bucketCount];
		while (bucket && bucket->m_key != key)
			bucket = bucket->m_next;
		if (bucket)
			bucket->m_key |= 0x04000000;

		node = (Q1ReceiverSetNode *)
			_STL::_Rb_global<bool>::_M_increment(node);
	}

	LeaveCriticalSection(lock2c);
	LeaveCriticalSection(lock60);
}
