// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class Rva004525B0String
{
public:
	int compare(const Rva004525B0String &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

inline bool operator==(const Rva004525B0String &left,
	const Rva004525B0String &right)
{
	return left.compare(right) == 0;
}

typedef _STL::_Rb_tree_iterator<Rva004525B0String,
	_STL::_Const_traits<Rva004525B0String> > Rva004525B0Iterator;

char __cdecl Rva004525B0Equal(Rva004525B0Iterator first,
	Rva004525B0Iterator last, Rva004525B0Iterator second)
{
	return _STL::equal(first, last, second);
}
