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

template <class CharT>
class ctype : public locale::facet
{
protected:
	virtual ~ctype();
};

template <class CharT>
ctype<CharT>::~ctype()
{
}

template class ctype<wchar_t>;

template <class InternT, class ExternT, class StateT>
class codecvt : public locale::facet
{
protected:
	virtual ~codecvt();
};

template <class InternT, class ExternT, class StateT>
codecvt<InternT, ExternT, StateT>::~codecvt()
{
}

template class codecvt<char, char, int>;
template class codecvt<wchar_t, char, int>;

template <class CharT>
class collate : public locale::facet
{
protected:
	virtual ~collate();
};

template <class CharT>
collate<CharT>::~collate()
{
}

template class collate<char>;
template class collate<wchar_t>;

template <class CharT>
class numpunct : public locale::facet
{
protected:
	virtual ~numpunct();
};

template <class CharT>
numpunct<CharT>::~numpunct()
{
}

template class numpunct<char>;
template class numpunct<wchar_t>;

} // namespace _STL
