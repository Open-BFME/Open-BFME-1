// cl: /O2 /Ob0

class Rva00696690
{
	char m_lead[4];
	char *m_ptr;

public:
	char *get();
};

char *Rva00696690::get()
{
	return m_ptr - 0x78;
}
