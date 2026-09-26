// cl: /DNDEBUG /MD /EHsc

class Rva000C8B70Holder
{
public:
	int &get();

private:
	char m_padding[ 0x110 ];
	int m_value;
};

int &Rva000C8B70Holder::get()
{
	return m_value;
}
