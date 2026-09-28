// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x009A2CD0 / 0x009A4090 are byte-identical stdcall list-teardown
// walks: while the head is non-null, fetch the next link at +0x30, free the
// head through operator delete (0x00881EB0), and advance. The void __stdcall
// spelling is what emits the `ret 4` tail (the cdecl/free-function form
// emits a bare `ret`); the while-loop spelling is what emits retail's
// `test esi,esi / mov eax,esi / jne +0x10` latch instead of an early-out.
// IDENTITY IS NOT RECOVERED: the node layout keeps its address token and
// both twins land under distinct opaque owners (one-identity rule).
void __cdecl operator delete(void *) throw();

struct Rva009A2CD0Node
{
	char m_pad[0x30];
	void *m_next;
};

class Rva009A2CD0Owner
{
public:
	static void __stdcall Rva009A2CD0Walk(void *head);
};

void __stdcall Rva009A2CD0Owner::Rva009A2CD0Walk(void *head)
{
	void *cur = head;
	while (cur != 0)
	{
		void *next = ((Rva009A2CD0Node *)cur)->m_next;
		operator delete(cur);
		cur = next;
	}
}

struct Rva009A4090Node
{
	char m_pad[0x30];
	void *m_next;
};

class Rva009A4090Owner
{
public:
	static void __stdcall Rva009A4090Walk(void *head);
};

void __stdcall Rva009A4090Owner::Rva009A4090Walk(void *head)
{
	void *cur = head;
	while (cur != 0)
	{
		void *next = ((Rva009A4090Node *)cur)->m_next;
		operator delete(cur);
		cur = next;
	}
}
