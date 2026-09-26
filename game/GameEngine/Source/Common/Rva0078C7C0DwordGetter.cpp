// ?get@Rva0078C7C0DwordGetter@@QBEHXZ
// cl: /O2 /GR- /EHsc- /MD /DNDEBUG

class Rva0078C7C0DwordGetter
{
public:
	int get( void ) const;

private:
	char m_padding[ 0x0c ];
	int m_value;
};

int Rva0078C7C0DwordGetter::get( void ) const
{
	return m_value;
}
