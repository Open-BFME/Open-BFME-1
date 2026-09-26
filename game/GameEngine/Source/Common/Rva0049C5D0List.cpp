// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0049C5D0List
{
public:
	void push(Rva0049C5D0List **head);

	char m_pad[0x60];
	Rva0049C5D0List *m_next;
};

void Rva0049C5D0List::push(Rva0049C5D0List **head)
{
	m_next = *head;
	*head = this;
}
