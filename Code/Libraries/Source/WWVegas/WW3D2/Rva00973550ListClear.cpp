// cl: /DNDEBUG /MD /O2 /EHs-c-

void __cdecl operator delete(void *);

struct Rva00973550Node
{
	Rva00973550Node *next;
};

class Rva00973550List
{
public:
	void clear();

private:
	void *unused;
	Rva00973550Node *head;
};

void Rva00973550List::clear()
{
	while (head)
	{
		Rva00973550Node *next = head->next;
		operator delete(head);
		head = next;
	}
}
