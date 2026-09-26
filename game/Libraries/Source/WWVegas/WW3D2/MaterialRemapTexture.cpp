// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME MaterialRemapper texture mapping, retail 0x0092F1F0 (194 bytes).
// Remap_Mesh at 0x0092F2C0 passes a borrowed handle and receives an owning
// handle through a hidden result pointer. Upstream matinfo.cpp supplies the
// cache lookup and mapping loop; BFME uses the same owning Texture handles
// already reconstructed by MaterialRemapperCtor.cpp.

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

class MaterialRemapperClass
{
public:
	MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest);
	~MaterialRemapperClass(void);
 BfmeHandleCX Remap_Texture(const BfmeHandleCX &src);

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


BfmeHandleCX MaterialRemapperClass::Remap_Texture(const BfmeHandleCX &src)
{
 if (!src.p) return src;
 if (src.p == LastSrcTex.p) return LastDestTex;
 for (int i = 0; i < TextureCount; ++i) {
  if (TextureRemaps[i].Src.p == src.p) {
   LastSrcTex = src;
   LastDestTex = TextureRemaps[i].Dest;
   return TextureRemaps[i].Dest;
  }
 }
 return BfmeHandleCX();
}
