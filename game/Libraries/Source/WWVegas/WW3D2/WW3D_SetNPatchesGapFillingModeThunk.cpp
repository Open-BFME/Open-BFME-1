// cl: /DNDEBUG /MD /EHsc
// readable body of ?Set_NPatches_Gap_Filling_Mode@WW3D@@: game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp
//
// WW3D::Set_NPatches_Gap_Filling_Mode at retail 0x008FD060 (31 bytes),
// directly before the matched Set_NPatches_Level (0x008FD080), spelled against
// the retail BFME shape with the same two differences as
// WW3D_SetNPatchesLevelThunk.cpp: TheDX8MeshRenderer is a pointer
// (0x0134B0E8) and Invalidate takes a bool that retail passes as false.  The
// mode lives in the plain global 0x012D6D88, recorded in dir32_addresses.csv
// as NPatchesGapFillingMode.  Its own translation unit keeps the change off
// ww3d.cpp and off the Set_NPatches_Level TU.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Invalidate( bool shutdown );
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;
extern unsigned NPatchesGapFillingMode;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	enum NPatchesGapFillingModeEnum {
		NPATCHES_GAP_FILLING_DISABLED,
		NPATCHES_GAP_FILLING_ENABLED,
		NPATCHES_GAP_FILLING_FORCE
	};

	static void Set_NPatches_Gap_Filling_Mode( NPatchesGapFillingModeEnum mode );
};

void WW3D::Set_NPatches_Gap_Filling_Mode( NPatchesGapFillingModeEnum mode )
{
	if( NPatchesGapFillingMode != (unsigned)mode ) {
		NPatchesGapFillingMode = mode;
		TheDX8MeshRenderer->Invalidate( false );
	}
}
