// cl: /DNDEBUG /MD /EHsc

class Rva000C8C60Holder
{
public:
	int &get();

private:
	char m_padding[ 0x8C ];
	int m_value;
};

int &Rva000C8C60Holder::get()
{
	return m_value;
}
