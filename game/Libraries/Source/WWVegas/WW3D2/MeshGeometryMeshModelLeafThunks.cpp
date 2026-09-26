// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: MeshGeometry leaf at 0x00924C30 (14B).
// Shape: load this+0x10; if non-null return *(ptr+0xc) else null.
// Get_User_Text is the clean C++ owner. Earlier versions also emitted the
// same bytes under two MeshModel::Replace_* names, but those void, two-argument
// declarations contradict a body that ignores its arguments and returns the
// inner pointer. They were unledgered false aliases, not recovered identities.

struct MeshGeomInner
{
	char pad[0xc];
	const char *text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
public:
	const char *Get_User_Text();

private:
	char m_pad[0x10];
	MeshGeomInner *m_data;
};

// ?Get_User_Text@MeshGeometryClass@@QAEPBDXZ
const char *MeshGeometryClass::Get_User_Text()
{
	MeshGeomInner *data = m_data;
	if (data)
		return data->text;
	return 0;
}
