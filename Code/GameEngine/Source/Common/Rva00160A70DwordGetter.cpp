// cl: /O2 /Ob0

// The carved body reads one four-byte field at this+0x34.  No caller or
// owning class evidence gives that field a semantic name, so this type keeps
// the retail address in its name.

class Rva00160A70Dword
{
public:
	unsigned int get() const;

private:
	char m_prefix[ 0x34 ];
	unsigned int m_value;
};

unsigned int Rva00160A70Dword::get() const
{
	return m_value;
}
