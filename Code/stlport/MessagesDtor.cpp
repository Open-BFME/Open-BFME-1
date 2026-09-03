// cl: /O2 /EHsc /MD
// STLport 4.5.3 messages<char>/messages<unsigned short> destructors
// (src/messages.cpp). Optionally-owned _Messages via vtable slot 4.

namespace _STL {

class locale {
public:
	class facet {
	protected:
		virtual ~facet();
		int _M_ref_count;
		bool _M_delete;
	};
};

class _Messages {
public:
	virtual void *do_open();
	virtual void *do_get_c();
	virtual void *do_get_w();
	virtual void do_close();
	virtual void *scalar_deleting_destructor(unsigned int);
	char _M_owned;
};

class messages_base {
public:
	typedef int catalog;
};

template <class _CharT>
class messages {};

template <>
class messages<char> : public locale::facet, public messages_base {
protected:
	~messages();
private:
	_Messages *_M_impl;
};

template <>
class messages<unsigned short> : public locale::facet, public messages_base {
protected:
	~messages();
private:
	_Messages *_M_impl;
};

messages<char>::~messages()
{
	_Messages *impl = _M_impl;
	if (impl != 0 && impl->_M_owned)
		impl->scalar_deleting_destructor(1);
}

messages<unsigned short>::~messages()
{
	_Messages *impl = _M_impl;
	if (impl != 0 && impl->_M_owned)
		impl->scalar_deleting_destructor(1);
}

} // namespace _STL
