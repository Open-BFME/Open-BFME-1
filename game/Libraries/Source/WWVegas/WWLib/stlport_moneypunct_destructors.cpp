// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

typedef unsigned short wchar_t;

namespace _STL
{

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
	};
};

template <class CharT, bool International>
class moneypunct : public locale::facet
{
protected:
	virtual ~moneypunct();
};

template <class CharT, bool International>
moneypunct<CharT, International>::~moneypunct()
{
}

template class moneypunct<char, true>;
template class moneypunct<char, false>;
template class moneypunct<wchar_t, true>;
template class moneypunct<wchar_t, false>;

} // namespace _STL
