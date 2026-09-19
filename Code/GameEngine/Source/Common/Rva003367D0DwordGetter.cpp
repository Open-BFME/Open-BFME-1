// Retail 0x003367D0 reads the dword at this+8 and returns it.

class Rva003367D0DwordGetter
{
public:
	int get();

private:
	char m_padding[ 8 ];
	int m_value;
};

int Rva003367D0DwordGetter::get()
{
	return m_value;
}
