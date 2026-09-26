// cl: /DNDEBUG /MD /EHsc

class Rva000C8B00Holder
{
public:
	int &get();

private:
	char m_padding[ 0xE8 ];
	int m_value;
};

int &Rva000C8B00Holder::get()
{
	return m_value;
}
