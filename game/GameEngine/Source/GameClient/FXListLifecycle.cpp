// cl: /DNDEBUG /MD /EHsc
// Retail establishes the 36-byte layout; list helper names and unknown field types remain descriptive.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class FXNugget
{
public:
	virtual ~FXNugget();
};

struct FXNuggetNode
{
	FXNuggetNode *next;
	FXNuggetNode *prev;
	FXNugget *value;
};

struct Rva0042D170Member04
{
	Rva0042D170Member04(const Rva0042D170Member04 &);
	~Rva0042D170Member04();
	FXNuggetNode *head;
};

struct Rva0042D170Member18
{
	Rva0042D170Member18(const Rva0042D170Member18 &);
	~Rva0042D170Member18();
	void *m_head;
};

namespace _STL
{
// retail 0x0082E5F0 is STLport's private node-pool entry; reach it under its real name.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}
static inline void bfmeDeallocate(void *block, unsigned int bytes) { _STL::nodePoolDeallocate(block, bytes); }

class FXList
{
public:
	FXList(const FXList &other);
	virtual ~FXList();
	void clear();
private:
	Rva0042D170Member04 m_nuggets;
	unsigned char m_field08;
	AsciiString m_string0C;
	unsigned char m_playEvenIfShrouded;
	int m_trackingFrames;
	Rva0042D170Member18 m_list18;
	int m_cullTrackingMax;
	int m_cullTrackingMin;
};

FXList::FXList(const FXList &other)
	: m_nuggets(other.m_nuggets)
	, m_field08(other.m_field08)
	, m_string0C(other.m_string0C)
	, m_playEvenIfShrouded(other.m_playEvenIfShrouded)
	, m_trackingFrames(other.m_trackingFrames)
	, m_list18(other.m_list18)
	, m_cullTrackingMax(other.m_cullTrackingMax)
	, m_cullTrackingMin(other.m_cullTrackingMin)
{
}

FXList::~FXList()
{
	clear();
}

void FXList::clear()
{
	FXNuggetNode *node = m_nuggets.head->next;
	while (node != m_nuggets.head)
	{
		delete node->value;
		node = node->next;
	}
	FXNuggetNode *walk = m_nuggets.head->next;
	while (walk != m_nuggets.head)
	{
		FXNuggetNode *current = walk;
		walk = walk->next;
		bfmeDeallocate(current, sizeof(FXNuggetNode));
	}
	m_nuggets.head->next = m_nuggets.head;
	m_nuggets.head->prev = m_nuggets.head;
}
