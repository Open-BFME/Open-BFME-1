// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00958790 initializes a _bstr_t Data node from a narrow string:
// refs = 0, len = 1, then the wide string through _com_util::
// ConvertStringToBSTR at 0x00AFD750, returning this. Same member order as
// the landed Bstr_t_ctor Data(value) precedent. Neighbours:
// Rva87820PointerPresent, Small03eComGuard, Rva009587C0Increment.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
namespace _com_util { unsigned short *__stdcall ConvertStringToBSTR(const char *value); }
class Rva00958790Box
{
public:
	Rva00958790Box *init(const char *value);
	unsigned short *m_wstr;
	long m_refs;
	long m_len;
};
Rva00958790Box *Rva00958790Box::init(const char *value)
{
	m_refs = 0;
	m_len = 1;
	m_wstr = _com_util::ConvertStringToBSTR(value);
	return this;
}
