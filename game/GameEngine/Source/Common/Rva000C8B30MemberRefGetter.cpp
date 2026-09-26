// cl: /DNDEBUG /MD /EHsc

class Rva000C8B30Holder
{
public:
	int &get();

private:
	char m_padding[ 0x98 ];
	int m_value;
};

int &Rva000C8B30Holder::get()
{
	return m_value;
}
