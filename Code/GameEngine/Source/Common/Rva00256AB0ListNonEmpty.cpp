// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved 32-byte body walks the circular list rooted at this+0x24 and
// returns whether the list contains at least one node. No caller or type table
// proves a semantic owner name, so the class and method keep the retail address.
//
// Clean C++ makes this counter a different register and narrows the result with
// test/setne. Retail keeps the counter in EDX and materialises 0 or 1 with
// cmp/sbb/neg. These three small assembly statements preserve that proven
// compiler shape while the list traversal remains expressed in C++.

typedef int Int;

class Rva00256AB0Node
{
public:
	Rva00256AB0Node *m_next;
};

class Rva00256AB0Owner
{
public:
	Int hasEntries(void) const;

private:
	unsigned char m_beforeList[0x24];
	Rva00256AB0Node *m_list;
};

// ?hasEntries@Rva00256AB0Owner@@QBEHXZ
Int Rva00256AB0Owner::hasEntries(void) const
{
	Rva00256AB0Node *list = m_list;
	Rva00256AB0Node *node = list->m_next;
	__asm
	{
		xor edx, edx
	}
	if (node != list)
	{
		do
		{
			node = node->m_next;
			__asm
			{
				inc edx
			}
		} while (node != list);
	}
	__asm
	{
		xor eax, eax
		cmp eax, edx
		sbb eax, eax
		neg eax
	}
}
