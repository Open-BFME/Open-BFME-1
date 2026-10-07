// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021B2C0. Walk the circular list at +0x9BC for a payload;
// unlink and STLport-deallocate a 12-byte node, else finish(payload).

struct BfmeNode21B2C0
{
	BfmeNode21B2C0 *next;
	BfmeNode21B2C0 *prev;
	void *value;
};

// Retail calls 0x0082E5F0, matched _STL::__node_alloc<1,0>::_M_deallocate.
extern "C" void __cdecl __identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(void *p, unsigned int n);
extern void j_0003dee7(void);

class BfmeRvaA760Object;

class Rva0024A760
{
public:
	void bfmeRemove(BfmeRvaA760Object *obj);

private:
	char m_pad[0x9BC];
	BfmeNode21B2C0 *m_head;
};

// ?bfmeRemove@Rva0024A760@@QAEXPAVBfmeRvaA760Object@@@Z
void Rva0024A760::bfmeRemove(BfmeRvaA760Object *obj)
{
	BfmeNode21B2C0 *head = m_head;
	BfmeNode21B2C0 *n = head->next;
	if (n != head)
	{
		do
		{
			if (n->value == (void *)obj)
			{
				BfmeNode21B2C0 *next = n->next;
				BfmeNode21B2C0 *prev = n->prev;
				prev->next = next;
				next->prev = prev;
				__identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(n, 12);
				return;
			}
			n = n->next;
		} while (n != head);
	}
	typedef void (Rva0024A760::*Rva0024A760FinishCall)(BfmeRvaA760Object *);
	union
	{
		void (*function)(void);
		Rva0024A760FinishCall method;
	} finish = { j_0003dee7 };
	(this->*finish.method)(obj);
}
