// cl: /O2 /Ob0

class Rva008FE890
{
	char m_lead[0x70];
	int m_flag;

public:
	int get();
};

int Rva008FE890::get()
{
	return m_flag ? 20000 : 0;
}
