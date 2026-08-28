// cl: /DNDEBUG /MD /EHsc

// VertexMaterialClass::Init (packet 00921eba) disagrees with the vendored
// vertmaterial.h on two points, both confirmed directly against the retail
// constructor at 0x00921820 and the retail Set_Ambient/Set_Emissive_Color_Source
// bodies at 0x00921160/0x00921190 (Get_Ambient/Get_Emissive_Color_Source at
// 0x00921210/0x00921230 read one field ahead of what their names claim, which
// independently pins the same three offsets):
//
//   - sizeof(VertexMaterialClass) is 0x6C (108), not the header's 0x70 (112).
//     The header's vertmaterial.h carries a spurious extra dword ahead of
//     MaterialDyn; retail's ctor stores the D3D material pointer at this+0x8
//     (immediately after RefCountClass's vtable ptr + NumRefs), with no gap.
//   - VertexMaterialClass does not use the W3DMPO_GLUE pooled operator new in
//     retail: Init's allocation is a single call to plain ::operator new(0x6C)
//     (0x00881F30, already matched as ??2@YAPAXI@Z), not the
//     getClassMemoryPool()+allocateFromW3DMemPool(pool,size) pair the header's
//     macro would generate.
//
// Real field offsets (from the retail ctor 0x00921820 and the two Set_*
// bodies above): vtable=0x00, NumRefs=0x04, MaterialDyn=0x08, Flags=0x0C,
// AmbientColorSource=0x10, EmissiveColorSource=0x14, DiffuseColorSource=0x18,
// Name=0x1C, Mapper[8]=0x20, UVSource[8]=0x40, UniqueID=0x60, CRC=0x64,
// CRCDirty=0x68, UseLighting=0x69, padded to 0x6C.
//
// vertmaterial.h is shared by 40+ already-matched rows in vertmaterial.cpp,
// so per project convention this is a local replica sized/laid out to match
// retail exactly rather than an edit to the shared header: only the fields
// Init actually touches are named, everything else is opaque padding, and
// the real (unmodified) constructor/Presets array are pulled in by mangled
// name so this stays a single definition of each, not a duplicate.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	enum ColorSourceType
	{
		MATERIAL = 0,
		COLOR1,
		COLOR2,
	};

	enum PresetType
	{
		PRELIT_DIFFUSE = 0,
		PRELIT_NODIFFUSE,
		PRESET_COUNT,
	};

	VertexMaterialClass(void);

	void Set_Diffuse_Color_Source(ColorSourceType src);
	void Set_Lighting(bool lighting);

	static void Init();

private:
	unsigned char _unused_pre_diffuse_source[0x18];
	unsigned int DiffuseColorSource;					// real offset 0x18
	unsigned char _unused_between[0x68 - 0x1C];
	unsigned char CRCDirty;								// real offset 0x68
	unsigned char UseLighting;							// real offset 0x69
	unsigned char _unused_tail[0x6C - 0x6A];			// pad sizeof() to 0x6C

	static VertexMaterialClass *Presets[PRESET_COUNT];
};

void VertexMaterialClass::Set_Diffuse_Color_Source(ColorSourceType src)
{
	CRCDirty = true;
	switch (src)
	{
	case COLOR1:	DiffuseColorSource = 1; break;
	case COLOR2:	DiffuseColorSource = 2; break;
	default:			DiffuseColorSource = 0; break;
	}
}

void VertexMaterialClass::Set_Lighting(bool lighting)
{
	CRCDirty = true;
	UseLighting = lighting;
}

// ?Init@VertexMaterialClass@@SAXXZ
void VertexMaterialClass::Init()
{
	int i;
	for (i = 0; i < PRESET_COUNT; i++)
		Presets[i] = new VertexMaterialClass();

	// Set up presets
	Presets[PRELIT_DIFFUSE]->Set_Diffuse_Color_Source(COLOR1);
	Presets[PRELIT_DIFFUSE]->Set_Lighting(false);
	Presets[PRELIT_NODIFFUSE]->Set_Lighting(false);
}
