// cl: /DNDEBUG /MD /EHsc
// readable body of ?Set_UV_Source@VertexMaterialClass@@QAEXHH@Z: Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.cpp

// VertexMaterialClass::Set_UV_Source (packet 00921250) writes UVSource[stage]
// (real offset 0x40, 8-element array) and sets CRCDirty (real offset 0x68).
// Per the already-landed VertexMaterialClass_Init_Thunk.cpp (see
// reverse/re_attempts.log, ?Init@VertexMaterialClass@@SAXXZ, 0x00921EC0),
// vertmaterial.h's sizeof(VertexMaterialClass) is 0x6C not 0x70 (a spurious
// extra dword ahead of MaterialDyn shifts every later field 4 bytes off from
// retail), so this stays a local replica sized/laid out to match retail
// exactly instead of an edit to the shared header used by 40+ matched rows
// in vertmaterial.cpp. WWASSERT is a no-op in this (NDEBUG) build config.
//
// Real field offsets: UVSource[8]=0x40, UniqueID=0x60, CRCDirty=0x68.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	void Set_UV_Source(int stage, int array_index);

private:
	unsigned char _unused_pre_uvsource[0x40];
	unsigned int UVSource[8];		// real offset 0x40
	unsigned char _unused_between[0x68 - 0x60];
	unsigned char CRCDirty;			// real offset 0x68
	unsigned char _unused_tail[0x6C - 0x69];	// pad sizeof() to 0x6C
};

// ?Set_UV_Source@VertexMaterialClass@@QAEXHH@Z
void VertexMaterialClass::Set_UV_Source(int stage, int array_index)
{
	CRCDirty = true;
	UVSource[stage] = array_index;
}
