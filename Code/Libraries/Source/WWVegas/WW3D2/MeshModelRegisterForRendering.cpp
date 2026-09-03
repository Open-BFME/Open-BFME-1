// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class MeshModelClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Register_Mesh_Type(MeshModelClass *mesh);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;
extern unsigned int NPatchesLevel;
extern unsigned int NPatchesGapFillingMode;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
	char m_prefix[0xc4];
	bool m_hasBeenInUse;

public:
	void Init_For_NPatch_Rendering();
	void Register_For_Rendering();
};

void MeshModelClass::Register_For_Rendering()
{
	m_hasBeenInUse = true;
	if (NPatchesLevel > 1) {
		if (NPatchesGapFillingMode != 0) {
			Init_For_NPatch_Rendering();
		}
	} else if (NPatchesGapFillingMode == 2) {
		Init_For_NPatch_Rendering();
	}
	TheDX8MeshRenderer->Register_Mesh_Type(this);
}
