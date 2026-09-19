// Retail 0x002214B0 reads the dword at this+4 and returns it.

class Rva002214B0DwordGetter
{
public:
	int get();

private:
	char m_padding[ 4 ];
	int m_value;
};

int Rva002214B0DwordGetter::get()
{
	return m_value;
}
