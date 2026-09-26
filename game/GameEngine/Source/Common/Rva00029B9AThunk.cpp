// cl: /O2 /DNDEBUG /MD /EHsc-
//
// Retail 0x00029B9A is a five-byte incremental-link thunk. Its direct target
// is the matched BitFlags<45>::parseFromINI body at 0x00204E70.

class INI;

template <int NUMBITS>
class BitFlags
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

class Rva00029B9AThunk
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store,
		const void *userData);
};

void Rva00029B9AThunk::parseFromINI(INI *ini, void *instance, void *store,
	const void *userData)
{
	BitFlags<45>::parseFromINI(ini, instance, store, userData);
}
