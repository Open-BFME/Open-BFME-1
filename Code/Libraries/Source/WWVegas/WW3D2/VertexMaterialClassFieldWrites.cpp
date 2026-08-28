// cl: /DNDEBUG /MD /EHsc
// readable body of ?Make_Unique@VertexMaterialClass@@QAEXXZ: Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp
// readable body of ?Set_UV_Source@VertexMaterialClass@@QAEXHH@Z: Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp

// VertexMaterialClass::Make_Unique (packet 00920ed0) and ::Set_UV_Source
// (packet 00921250) are one shape: write a single field, then raise CRCDirty
// (real offset 0x68). Make_Unique's field is UniqueID (0x60), fed by a
// file-static counter; Set_UV_Source's is UVSource[stage] (0x40, 8 elements).
// WWASSERT is a no-op in this (NDEBUG) build config.
//
// Per the already-landed VertexMaterialClass_Init_Thunk.cpp (see
// reverse/re_attempts.log, ?Init@VertexMaterialClass@@SAXXZ, 0x00921EC0),
// vertmaterial.h's sizeof(VertexMaterialClass) is 0x6C not 0x70 (a spurious
// extra dword ahead of MaterialDyn shifts every later field 4 bytes off from
// retail), so this stays a local replica sized/laid out to match retail
// exactly instead of an edit to the shared header used by 40+ matched rows
// in vertmaterial.cpp. They sat in two single-function files, each
// re-declaring the same replica with a different span of opaque padding, so
// nothing checked that the two agreed about where UniqueID ends and CRC
// begins.
//
// Real field offsets: UVSource[8]=0x40, UniqueID=0x60, CRC=0x64,
// CRCDirty=0x68, UseLighting=0x69, padded to 0x6C.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	void Make_Unique();
	void Set_UV_Source(int stage, int array_index);

private:
	unsigned char _unused_pre_uvsource[0x40];
	unsigned int UVSource[8];		// real offset 0x40
	unsigned int UniqueID;			// real offset 0x60
	unsigned char _unused_crc[0x68 - 0x64];	// CRC, real offset 0x64
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

// ?Set_UV_Source@VertexMaterialClass@@QAEXHH@Z
void VertexMaterialClass::Set_UV_Source(int stage, int array_index)
{
	CRCDirty = true;
	UVSource[stage] = array_index;
}
