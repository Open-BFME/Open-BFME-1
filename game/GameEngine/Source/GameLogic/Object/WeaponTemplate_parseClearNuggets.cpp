// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail's ClearNuggets table entry proves WeaponTemplate ownership at 0x001E3F90.
// The callback name describes that key; its original C++ spelling is unknown.

class INI;

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}

class Rva001E3F90NuggetBase
{
public:
	virtual ~Rva001E3F90NuggetBase();
};

class Rva001E3F90Nugget : public Rva001E3F90NuggetBase
{
public:

	unsigned char m_pad04[0x50];
	volatile unsigned char m_field54;
};

struct Rva001E3F90Node
{
	Rva001E3F90Node *m_next;
	Rva001E3F90Node *m_previous;
	Rva001E3F90Nugget * volatile m_value;
};

class WeaponTemplate
{
private:
	static void parseClearNuggets(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_pad000[0x4DC];
	unsigned char m_field4DC;
	unsigned char m_pad4DD[0x528 - 0x4DD];
	unsigned char m_field528;
	unsigned char m_pad529[0x538 - 0x529];
	Rva001E3F90Node *m_nuggetList;
};

void WeaponTemplate::parseClearNuggets(INI *, void *instance, void *, const void *)
{
	WeaponTemplate *self = (WeaponTemplate *)instance;
	Rva001E3F90Node *node = self->m_nuggetList->m_next;
	while (node != self->m_nuggetList)
	{
		if (!self->m_field528 || node->m_value->m_field54)
		{
			Rva001E3F90Nugget *held = node->m_value;
			if (held)
				delete held;
		}
		node = node->m_next;
	}

	node = self->m_nuggetList->m_next;
	while (node != self->m_nuggetList)
	{
		Rva001E3F90Node *current = node;
		node = node->m_next;
		_STL::nodePoolDeallocate(current, sizeof(Rva001E3F90Node));
	}

	self->m_nuggetList->m_next = self->m_nuggetList;
	self->m_nuggetList->m_previous = self->m_nuggetList;
	self->m_field4DC = 0;
}
