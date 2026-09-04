// ??0MaterialRemapperClass@@QAE@PAVMaterialInfoClass@@0@Z
// partial score=0.92 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// MaterialRemapperClass dtor / ctor / Remap_Mesh. Dedicated TU so iterating
// does not rebuild matinfo.cpp. Texture remaps are non-trivial (16-bit
// TextureClass refs + cookie new[]/delete[]); vmat remaps are a POD pair.
//
// Retail allocates and frees both arrays through operator new[] / delete[]
// (0x00881F70 / 0x00881EF0). Extern declarations stop MSVC 7.1 from
// lowering those to the scalar pair. Get_Texture is ICF'd with
// Gen_007A0340::bfmeGet (return-by-value handle at this+0x24).

void *__cdecl operator new[](unsigned int n);
void __cdecl operator delete[](void *pointer);

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
	void **VmatVector;
	int m_10;
	int m_14;
	int VmatCount;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int TextureCount;

	void Add_Ref(void)
	{
		++m_refs;
	}

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

struct VmatRemapStruct
{
	void *Src;
	void *Dest;
};

// Same spelling as the ICF'd Get_Texture return so
// ?bfmeGet@Gen_007A0340@@QBE?AVBfmeHandleCX@@H@Z resolves.
struct BfmeHandleCX
{
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

	if (src->VmatCount > 0)
	{
		VertexMaterialRemaps = (VmatRemapStruct *)operator new[]((unsigned)(VertexMaterialCount = src->VmatCount) * 8);
		for (int i = 0; i < src->VmatCount; i++)
		{
			VertexMaterialRemaps[i].Src = src->VmatVector[i];
			VertexMaterialRemaps[i].Dest = dest->VmatVector[i];
		}
	}

	if (src->TextureCount > 0)
	{
		TextureCount = src->TextureCount;
		TextureRemaps = new TextureRemapStruct[src->TextureCount];
		for (int i = 0; i < src->TextureCount; i++)
		{
			TextureRemaps[i].Src = reinterpret_cast<Gen_007A0340 *>(src)->bfmeGet(i);
			TextureRemaps[i].Dest = reinterpret_cast<Gen_007A0340 *>(dest)->bfmeGet(i);
		}
	}
}

MaterialRemapperClass::~MaterialRemapperClass(void)
{
	SrcMatInfo->Release_Ref();
	DestMatInfo->Release_Ref();
	if (TextureRemaps)
		delete[] TextureRemaps;
	if (VertexMaterialRemaps)
		delete[] VertexMaterialRemaps;
}
