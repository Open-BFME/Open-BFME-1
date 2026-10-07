// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: retail 0x0046C7D0, 272 bytes. Converted from gen-dump
// d_0046c7d0. Reached through ILT 0x00008FEE from the image draw helpers at
// 0x0046F060 and 0x0046F3D0, which call it on the 0x012F19E8 manager and
// draw the pointer it returns. Looks the level-prefix-stripped path up in the
// AsciiString hash at +0x6C; on a miss it retries with the path cut at its
// '~' (and a '/' just before it), restoring the cut character afterwards.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef int Int;
typedef bool Bool;

const char *bfmeSkipLevelPrefix(const char *path);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

// Retail calls the bucket lookup through ILT 0x0002F612, pinned as the
// hash_map<AsciiString, Rva00469FC0Mapped> _M_find instantiation.
enum Rva00469FC0Mapped { Rva00469FC0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva00469FC0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00469FC0Mapped> > > Rva0046C7D0Hash;

class Rva00579160Manager
{
public:
	void *bfmeLookup46C7D0(const char *pathIn) const;

private:
	unsigned char m_pad[0x6c];
	Rva0046C7D0Hash m_table;			// +0x6c
};

void *Rva00579160Manager::bfmeLookup46C7D0(const char *pathIn) const
{
	const char *path = bfmeSkipLevelPrefix(pathIn);

	if (*path == 0)
		return 0;

	Rva0046C7D0Hash::const_iterator it = m_table.find(AsciiString(path));
	if (it == m_table.end())
	{
		char *cut = strchr(path, '~');
		if (cut == 0)
			return 0;

		if (cut[-1] == '/')
			--cut;

		char saved = *cut;
		*cut = 0;
		it = m_table.find(AsciiString(path));
		*cut = saved;
		if (it == m_table.end())
			return 0;
	}

	return (void *)it->second;
}
