class BfmeW1176;
namespace _STL {
 template<class T> class char_traits;
 template<class T> class allocator;
 template<class C, class T, class A> class basic_string { public: basic_string(const basic_string &); };
 template<class C, class T, class A> class basic_stringbuf {
  void _M_append_buffer() const;
  friend class ::BfmeW1176;
 };
}

// Open-BFME5 conversions.

class BfmeS1176
{
public:
};

class BfmeW1176
{
public:
	BfmeS1176 *bfmeGetText1176(BfmeS1176 *ret);
	char m_bfmePad[0x58];
	char m_bfme58;
};

BfmeS1176 *BfmeW1176::bfmeGetText1176(BfmeS1176 *ret)
{
	volatile int x = 0;

	reinterpret_cast<const _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> > *>(this)->_M_append_buffer();
	reinterpret_cast<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *>(ret)->_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::basic_string(*reinterpret_cast<const _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *>(&m_bfme58));

	return ret;
}
