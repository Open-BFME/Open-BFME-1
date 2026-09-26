// Address-derived seven-byte unsigned-byte getter at 0x006BFE90.

class Rva006BFE90
{
public:
	unsigned char get() const;

private:
	char          m_pad00[ 0x132 ];
	unsigned char m_value;
};

unsigned char Rva006BFE90::get() const
{
	return m_value;
}
