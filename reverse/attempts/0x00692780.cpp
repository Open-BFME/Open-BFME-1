// ?_M_upper_bound@?$_Rb_tree@URva00692690Key@@U1@U?$_Identity@URva00692690Key@@@_STL@@U?$less@URva00692690Key@@@3@V?$allocator@URva00692690Key@@@3@@_STL@@ABEPAU?$_Rb_tree_node@URva00692690Key@@@2@ABURva00692690Key@@@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _Rb_tree 12-byte key lower_bound / upper_bound at 0x00692690
// and 0x00692780. Unsigned primary then inlined AsciiString compare.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	int compare(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : "";
		int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result == 0) {
			result = myLen - len;
		}
		return result;
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

struct Rva00692690Key
{
	unsigned primary;
	AsciiString secondary;
	unsigned trailing;
};

inline bool operator<(const Rva00692690Key &left, const Rva00692690Key &right)
{
	if (left.primary < right.primary)
		return true;
	if (left.primary > right.primary)
		return false;
	return left.secondary.compare(right.secondary) < 0;
}

Bool BfmeRva00692690BoundsAnchor(const _STL::set<Rva00692690Key> &tree, const Rva00692690Key &key)
{
	return tree.lower_bound(key) != tree.upper_bound(key);
}
