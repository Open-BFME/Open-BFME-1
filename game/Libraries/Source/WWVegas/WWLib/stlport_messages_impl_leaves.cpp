// cl: /O2 /EHsc /MD
// STLport 4.5.3 _Messages::do_close and its compiler-written scalar deleting
// destructor (src/messages.cpp).
//
// The vtable at VA 0x0112FBA0 sits behind an RTTI complete object locator
// spelling '.?AV_Messages@_STL@@'.  _Messages declares do_open, the two do_get
// overloads, do_close and then its destructor, so slot 0 is do_open, slot 3 is
// do_close and slot 4 is the deleting destructor.  game/stlport/MessagesDtor.cpp
// already reads slot 4 that way when messages<char> releases an owned
// _Messages, and the two messages do_open forwarders in
// stlport_messages_do_open.cpp tail-jump to slot 0 with a narrow string and a
// locale still on the stack.

namespace _STL
{

template <class CharT> class char_traits;
template <class T> class allocator;
template <class CharT, class Traits, class Alloc> class basic_string;

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class locale;

class _Messages
{
public:
	typedef int catalog;

	virtual catalog do_open(const string &name, const locale &loc) const;
	virtual void *do_get_c() const;
	virtual void *do_get_w() const;
	virtual void do_close(catalog c) const;
	virtual ~_Messages();

	bool _M_delete;
	void *_M_message_obj;
};

_Messages::catalog _Messages::do_open(const string &, const locale &) const
{
	return -1;
}

void _Messages::do_close(catalog) const
{
}

// The destructor body is empty and retail folded it away, so only the
// compiler-written deleting wrapper above it survives as a real body.
// ??1_Messages@_STL@@UAE@XZ present-unmatched
_Messages::~_Messages()
{
}

} // namespace _STL
