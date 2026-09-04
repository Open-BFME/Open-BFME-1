// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// MaterialRemapperClass dtor / ctor / Remap_Mesh. Dedicated TU so iterating
// does not rebuild matinfo.cpp. Texture remaps are non-trivial (16-bit
// TextureClass refs + cookie new[]/delete[]); vmat remaps are a POD pair.
//
// Retail frees both arrays through operator delete[] (0x00881EF0), not
// scalar delete. An extern declaration stops MSVC 7.1 from lowering
// delete[] to ??3@YAXPAX@Z.

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

struct TextureRemapStruct
{
	TextureClass *Src;
	TextureClass *Dest;

	TextureRemapStruct(void) : Src(0), Dest(0)
	{
	}

	~TextureRemapStruct(void)
	{
		if (Dest)
			Dest->Release_Ref();
		if (Src)
			Src->Release_Ref();
	}
};

// LastSrcTex / LastDestTex are owning refs. Their implicit dtors (Dest
// then Src, reverse declaration order) are what emit retail's trailing
// Release_Ref calls and the EH state 0 / -1 stores around them.
struct TextureRef
{
	TextureClass *p;

	~TextureRef(void)
	{
		if (p)
			p->Release_Ref();
	}
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
	TextureRef LastSrcTex;
	TextureRef LastDestTex;
};

MaterialRemapperClass::~MaterialRemapperClass(void)
{
	SrcMatInfo->Release_Ref();
	DestMatInfo->Release_Ref();
	if (TextureRemaps)
		delete[] TextureRemaps;
	if (VertexMaterialRemaps)
		delete[] VertexMaterialRemaps;
}
