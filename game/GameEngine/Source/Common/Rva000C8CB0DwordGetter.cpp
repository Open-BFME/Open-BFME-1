// cl: /DNDEBUG /MD /EHsc

class Rva000C8CB0Holder
{
public:
	unsigned int get() const;

private:
	char m_padding[ 0x6A0 ];
	unsigned int m_value;
};

unsigned int Rva000C8CB0Holder::get() const
{
	return m_value;
}
