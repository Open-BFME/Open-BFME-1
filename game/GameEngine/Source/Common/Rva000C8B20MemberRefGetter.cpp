// cl: /DNDEBUG /MD /EHsc

class Rva000C8B20Holder
{
public:
	int &get();

private:
	char m_padding[ 0x8C ];
	int m_value;
};

int &Rva000C8B20Holder::get()
{
	return m_value;
}
