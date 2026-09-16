// cl: /DNDEBUG /MD /EHsc
//
// The retail body at 0x000C0B00 constructs a 0x14-byte circular list node.
// No caller or vtable proves a semantic class name, so this source keeps the
// address-derived owner Rva000C0B00.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

}

class Rva000C0B00Node
{
public:
	char m_flag;
	unsigned char m_padding[3];
	int m_value;
	Rva000C0B00Node *m_next;
	Rva000C0B00Node *m_previous;
	int m_tail;
};

class Rva000C0B00
{
public:
	Rva000C0B00();

	volatile char m_firstFlag;
	volatile char m_secondFlag;
	volatile char m_thirdFlag;
	unsigned char m_padding;
	volatile int m_status;
	Rva000C0B00Node *m_node;
	volatile int m_count;
};

Rva000C0B00::Rva000C0B00()
{
	m_firstFlag = 1;
	m_secondFlag = 1;
	m_thirdFlag = 1;
	m_status = -1;
	_ReadWriteBarrier();
	m_node = 0;
	m_node = (Rva000C0B00Node *)_STL::__new_alloc::allocate(0x14);
	m_count = 0;
	m_node->m_flag = 0;
	m_node->m_value = 0;
	m_node->m_next = m_node;
	m_node->m_previous = m_node;
}
