// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace _STL
{

struct input_iterator_tag
{
};

struct forward_iterator_tag : public input_iterator_tag
{
};

struct __false_type
{
};

template <class Type>
struct _Is_integer
{
	typedef __false_type _Integral;
};

template <class Character>
class char_traits
{
};

template <class Character>
class allocator
{
public:
	__declspec(nothrow) allocator(void) {}
	__declspec(nothrow) allocator(const allocator &source) {}
	__declspec(nothrow) ~allocator(void) {}
};

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *pointer, unsigned int bytes);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &a, Pointer pointer)
		: Alloc(a), _M_data(pointer) {}

	Pointer _M_data;

	void deallocate(Pointer pointer, unsigned int count)
	{
		if (pointer != 0)
		{
			if (count > 128)
				::operator delete(pointer);
			else
				__node_alloc<false, 0>::_M_deallocate(pointer, count);
		}
	}
};

template <class Character, class Alloc>
class _String_base
{
public:
	Character *_M_start;
	Character *_M_finish;
	_STLP_alloc_proxy<Character *, Character, Alloc> _M_end_of_storage;

	_String_base(const Alloc &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (Character *)0) {}
	~_String_base(void)
	{
		_M_end_of_storage.deallocate(_M_start,
			(unsigned int)(_M_end_of_storage._M_data - _M_start));
	}
};

template <class Character, class Traits, class Alloc>
class basic_string : protected _String_base<Character, Alloc>
{
public:
	typedef Alloc allocator_type;

		basic_string(const Character *text,
			const allocator_type &a = allocator_type());
		basic_string(const basic_string &source);

		template <class InputIterator>
		basic_string &append(InputIterator first, InputIterator last,
			const forward_iterator_tag &tag);

	template <class InputIterator>
		basic_string &append(InputIterator first, InputIterator last)
		{
			typedef typename _STL::_Is_integer<InputIterator>::_Integral Integral;
			return appendDispatch(first, last, Integral());
		}

	basic_string &append(const basic_string &source)
		{
			return append(source._M_start, source._M_finish);
		}

	private:
		template <class InputIterator>
		basic_string &appendDispatch(InputIterator first, InputIterator last,
			const __false_type &)
		{
			return append(first, last, forward_iterator_tag());
		}

	public:

	const Character *c_str(void) const
	{
		return this->_M_start;
	}

	unsigned int length(void) const
	{
		return (unsigned int)(this->_M_finish - this->_M_start);
	}

	~basic_string(void) {}
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > RegistryString;

bool getUnsignedIntFromRegistry( HKEY root, RegistryString path, RegistryString key, unsigned int &val )
{
	HKEY handle;
	unsigned long buffer;
	unsigned long size = sizeof(buffer);
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyEx( root, path.c_str(), 0, KEY_READ, &handle )) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueEx( handle, key.c_str(), NULL, &type,
		                              (unsigned char *)&buffer, &size );
		RegCloseKey( handle );
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = buffer;
		return true;
	}

	return false;
}

bool setStringInRegistry( HKEY root, RegistryString path, RegistryString key, RegistryString val )
{
	HKEY handle;
	unsigned long type;
	unsigned long returnValue;
	int size;

	if ((returnValue = RegCreateKeyEx( root, path.c_str(), 0, "REG_NONE",
	                                  REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
	                                  &handle, NULL )) == ERROR_SUCCESS)
	{
		type = REG_SZ;
		size = val.length() + 1;
		returnValue = RegSetValueEx( handle, key.c_str(), 0, type,
		                             (unsigned char *)val.c_str(), size );
		RegCloseKey( handle );
	}

	return (returnValue == ERROR_SUCCESS);
}

bool SetStringInRegistry( RegistryString path, RegistryString key, RegistryString val )
{
	RegistryString fullPath =
		"SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
	fullPath.append(path);

	if (setStringInRegistry( (HKEY)0x80000002, fullPath, key, val))
		return true;

	return setStringInRegistry( (HKEY)0x80000001, fullPath, key, val );
}
