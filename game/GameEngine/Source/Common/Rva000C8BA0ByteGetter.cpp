// cl: /DNDEBUG /MD /EHsc

class Rva000C8BA0Holder
{
public:
	unsigned char get() const;

private:
	char m_padding[ 0x118 ];
	unsigned char m_value;
};

unsigned char Rva000C8BA0Holder::get() const
{
	return m_value;
}
