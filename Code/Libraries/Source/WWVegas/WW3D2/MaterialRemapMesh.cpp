// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME MaterialRemapper mesh mapping, retail 0x0092F2C0 (493 bytes).
// The byte-matched clone_materials at 0x0096DDC0 identifies this method.
// Upstream matinfo.cpp traversal with BFME owning Texture handles: source
// handles remain local until each iteration ends, while remapped temporaries
// are released at the setter expression. Distinct lifetimes match retail EH.

class VertexMaterialClass;

class TextureClass
{
public:
	void Add_Ref(void)
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref(void);
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	int m_refs;
	int m_08;
	VertexMaterialClass **VmatVector;
	int m_10;
	int m_14;
	int VmatCount;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int TextureCount;

	int Vertex_Material_Count(void) const
	{
		return VmatCount;
	}

	VertexMaterialClass *Peek_Vertex_Material(int index)
	{
		return VmatVector[index];
	}

	void Add_Ref(void)
	{
		++m_refs;
	}
};

struct VmatRemapStruct
{
	VertexMaterialClass *Src;
	VertexMaterialClass *Dest;
};

// Same spelling as the ICF'd Get_Texture return so
// ?bfmeGet@Gen_007A0340@@QBE?AVBfmeHandleCX@@H@Z resolves.
class BfmeHandleCX
{
	public:
	TextureClass *p;

	BfmeHandleCX(void) : p(0)
	{
	}

	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p)
			p->Add_Ref();
	}

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p)
			other.p->Add_Ref();
		if (p)
			p->Release_Ref();
		p = other.p;
		return *this;
	}
};

struct TextureRemapStruct
{
	BfmeHandleCX Src;
	BfmeHandleCX Dest;
};

class Gen_007A0340
{
public:
	BfmeHandleCX bfmeGet(int index) const;
};

// BFME MeshMatDesc fields used by the original matinfo.cpp traversal.
class MeshMatDescClass {
public:
 int PassCount, VertexCount, PolygonCount;
 char pad[0x98];
 VertexMaterialClass *Material[4];
 void *TextureArray[4][2];
 void *MaterialArray[4];
 int Get_Pass_Count() const { return PassCount; }
 int Get_Vertex_Count() const { return VertexCount; }
 int Get_Polygon_Count() const { return PolygonCount; }
 bool Has_Material_Array(int pass) const { return MaterialArray[pass] != 0; }
 bool Has_Texture_Array(int pass, int stage) const { return TextureArray[pass][stage] != 0; }
 VertexMaterialClass *Peek_Single_Material(int pass) const { return Material[pass]; }
 VertexMaterialClass *Peek_Material(int index, int pass) const;
 void Set_Material(int index, VertexMaterialClass *material, int pass);
 void Set_Single_Material(VertexMaterialClass *material, int pass);
 BfmeHandleCX Get_Texture(int index, int pass, int stage) const;
 BfmeHandleCX Get_Single_Texture(int pass, int stage) const;
 void Set_Texture(int index, const BfmeHandleCX &texture, int pass, int stage);
 void Set_Single_Texture(const BfmeHandleCX &texture, int pass, int stage);
};

class MaterialRemapperClass
{
public:
	MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest);
	~MaterialRemapperClass(void);
 BfmeHandleCX Remap_Texture(const BfmeHandleCX &src);
 VertexMaterialClass *Remap_Vertex_Material(VertexMaterialClass *src);
 void Remap_Mesh(const MeshMatDescClass *src, MeshMatDescClass *dest);

	MaterialInfoClass *SrcMatInfo;
	MaterialInfoClass *DestMatInfo;
	int TextureCount;
	TextureRemapStruct *TextureRemaps;
	int VertexMaterialCount;
	VmatRemapStruct *VertexMaterialRemaps;
	void *LastSrcVmat;
	void *LastDestVmat;
	BfmeHandleCX LastSrcTex;
	BfmeHandleCX LastDestTex;
};


void MaterialRemapperClass::Remap_Mesh(const MeshMatDescClass *src, MeshMatDescClass *dest)
{
 if (SrcMatInfo->Vertex_Material_Count() >= 1) {
  for (int pass = 0; pass < src->Get_Pass_Count(); ++pass) {
   if (src->Has_Material_Array(pass)) {
    for (int vertex = 0; vertex < src->Get_Vertex_Count(); ++vertex) {
     VertexMaterialClass *material = src->Peek_Material(vertex, pass);
     dest->Set_Material(vertex, Remap_Vertex_Material(material), pass);
    }
   } else {
    dest->Set_Single_Material(Remap_Vertex_Material(src->Peek_Single_Material(pass)), pass);
   }
  }
 }
 if (SrcMatInfo->TextureCount >= 1) {
  for (int pass = 0; pass < src->Get_Pass_Count(); ++pass) {
   for (int stage = 0; stage < 2; ++stage) {
    if (src->Has_Texture_Array(pass, stage)) {
     for (int polygon = 0; polygon < src->Get_Polygon_Count(); ++polygon) {
      BfmeHandleCX texture = src->Get_Texture(polygon, pass, stage);
      dest->Set_Texture(polygon, Remap_Texture(texture), pass, stage);
     }
    } else {
     BfmeHandleCX texture = src->Get_Single_Texture(pass, stage);
     dest->Set_Single_Texture(Remap_Texture(texture), pass, stage);
    }
   }
  }
 }
}
