// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BFME MaterialRemapperClass constructor, retail 0x0092FD60 (453 bytes).
// The destructor remains in MaterialRemapper.cpp so this TU can retain the
// constructor's independent MSVC 7.1 layout and EH shape.

void *__cdecl operator new[](unsigned int n);

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

MaterialRemapperClass::MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest) :
	TextureCount(0),
	TextureRemaps(0),
	VertexMaterialCount(0),
	VertexMaterialRemaps(0),
	LastSrcVmat(0),
	LastDestVmat(0)
{
	SrcMatInfo = src;
	src->Add_Ref();
	DestMatInfo = dest;
	dest->Add_Ref();

	if (src->Vertex_Material_Count() > 0)
	{
		VertexMaterialRemaps = (VmatRemapStruct *)operator new[]((unsigned)(VertexMaterialCount = src->Vertex_Material_Count()) * 8);
		for (int i = 0; i < src->Vertex_Material_Count(); i++)
		{
			VertexMaterialRemaps[i].Src = src->Peek_Vertex_Material(i);
			VertexMaterialRemaps[i].Dest = dest->Peek_Vertex_Material(i);
		}
	}

	if (src->TextureCount > 0)
	{
		TextureCount = src->TextureCount;
		TextureRemaps = new TextureRemapStruct[TextureCount];
		for (int i = 0; i < src->TextureCount; i++)
		{
			TextureRemaps[i].Src = reinterpret_cast<Gen_007A0340 *>(src)->bfmeGet(i);
			TextureRemaps[i].Dest = reinterpret_cast<Gen_007A0340 *>(dest)->bfmeGet(i);
		}
	}
}
