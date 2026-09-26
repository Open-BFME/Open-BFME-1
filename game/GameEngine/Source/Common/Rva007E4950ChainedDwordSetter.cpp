// Address-derived reconstruction of the 13-byte chained dword setter at 0x007E4950.

struct Rva007E4950Payload
{
	char m_pad00[ 0x20 ];
	int m_value;
};

class Rva007E4950ChainedDword
{
public:
	void setValue( int value );

private:
	char m_pad00[ 0x2C ];
	Rva007E4950Payload *m_payload;
};

void Rva007E4950ChainedDword::setValue( int value )
{
	m_payload->m_value = value;
}
