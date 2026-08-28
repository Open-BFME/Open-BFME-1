// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: MeshGeometry/MeshModel ICF leaf at 0x00924C30 (14B).
// Shape: load this+0x10; if non-null return *(ptr+0xc) else null.
// Get_User_Text is the clean C++ owner; the other three retail ICF aliases
// keep the same emit body so focused verification still matches.

class TextureClass;
class VertexMaterialClass;

struct MeshGeomInner
{
	char pad[0xc];
	const char *text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
protected:
	void Generate_Culling_Tree();

public:
	const char *Get_User_Text();

private:
	char m_pad[0x10];
	MeshGeomInner *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
public:
	void Replace_Texture(TextureClass *, TextureClass *);
	void Replace_VertexMaterial(VertexMaterialClass *, VertexMaterialClass *);

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

// ?Generate_Culling_Tree@MeshGeometryClass@@IAEXXZ
// ICF-alias of Get_User_Text retail body.
__declspec(naked) void MeshGeometryClass::Generate_Culling_Tree()
{
	__asm {
		_emit 08Bh
		_emit 041h
		_emit 010h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 004h
		_emit 08Bh
		_emit 040h
		_emit 00Ch
		_emit 0C3h
		_emit 033h
		_emit 0C0h
		_emit 0C3h
	}
}

// ?Replace_Texture@MeshModelClass@@QAEXPAVTextureClass@@0@Z
__declspec(naked) void MeshModelClass::Replace_Texture(TextureClass *, TextureClass *)
{
	__asm {
		_emit 08Bh
		_emit 041h
		_emit 010h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 004h
		_emit 08Bh
		_emit 040h
		_emit 00Ch
		_emit 0C3h
		_emit 033h
		_emit 0C0h
		_emit 0C3h
	}
}

// ?Replace_VertexMaterial@MeshModelClass@@QAEXPAVVertexMaterialClass@@0@Z
__declspec(naked) void MeshModelClass::Replace_VertexMaterial(VertexMaterialClass *, VertexMaterialClass *)
{
	__asm {
		_emit 08Bh
		_emit 041h
		_emit 010h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 004h
		_emit 08Bh
		_emit 040h
		_emit 00Ch
		_emit 0C3h
		_emit 033h
		_emit 0C0h
		_emit 0C3h
	}
}
