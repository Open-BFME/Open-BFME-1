// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Neutral ABI recovery for the 98-byte body at 0x002581B0.  The public owner
// is not proven by a named caller, vtable slot, or a unique source identity.

struct Rva002581B0Node
{
	Rva002581B0Node *m_next;
	Rva002581B0Node *m_previous;
};

struct Rva002581B0List
{
	Rva002581B0Node *m_next;
	Rva002581B0Node *m_previous;
};

namespace _STL
{
	template<bool threads, int instance> class __node_alloc
	{
	public:
		static void _M_deallocate( void *node, unsigned int bytes );
	};
}

extern void j_00020af9(void);
extern void j_0003839d(void);

class Rva002581B0LifecycleCall
{
public:
	void stage();
};

static __forceinline void callRva002581B0InitialStage(void *owner)
{
	typedef void (Rva002581B0LifecycleCall::*Function)();
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_00020af9;
	(reinterpret_cast<Rva002581B0LifecycleCall *>(owner)->*fn.member)();
}

static __forceinline void callRva002581B0FinalStage(void *owner)
{
	typedef void (Rva002581B0LifecycleCall::*Function)();
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_0003839d;
	(reinterpret_cast<Rva002581B0LifecycleCall *>(owner)->*fn.member)();
}

class Rva002581B0Owner
{
public:
	void run();

private:
	unsigned char m_pad00[0xe8];
	Rva002581B0List *m_list;
	unsigned int m_valueEC;
	unsigned int m_valueF0;
	unsigned int m_valueF4;
	unsigned char m_flagF8;
};

void Rva002581B0Owner::run()
{
	Rva002581B0Owner *self = this;
	callRva002581B0InitialStage(self);

	Rva002581B0Node *node = self->m_list->m_next;
	if( node != (Rva002581B0Node *)m_list )
	{
		do
		{
			Rva002581B0Node *old = node;
			node = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate( old, 0x0c );
		}
		while( node != (Rva002581B0Node *)self->m_list );
	}

	self->m_list->m_next = (Rva002581B0Node *)self->m_list;
	self->m_list->m_previous = (Rva002581B0Node *)self->m_list;
	self->m_valueEC = 0;
	self->m_valueF0 = 0;
	self->m_valueF4 = 0;
	self->m_flagF8 = 0;
	callRva002581B0FinalStage(self);
}
