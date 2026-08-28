// cl: /DNDEBUG /MD /EHsc
// readable body of ?Make_Unique@VertexMaterialClass@@QAEXXZ: Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp

// VertexMaterialClass::Make_Unique (packet 00920ed0) is a two-field write
// (UniqueID at real offset 0x60, CRCDirty at real offset 0x68) against a
// file-static counter. Per the already-landed VertexMaterialClass_Init_Thunk.cpp
// (see reverse/re_attempts.log, ?Init@VertexMaterialClass@@SAXXZ, 0x00921EC0),
// vertmaterial.h's sizeof(VertexMaterialClass) is 0x6C not 0x70 (a spurious
// extra dword ahead of MaterialDyn shifts every later field 4 bytes off from
// retail), so this stays a local replica sized/laid out to match retail
// exactly instead of an edit to the shared header used by 40+ matched rows
// in vertmaterial.cpp.
//
// Real field offsets: UniqueID=0x60, CRC=0x64, CRCDirty=0x68, UseLighting=0x69.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	void Make_Unique();

private:
	unsigned char _unused_pre_unique[0x60];
	unsigned int UniqueID;			// real offset 0x60
	unsigned char _unused_between[0x68 - 0x64];
	unsigned char CRCDirty;			// real offset 0x68
	unsigned char _unused_tail[0x6C - 0x69];	// pad sizeof() to 0x6C
};

static unsigned int unique = 1;

// ?Make_Unique@VertexMaterialClass@@QAEXXZ
void VertexMaterialClass::Make_Unique()
{
	CRCDirty = true;
	UniqueID = unique;
	unique++;
}
