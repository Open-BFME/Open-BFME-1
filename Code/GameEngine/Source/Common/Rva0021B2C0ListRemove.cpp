// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021B2C0. Walk the circular list at +0x9BC for a payload;
// unlink and STLport-deallocate a 12-byte node, else finish(payload).

struct BfmeNode21B2C0
{
	BfmeNode21B2C0 *next;
	BfmeNode21B2C0 *prev;
	void *value;
};

void __cdecl bfmeDeallocate(void *p, unsigned int n);

class BfmeRvaA760Object;

class Rva0024A760
{
public:
	void finish(BfmeRvaA760Object *obj);
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
				bfmeDeallocate(n, 12);
				return;
			}
			n = n->next;
		} while (n != head);
	}
	finish(obj);
}
