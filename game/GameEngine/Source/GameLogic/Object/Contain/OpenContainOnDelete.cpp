// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME OpenContain::onDelete, retail 0x002269B0.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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

class Rva226790Template
{
public:
	Rva226790Template *getFinalOverride();

	unsigned long m_unknown;
	Rva226790Template *m_nextOverride;
	unsigned char m_padding[0xc4];
	unsigned long m_kindOf[3];
};

class BfmeDrop987
{
public:
	void bfmeClear987(int state, int value);
};

class Object
{
public:
	unsigned long m_vtable;
	Rva226790Template *m_template;
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

struct ContainedNode
{
	ContainedNode *m_next;
	ContainedNode *m_previous;
	Object *m_object;
};

struct ContainedList
{
	ContainedNode *m_sentinel;
};

class OpenContain
{
public:
	virtual void onDelete();

private:
	unsigned char m_padding[0x34];
	ContainedList m_containList;
	unsigned int m_containListSize;
	unsigned char m_unmodelled[0x77];
};

void OpenContain::onDelete()
{
	ContainedNode *sentinel = m_containList.m_sentinel;
	*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(this) + 0xb7) = 1;
	ContainedNode *node = sentinel->m_next;
	if (node == m_containList.m_sentinel)
		goto free_nodes;

first_node:
	{
		Object *object = node->m_object;
		node = node->m_next;
		_ReadWriteBarrier();
		*reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(object) + 0x214) = 0;
		_ReadWriteBarrier();
		Rva226790Template *objectTemplate = object->m_template;
		if (objectTemplate != 0 && objectTemplate->m_nextOverride != 0)
			objectTemplate = objectTemplate->m_nextOverride->getFinalOverride();
		if ((objectTemplate->m_kindOf[1] & 0x02000000) != 0)
			((BfmeDrop987 *)object)->bfmeClear987(8, 0);
		else
			TheGameLogic->destroyObject(object);
	}
	if (node != m_containList.m_sentinel)
		goto first_node;

	free_nodes:
	node = m_containList.m_sentinel->m_next;
	if (node != m_containList.m_sentinel)
	{
		do
		{
			ContainedNode *oldNode = node;
			node = node->m_next;
			_STL::nodePoolDeallocate(oldNode, 0xc);
		}
		while (node != m_containList.m_sentinel);
	}
	m_containList.m_sentinel->m_next = m_containList.m_sentinel;
	m_containList.m_sentinel->m_previous = m_containList.m_sentinel;
	m_containListSize = 0;
}
