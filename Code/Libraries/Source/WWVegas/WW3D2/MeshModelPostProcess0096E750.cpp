// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME7: MeshModelClass::post_process at 0x0096E750 (106 B), the BFME
// shape of meshmdlio.cpp's post-load pass: skinned meshes drop their cull tree
// (inline REF_PTR_RELEASE: --NumRefs, Delete_This through vtable slot 0),
// flag 0x100 runs a per-material-description pass (0x0096CF60, a
// MeshMatDescClass member that clears bit 0x100000 on the description and on
// every pass entry) over DefMatDesc (+0x94) and AlternateMatDesc (+0x98),
// then SORT with no sort level and WW3D's munge-on-load flag (VA 0x0133F42E)
// tail-jumps into compute_static_sort_levels. Flags live at +0x18, SortLevel
// at +0x1c, CullTree at +0x90.

class Rva0096E750RefCounted
{
public:
	virtual void Delete_This() = 0;
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

class MeshMatDescClass
{
public:
	void Rva0096CF60ClearPassBit();
};

class WW3D
{
public:
	static bool Is_Munge_Sort_On_Load_Enabled() { return IsMungeSortOnLoadEnabled; }
	static bool IsMungeSortOnLoadEnabled;
};

class MeshModelClass
{
public:
	enum
	{
		SORT = 0x10,
		BFME_MATDESC_PASS = 0x100,
		SKIN = 0x400
	};
	unsigned Get_Flag(unsigned flag) const { return Flags & flag; }
protected:
	void post_process();
	void compute_static_sort_levels();

	char m_pad0[0x18];
	unsigned int Flags;
	char SortLevel;
	char m_pad1[0x90 - 0x1d];
	Rva0096E750RefCounted *CullTree;
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
};

void MeshModelClass::post_process()
{
	// skinned meshes should not have cull trees
	if (Get_Flag(SKIN)) {
		if (CullTree) {
			CullTree->Release_Ref();
			CullTree = 0;
		}
	}

	if (Get_Flag(BFME_MATDESC_PASS)) {
		DefMatDesc->Rva0096CF60ClearPassBit();
		if (AlternateMatDesc) {
			AlternateMatDesc->Rva0096CF60ClearPassBit();
		}
	}

	// Static sort levels
	if (Get_Flag(SORT) && (SortLevel == 0) && WW3D::Is_Munge_Sort_On_Load_Enabled()) {
		compute_static_sort_levels();
	}
}
