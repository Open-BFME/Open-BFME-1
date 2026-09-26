// cl: /DNDEBUG /MD /EHsc

class Rva000C8CC0Holder
{
public:
	unsigned char get() const;

private:
	char m_padding[ 0x29E ];
	unsigned char m_value;
};

unsigned char Rva000C8CC0Holder::get() const
{
	return m_value;
}
