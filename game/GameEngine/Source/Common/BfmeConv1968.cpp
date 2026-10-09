class BfmeSubESD;
namespace _STL {
 template<class T> class char_traits;
 template<class T> class allocator;
 struct __false_type;
 template<class C, class T, class A> class basic_string {
  template<class I> basic_string &_M_assign_dispatch(I, I, const __false_type &);
  friend class ::BfmeSubESD;
 };
}

class BfmeSubESD
{
public:

	BfmeSubESD &operator=(const BfmeSubESD &other)
	{
		if (&other != this)
		{
			void *spare;

			reinterpret_cast<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *>(this)->_M_assign_dispatch<char *>((char *)other.m_bfmeAESD, (char *)other.m_bfmeBESD, *reinterpret_cast<const _STL::__false_type *>(&spare));
		}

		return *this;
	}

	void *m_bfmeAESD;
	void *m_bfmeBESD;
	void *m_bfmeCESD;
};

class BfmeRecESD
{
public:
	BfmeRecESD &operator=(const BfmeRecESD &other);

	BfmeSubESD m_bfmeXESD;
	BfmeSubESD m_bfmeYESD;
	BfmeSubESD m_bfmeZESD;
	int m_bfme24ESD;
	int m_bfme28ESD;
};

BfmeRecESD &BfmeRecESD::operator=(const BfmeRecESD &other)
{
	m_bfmeXESD = other.m_bfmeXESD;
	m_bfmeYESD = other.m_bfmeYESD;
	m_bfmeZESD = other.m_bfmeZESD;

	m_bfme24ESD = other.m_bfme24ESD;
	m_bfme28ESD = other.m_bfme28ESD;

	return *this;
}
