// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace _STL
{

struct forward_iterator_tag
{
};

template <class Character>
class char_traits
{
};

template <class Character>
class allocator
{
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

template <class Character, class Traits, class Alloc>
class basic_string
{
public:
	Character *_M_start;
	Character *_M_finish;
	_STLP_alloc_proxy<Character *, Character, Alloc> _M_end_of_storage;

		basic_string(const Character *text,
			const allocator<Character> &a = allocator<Character>());
		basic_string(const basic_string &source);

		template <class InputIterator>
		basic_string &append(InputIterator first, InputIterator last,
			const forward_iterator_tag &tag);

	const Character *c_str(void) const
	{
		return _M_start;
	}

	unsigned int length(void) const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	~basic_string(void)
	{
		_M_end_of_storage.deallocate(_M_start,
			(unsigned int)(_M_end_of_storage._M_data - _M_start));
	}
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
	RegistryString fullPath = "SOFTWARE\\Electronic Arts\\EA Games\\Command and Conquer Generals Zero Hour";
	fullPath.append(path._M_start, path._M_finish,
		_STL::forward_iterator_tag());

	if (setStringInRegistry( (HKEY)0x80000002, fullPath, key, val))
		return true;

	return setStringInRegistry( (HKEY)0x80000001, fullPath, key, val );
}
