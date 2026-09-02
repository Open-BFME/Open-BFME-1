// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

class AsciiString
{
	public:
	AsciiString( const AsciiString &other );
	~AsciiString();

	private:
	void *m_data;
};

// The generated payload name records the observed 12-byte copy-and-destroy
// shape. Its first dword is a string-family subobject; the remaining two
// dwords are copied inline by MSVC 7.1.
struct Gen_t_00595870_p12cd
{
	AsciiString m_name;
	int m_first;
	int m_second;
};

void BfmeGen00595870DequeAnchor(
	_STL::deque<Gen_t_00595870_p12cd> &values,
	const Gen_t_00595870_p12cd &value )
{
	values.push_back( value );
}
