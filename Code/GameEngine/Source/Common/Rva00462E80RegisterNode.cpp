// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: carved body at retail 0x00462E80 (431 bytes), a plain __cdecl
// free function. Its only caller, Rva00463BA0 (Rva00463BA0WindowBounds.cpp),
// looks a node up by path leaf in the table Rva00462DE0 searches and calls
// this on a miss with (path, query). This body parses "_RenderObj",
// "_KeepAspectRatio" and "_AnimMode" out of the query (literals at retail
// 0x00CF6FEC/0x00CF6FD8/0x00CF6FA8), creates the node through
// createGen_0078A430 (Gen_0078A430.cpp; vtable 0x01126CCC, whose slot names
// are not recovered), and registers it under the leaf in the same global
// table (g_Rva00462DE0_table, retail 0x00EF19B8). Owner and real name are
// unproven, so the name stays address-derived.

#include "ascii_string.h"

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

namespace rts { template <class T> struct hash { unsigned int operator()(T value) const; }; }

enum Rva004613F0Mapped { Rva004613F0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva004613F0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva004613F0Mapped> > > Rva004613F0Map;

// address-derived stand-in for the hashtable instance at retail 0x00EF19B8
class Rva00462DE0Table : public Rva004613F0Map
{
};

extern Rva00462DE0Table g_Rva00462DE0_table;

// retail AsciiString view: buffer header with the length word at +4 and the
// characters at +8, inlined by retail at every check below
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const { return m_data ? m_data + 8 : ""; }
	int getLength() const { return m_data ? *(const unsigned short *)(m_data + 4) : 0; }
	bool isEmpty() const { return !m_data || !*(const unsigned short *)(m_data + 4); }

private:
	void releaseBuffer();

	const char *m_data;
};

class BfmeStrVMZ;

const char *__cdecl bfmePathLeafAfterMarker(const char *path);
char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);
BFMERetailAsciiString Rva0046F6F0SlashToDot(void *what);
int bfmeGoDYG(void *s);

// layout from Gen_0078A430.cpp; the table pointer is the vtable at 0x01126CCC
struct Gen_0078A430
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3(const BFMERetailAsciiString &dotPath,
		const BFMERetailAsciiString &renderObj, const BFMERetailAsciiString &animMode);

	int m_a;
	int m_b;
	int m_c;
	int m_d;
	unsigned char m_flag;
	int m_e;
	int m_f;
	int m_g;
	int m_h;
	int m_i;
	int m_j;
};

Gen_0078A430 *createGen_0078A430(unsigned char flag);

static inline BfmeStrVMZ *asParam(BFMERetailAsciiString *s)
{
	return reinterpret_cast<BfmeStrVMZ *>(s);
}

static inline const char *findChar(const char *p, const char *end, char c)
{
	for (; p != end; ++p)
	{
		if (*p == c)
			return p;
	}
	return 0;
}

// ?Rva00462E80@@YAPAXPBD0@Z -- address-derived name, identity unresolved
void *Rva00462E80(const char *path, const char *query)
{
	const char *leaf = bfmePathLeafAfterMarker(path);

	BFMERetailAsciiString renderObj;
	if (!bfmeGetParamVMZ(query, "_RenderObj", asParam(&renderObj)))
		return 0;
	if (renderObj.isEmpty())
		return 0;

	BFMERetailAsciiString keepAspect;
	bfmeGetParamVMZ(query, "_KeepAspectRatio", asParam(&keepAspect));

	const char *begin = keepAspect.str();
	bool keepAspectRatio = findChar(begin, begin + keepAspect.getLength(), 'f') == 0;

	BFMERetailAsciiString animMode;
	bfmeGetParamVMZ(query, "_AnimMode", asParam(&animMode));

	Gen_0078A430 *obj = createGen_0078A430(keepAspectRatio);
	obj->slot1();
	obj->m_a = bfmeGoDYG((void *)path);
	obj->slot3(Rva0046F6F0SlashToDot((void *)path), renderObj, animMode);

	reinterpret_cast<void *&>(g_Rva00462DE0_table[AsciiString(leaf)]) = obj;
	return obj;
}
