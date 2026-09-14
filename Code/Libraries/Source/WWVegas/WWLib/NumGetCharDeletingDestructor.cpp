// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME: STLport num_get<char, istreambuf_iterator<char> > scalar-
// deleting destructor at retail RVA 0x00832360 (30 bytes).  The adjacent
// num_get<char> integer, floating-point, and long-double virtual slots in the
// retail facet vtable at 0x0112E97C establish the specialization identity;
// its complete destructor is the matched 7-byte body at 0x00832380.

namespace _STL
{
	template <class CHAR>
	class char_traits
	{
	};

	template <class CHAR, class TRAITS>
	class istreambuf_iterator
	{
	};

	class locale
	{
	public:
		class facet
		{
		protected:
			virtual ~facet();
		};
	};

	template <class CHAR, class ITERATOR>
	class num_get : public locale::facet
	{
	protected:
		virtual ~num_get();
		virtual void getLong() = 0;
		virtual void getDouble() = 0;
	};

	template <>
	num_get<char, istreambuf_iterator<char, char_traits<char> > >::~num_get()
	{
	}

} // namespace _STL

void forceSTLNumGetCharDeletingDestructor()
{
}
