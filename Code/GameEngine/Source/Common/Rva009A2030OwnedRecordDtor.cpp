// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x009A2030 (125 B): fuzzy twin (tools/fuzzy_twin_scan.py) of the
// Rva003691A0OwnedRecord destructor in Rva0036B6B0OwnedPointerCleanup.cpp.
// Same 8-byte-pair vector at +0 freed through the inline __node_alloc shape,
// but where the twin releases a trailing StringBase member, this body calls a
// this-relative helper (the dump at 0x009A1F90, thiscall, no arguments) from
// the destructor body first. Identity unproven; address-derived names.

#include <vector>

struct Rva009A2030Pair
{
	void *m_first;
	void *m_second;
};

class Rva009A2030OwnedRecord
{
public:
	~Rva009A2030OwnedRecord();

private:
	void releaseContents();	// 0x009A1F90

	std::vector<Rva009A2030Pair> m_pairs;
};

Rva009A2030OwnedRecord::~Rva009A2030OwnedRecord()
{
	releaseContents();
}
