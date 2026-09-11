// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
// cl: /O2 /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 money_get<wchar_t, istreambuf_iterator<wchar_t> > long-double
// overload at retail 0x00839410 (280B).  The TU-local specializations keep the
// visible callee bodies while preserving their retail out-of-line calls.

#include <locale>

typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
	BfmeMoneyWideIterator;

namespace _STL {

// ?push_back@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEXG@Z
template <>
__declspec(noinline)
void basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::push_back(wchar_t c)
{
	if (this->_M_finish + 1 == this->_M_end_of_storage._M_data)
		reserve(size() + (max)(size(), static_cast<size_type>(1)));
	_M_construct_null(this->_M_finish + 1);
	traits_type::assign(*(this->_M_finish), c);
	++this->_M_finish;
}

// ?_M_getc@?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@ABEXXZ
template <>
__declspec(noinline)
void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const
{
	if (_M_have_c)
		return;
	int_type c = _M_buf->sgetc();
	_M_c = traits_type::to_char_type(c);
	_M_eof = traits_type::eq_int_type(c, traits_type::eof());
	_M_have_c = true;
}

// ?deallocate@?$__node_alloc@$00$0A@@_STL@@SAXPAXI@Z
template <>
__declspec(noinline)
void __node_alloc<true, 0>::deallocate(void *p, size_t n) throw()
{
	if (n > (size_t)_MAX_BYTES)
		__stl_delete(p);
	else
		_M_deallocate(p, n);
}

}

// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@2@V32@0_NAAVios_base@2@AAHAAO@Z
template <>
BfmeMoneyWideIterator
_STL::money_get<wchar_t, BfmeMoneyWideIterator>::do_get(
	BfmeMoneyWideIterator first, BfmeMoneyWideIterator last, bool intl,
	_STL::ios_base &stream, _STL::ios_base::iostate &error,
	long double &units) const
{
	string_type buffer;
	first = do_get(first, last, intl, stream, error, buffer);
	if (error == _STL::ios_base::goodbit ||
		error == _STL::ios_base::eofbit)
	{
		buffer.push_back(0);
		string_type::iterator begin = buffer.begin();
		string_type::iterator end = buffer.end();
		_STL::__get_decimal_integer(begin, end, units);
	}
	if (first.equal(last))
		error |= _STL::ios_base::eofbit;
	return first;
}
