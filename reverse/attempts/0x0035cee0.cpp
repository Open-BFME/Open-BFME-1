// ?Rva0035CEE0@@YAXPAURva0035CEE0Item@@PBU1@@Z
// partial score=0.17 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: anonymous carved body at 0x0035CEE0 (460 bytes), boundary
// "jmp-tail" (ends with an unconditional jmp to a shared continuation, not
// a ret). Structural twin of the already-banked 0x0035D460 (see
// Rva0035D460ScriptQueueCopy.cpp): same dword+dword+UnicodeString(via
// ?set@UnicodeString, offset +8)+byte+word+deque<T*> record copy shape,
// same push_back chain (_M_initialize_map/_M_reallocate_map/allocate/
// operator new/_M_deallocate, all pinned, element Rva0035AF40Element 4B).
// The deque element here is a small polymorphic node -- vtable 0x010E855C
// is shared with the landed Rva00359330StringRecordTable::addNode
// (Rva00359330StringRecordAddDefaultNode.cpp), whose Rva00354BC0 node
// class gives the exact 20-byte layout {link, vptr, pair(8B), byte, byte,
// byte}; here the pair and the two trailing bytes are copied from the
// source node (through the still dump-only Rva003525E0 pair copy ctor)
// instead of default-initialized.

class UnicodeString
{
public:
	void set(const UnicodeString &src);

	const void *m_data;
};

extern "C" void Rva003525E0PairCopyCtor(void *dest, const void *src);

class Rva0035CEE0Node
{
public:
	Rva0035CEE0Node *m_link;

private:
	void *m_vptr;
	int m_pair0;
	int m_pair1;
	char m_10;
	char m_11;
	char m_12;

public:
	explicit Rva0035CEE0Node(const void *srcInner) : m_link(0)
	{
		m_vptr = (void *)0x010E855C;
		Rva003525E0PairCopyCtor(&m_pair0,
			srcInner ? (const char *)srcInner + 4 : 0);
		if (srcInner)
		{
			m_10 = *((const char *)srcInner + 0xc);
			m_11 = *((const char *)srcInner + 0xd);
		}
		m_12 = 0;
	}
};

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

struct Rva0035CEE0Item
{
	unsigned int m_field0;
	unsigned int m_field1;
	UnicodeString m_name;
	unsigned char m_flag;
	unsigned short m_word;
	_STL::deque<Rva0035CEE0Node *> m_records;
};

// address-derived identity: only reachable via one unlanded caller
void Rva0035CEE0(Rva0035CEE0Item *dest, const Rva0035CEE0Item *src)
{
	dest->m_field0 = src->m_field0;
	dest->m_field1 = src->m_field1;
	dest->m_name.set(src->m_name);
	dest->m_flag = src->m_flag;
	dest->m_word = src->m_word;

	new (&dest->m_records) _STL::deque<Rva0035CEE0Node *>();

	for (_STL::deque<Rva0035CEE0Node *>::const_iterator it =
		src->m_records.begin(); it != src->m_records.end(); ++it)
	{
		const void *srcInner = *(const void *const *)*it;
		dest->m_records.push_back(new Rva0035CEE0Node(srcInner));
	}
}
