// Retail 0x005376B0 is a four-byte field getter reached through the generated
// thunk at ILT 0x00035C33.  No caller proves a semantic owner, so the
// address-derived class records the field at this+0x14.

class Rva005376B0
{
public:
	int get( void ) const;

private:
	char m_padding[ 0x14 ];
	int m_value;
};

int Rva005376B0::get( void ) const
{
	return m_value;
}
