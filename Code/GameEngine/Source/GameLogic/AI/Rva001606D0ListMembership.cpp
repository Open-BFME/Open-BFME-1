// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x001606D0 and 0x001608A0, 36 bytes each through the `ret 4` at
// +0x21 (int3 padding follows).  Both are intrusive-list membership tests:
// the node is in the list when it is the head or has either link set.  Their
// shared `return 1` tails (0x001606EC, 0x001608BC) were split off by Ghidra
// and claimed as 8-byte aliases; every early exit branches there.  The first
// uses the head at +4 and links at +4/+8 of the node, as the list whose
// remove is at 0x00160740; the second the head at +8 and links at
// +0xC/+0x10.  No caller names either owner, so the names keep the address.

class Rva001606D0Node
{
public:
	char m_unmodelled00[ 4 ];
	Rva001606D0Node *m_next;
	Rva001606D0Node *m_prev;
};

class Rva001606D0List
{
public:
	int isInList( const Rva001606D0Node *node ) const;

private:
	char m_unmodelled00[ 4 ];
	Rva001606D0Node *m_head;
};

int Rva001606D0List::isInList( const Rva001606D0Node *node ) const
{
	return m_head == node || node->m_next != 0 || node->m_prev != 0;
}

class Rva001608A0Node
{
public:
	char m_unmodelled00[ 0xC ];
	Rva001608A0Node *m_next;
	Rva001608A0Node *m_prev;
};

class Rva001608A0List
{
public:
	int isInList( const Rva001608A0Node *node ) const;

private:
	char m_unmodelled00[ 8 ];
	Rva001608A0Node *m_head;
};

int Rva001608A0List::isInList( const Rva001608A0Node *node ) const
{
	return m_head == node || node->m_next != 0 || node->m_prev != 0;
}
