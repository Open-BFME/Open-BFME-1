// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Open-BFME: address-derived reconstruction of the BFME WeaponTemplate
// ClearNuggets parser callback at retail 0x001E3F90.

class INI;

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int bytes);
};
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

class Rva001E3F90Owner
{
public:
	static void parse(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_pad000[0x4DC];
	unsigned char m_field4DC;
	unsigned char m_pad4DD[0x528 - 0x4DD];
	unsigned char m_field528;
	unsigned char m_pad529[0x538 - 0x529];
	Rva001E3F90Node *m_nuggetList;
};

void Rva001E3F90Owner::parse(INI *, void *instance, void *, const void *)
{
	Rva001E3F90Owner *self = (Rva001E3F90Owner *)instance;
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
		_STL::__node_alloc<true, 0>::_M_deallocate(current, sizeof(Rva001E3F90Node));
	}

	self->m_nuggetList->m_next = self->m_nuggetList;
	self->m_nuggetList->m_previous = self->m_nuggetList;
	self->m_field4DC = 0;
}
