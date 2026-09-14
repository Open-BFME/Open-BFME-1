// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: _STL::ctype<char> scalar-deleting destructor at retail RVA
// 0x00840D20.  The matched specialization constructor at 0x00840730 installs
// vtable 0x0112F254, whose case-conversion, widen, and narrow slots establish
// the canonical STLport facet identity.

namespace _STL
{
	template <class T>
	class ctype
	{
	public:
		virtual ~ctype();
	};
}

void forceSTLCtypeCharDeletingDestructor()
{
	_STL::ctype<char> value;
}
