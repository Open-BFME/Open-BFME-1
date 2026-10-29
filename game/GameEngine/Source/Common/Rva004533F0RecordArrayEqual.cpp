// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: retail 0x004533F0, 115 bytes: equality of two arrays of eight
// 20-byte records. Each record compares three bytes, a dword and an STLport
// set<Rva004525B0String> at +0x08 (set operator==: node count at +0x0C, then
// _STL::equal over the trees, the matched out-of-line body at 0x004525B0 via
// ILT 0x000162E8). The names stay address-derived; the string view and the
// _STLP_NO_EXCEPTIONS setting follow Rva004525B0TreeEqual.cpp.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

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

inline bool operator<(const Rva004525B0String &left,
	const Rva004525B0String &right)
{
	return left.compare(right) < 0;
}

struct Rva004533F0Record
{
	unsigned char m_byte0;
	unsigned char m_byte1;
	unsigned char m_byte2;
	int m_word4;
	_STL::set<Rva004525B0String> m_names;			// +0x08

	bool operator==(const Rva004533F0Record &that) const
	{
		return m_byte0 == that.m_byte0 && m_byte1 == that.m_byte1 &&
			m_byte2 == that.m_byte2 && m_word4 == that.m_word4 &&
			m_names == that.m_names;
	}
};

bool __cdecl rva004533f0(const Rva004533F0Record *first,
	const Rva004533F0Record *second)
{
	for (int i = 0; i < 8; ++i)
	{
		if (!(first[i] == second[i]))
			return false;
	}
	return true;
}
