// cl: /DNDEBUG /MD /EHsc
// The carved body at retail RVA 0x006E7B20 copies three argument dwords.
// No caller or table proves the owning class, so both names keep the address.

typedef int Int;

struct Rva006E7B20Vector3
{
	Int m_x;
	Int m_y;
	Int m_z;
};

class Rva006E7B20Vector3Slot
{
public:
	void set( const Rva006E7B20Vector3 &value );

private:
	char m_head[ 0x140 ];
	Int m_x;
	Int m_y;
	Int m_z;
};

// ?set@Rva006E7B20Vector3Slot@@QAEXABURva006E7B20Vector3@@@Z
void Rva006E7B20Vector3Slot::set( const Rva006E7B20Vector3 &value )
{
	m_x = value.m_x;
	m_y = value.m_y;
	m_z = value.m_z;
}
