// ?d_0042cdf0@@YAXXZ
// partial score=0.2 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

void *bfmeAllocNode(unsigned int bytes);
inline void * __cdecl operator new(unsigned int, void *where) { return where; }

struct Rva0042CDF0Node
{
	Rva0042CDF0Node *next;
	Rva0042CDF0Node *prev;
	void *value;
};

struct FXListNodes
{
	Rva0042CDF0Node *head;
};

class FXList
{
public:
	virtual ~FXList();
	FXListNodes m_nodes;
};

struct BfmeCtorNodeD
{
	BfmeCtorNodeD *next;
	BfmeCtorNodeD *prev;
	void *value;
};

class BfmeCtorListD
{
public:
	BfmeCtorListD(void);
	~BfmeCtorListD(void);
	BfmeCtorNodeD *m_bfmeNode;
};

class BfmeThingASABase
{
public:
	BfmeThingASABase(void);
	void *volatile m_bfmeVftA;
};

class Rva0042CDF0Secondary
{
public:
	virtual void release(int mode);
};

class BfmeThingASA : public BfmeThingASABase
{
public:
	BfmeThingASA(void *one);
	BfmeCtorListD m_listA;
	unsigned char m_flag8;
	AsciiString m_name;
	unsigned char m_flag10;
	int m_zero14;
	BfmeCtorListD m_listB;
	int m_limit;
	int m_period;
	Rva0042CDF0Secondary m_bfmeVftB;
	volatile int m_refCount;
};

class Rva0042CDF0Handle
{
public:
	Rva0042CDF0Handle(void) : m_pointer(0) {}
	~Rva0042CDF0Handle(void)
	{
		if (m_pointer)
		{
			int refs = m_pointer->m_refCount;
			Rva0042CDF0Secondary *secondary = &m_pointer->m_bfmeVftB;
			--refs;
			m_pointer->m_refCount = refs;
			if (refs <= 0)
				secondary->release(1);
		}
	}
	void attach(BfmeThingASA *pointer)
	{
		m_pointer = pointer;
		if (m_pointer)
			++m_pointer->m_refCount;
	}
	BfmeThingASA *get(void) const { return m_pointer; }

private:
	BfmeThingASA *m_pointer;
	int m_guard;
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
	BfmeThingASA *&Rva0042CDF0(BfmeThingASA *&result, const char *name);
};

BfmeThingASA *&FXListStore::Rva0042CDF0(BfmeThingASA *&result, const char *name)
{
	Rva0042CDF0Handle holder;
	BfmeThingASA *thing = 0;
	void *storage = 0;
	const FXList *source = findFXList(name);

	if (!source)
	{
		result = 0;
		return result;
	}

	storage = ::operator new(0x2c);
	if (storage)
	{
		{
			AsciiString text(name);
			new ((BfmeThingASA *)storage) BfmeThingASA(&text);
			thing = (BfmeThingASA *)storage;
			thing->m_refCount = 0;
			*(void **)&thing->m_bfmeVftB = (void *)0x010EAD58;
			thing->m_bfmeVftA = (void *)0x010F3558;
			*(void **)&thing->m_bfmeVftB = (void *)0x010F3554;
			holder.attach(thing);
		}
	}

	if (holder.get())
	{
		Rva0042CDF0Node *node = (Rva0042CDF0Node *)holder.get()->m_listA.m_bfmeNode;
		Rva0042CDF0Node *first = ((FXListNodes *)&source->m_nodes)->head;
		first = first->next;
		while (first != ((FXListNodes *)&source->m_nodes)->head)
		{
			void *value = first->value;
			Rva0042CDF0Node *newNode = (Rva0042CDF0Node *)bfmeAllocNode(0xc);
			if (newNode)
				new (&newNode->value) void *(value);
			Rva0042CDF0Node *previous = node->prev;
			newNode->next = node;
			newNode->prev = previous;
			previous->next = newNode;
			node->prev = newNode;
			first = first->next;
		}
	}

	result = holder.get();
	if (result)
		++result->m_refCount;
	return result;
}
