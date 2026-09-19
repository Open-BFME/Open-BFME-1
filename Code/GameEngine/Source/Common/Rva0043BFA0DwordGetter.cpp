// ?get@Rva0043BFA0DwordGetter@@QBEIXZ
// cl: /O2 /GR- /EHsc- /MD /DNDEBUG

class Rva0043BFA0DwordGetter
{
public:
	unsigned int get( void ) const;

private:
	char m_padding[ 0x04 ];
	unsigned int m_value;
};

unsigned int Rva0043BFA0DwordGetter::get( void ) const
{
	return m_value;
}
